# Architecture issues report (build date 2026-02-09)

## Miralis/Application.cpp
- The application constructor owns Vulkan resources (vertex + index buffers, pipeline, descriptors) at namespace scope, so `Application` is simultaneously a window, renderer and resource factory. That tight coupling eliminates any separation between the platform layer, renderer and game logic, makes testing harder, and leaves no room for swapping out a different renderer. These resources are also stored in global variables, so there is no way to create two `Application` instances or control their lifetimes safely.
- `Run()` drives the frame loop directly through `RenderCommands` (binds shaders, buffers, draws) instead of delegating to a renderer layer or layer stack. In addition to mixing responsibilities, `OnEvent()` loops from `m_LayerStack.end()` but never decrements before dereferencing, so it will read past the end of the vector and invoke undefined behaviour whenever an event arrives.
- No cleanup happens when the application shuts down—`Application::~Application()` is empty—yet every subsystems allocates GPU resources, so the class leaks buffers, pipelines and possibly the window/context when the process exits.

## Miralis/Application.h
- `Application` exposes only a static `CreateApplication` factory and the window getter; there is no dependency injection for renderer backends, window straps, or platform services, so the application is unconfigurable and tied to the single concrete implementation defined in `Application.cpp`.
- The singleton model inside `Application::Get()` prevents spawning more than one `Application`, while raw pointers are used throughout (`Layer*`, `LayerStack`), so ownership semantics are unclear and deletions become ad-hoc.

## Miralis/Core.h
- `MIRALIS_API` is always empty, so the header does not actually export anything when building a DLL; applications never see a proper import/export boundary.
- `BIT(x)` is defined as `(x>>1)` which is the opposite of the typical power-of-two flag helper; any flags defined with this macro will be miscalculated, so callers cannot rely on it for bitmask generation.

## Miralis/LayerStack.{cpp,h}
- `LayerStack` owns raw `Layer*` pointers and deletes them in its destructor, yet `Application::PushLayer()` passes stack-managed `Layer*` objects. The ownership contract is never documented and multiple deletes could easily happen if a caller also deletes the layer.
- `m_LayerInsert` is never kept in sync. `pushLayer` inserts before `m_LayerInsert` but never moves the iterator forward, `popLayer` unconditionally decrements even when `m_LayerInsert == begin()`, and `pushOverLay` bypasses `m_LayerInsert` entirely. This iterator arithmetic is fragile and will underflow or access invalid memory as soon as layers are removed.
- Application consumes the stack by iterating from `end()` without adjusting before dereference, so there is already undefined behaviour even before any overlay logic runs.

## Miralis/Window.h
- The `Window` interface exposes a single static `std::unique_ptr<GraphicsContext> m_Context`, meaning every window shares the same graphics context and the platform layer cannot host more than one window/context at a time. This static relationship also forces the Vulkan implementation to depend on the static `Window::m_Context`, which prevents unit testing and decouples context creation from window creation.
- The callback setter is called `SetEventClassBack` (probably a typo) and there is no clear contract for when the callback is invoked, which makes hooking platform events from the application layer brittle.

## Miralis/Log.{cpp,h}
- All logging macros are wired under `#if MR_DEBUG`, so release builds silently drop logs even though the infrastructure (spdlog) is already wired up. As soon as `MR_DEBUG` is undefined, `MR_LOG_*` expands to nothing and there is zero runtime diagnostics.
- `Log::Init()` unconditionally creates `spdlog::stdout_color_mt` loggers every time it runs; there is no guard against repeated calls nor a way to override the sinks, so the design forces early initialization in a single place, which increases coupling between `Application` and logging setup.

## Miralis/Rendering/RenderCommands.{cpp,h} & Renderer.{cpp,h}
- `RenderCommands` includes `RendererAPI.h"*` (note the stray `*`), which will not compile and shows there is no build-time verification of the rendering layer designs.
- `RenderCommand.cpp` eagerly constructs a `VulkanRendererAPI`, and `RendererAPI::s_API` is a static member hard-coded to Vulkan, so the system cannot switch backends or even substitute a mock renderer for unit tests.
- `Renderer` uses a class called `Rendere` with methods like `BegineScene` and `Sbumit`, locking the naming and API to a single implementation instead of providing a clean renderer interface.

## Miralis/Rendering/Buffer.{cpp,h}
- Buffer/Resource helpers call `Rendere::GetAPI()` and instantiate Vulkan buffers (`new VulkanVertexBuffer`, etc.) before handing the raw pointer to the caller. There is no factory abstraction or smart pointer, so the renderer is tightly bound to Vulkan and the caller is responsible for deleting the buffer.
- The helper functions duplicate the `createBuffer`/`copyBuffer` logic that already lives inside `VulkanContext`, so every buffer call reaches through the global context and duplicates logic, which makes maintenance harder and prevents sharing helper code between different renderers.

## Platfrom/Windows/WindowsWindow.{cpp,h}
- The Windows window implementation directly instantiates `VulkanContext` by reaching into `Window::m_Context`, so the platform layer can never host another renderer (OpenGL, D3D12, etc.). This static coupling to Vulkan also makes mocking or swapping the context impossible.
- `WindowsWindow::NewFrame()` only calls `m_Context->ImGUINewFrame()` and `OnUpdate()` only polls GLFW events; there is no coordination with `BeginScene`/`EndScene` or presentation, so the device never draws anything outside the minimal triangle that `Application` hard-codes.
- All GLFW callbacks are commented out, so no events actually reach the application layer even though `m_Data.EventCallBack` exists.

## Platfrom/Vulkan/VulkanContext.{cpp,h}
- The entire Vulkan stack (instance, device, swap chain, semaphores, command buffers, descriptor pools, ImGui state, etc.) sits inside `VulkanContext` with almost every handle marked `public`. Single-responsibility and encapsulation are violated, so everything is tightly coupled and no higher-level renderer can reuse a subset of that code.
- `SwapBuffers()` is empty, so there is no actual presentation path at all; `Application` calls `m_Window->m_Context->SwapBuffers()` every frame but it does nothing, so the architecture is non-functional.
- `VulkanContext` mixes platform/window management (GLFW callbacks, Win32 handles) with rendering resource allocation and ImGui setup, making the class massive and preventing reuse in other contexts or tests.
- Descriptor pool creation uses hard-coded numbers of descriptor types (mostly 1000). Because those constants are magic numbers, the pool size cannot adapt to real resource needs and will either over- or under-allocate.
- Resource helpers (`createBuffer`, `copyBuffer`, `findMemoryType`) are duplicated across `VulkanContext` and `VulkanBuffer`, so every new renderer that wants these helpers will have to reimplement them, rather than sharing a single utility or exposing a loader interface.

## Platfrom/Vulkan/VulkanBuffer.{cpp,h}
- Vertex/index/uniform buffers all pull the Vulkan handles from the static `Window::m_Context`, so they cannot exist without that specific global and cannot be moved to another renderer or tested in isolation.
- `VulkanResourceSet` constructor allocates descriptor sets and only destroys the layout in the destructor; descriptor sets and descriptor pools are never freed explicitly and the lifetime of `VkDescriptorSetLayoutBinding` data is tangled with the class fields.
- Uniform buffers are allocated per-frame and kept mapped forever (`uniformBuffersMapped`), but there is no allocator abstraction or upload helper, so every part of the renderer must duplicate the logic to call `UploadUnifrom`.

## Platfrom/Vulkan/VulkanPipeLine.h
- The Vulkan pipeline implementation inherits from `PipeLine` but the header exposes no builder or caching strategy, and the class holds a bare `VkPipeline` and `VkPipelineLayout` without any RAII helpers. This leaves pipeline creation scattered and makes shader/layout management fragile.

## Files I could not inspect
- `Miralis/Events/` and `Miralis/ImGui/` directories – every attempt to list or open contents timed out (invalid argument from the CLI) so I could not audit these files.
- `Platfrom/Vulkan/VulkanRenderAPI.*` and `Platfrom/Vulkan/VulkanShader.cpp` – the CLI consistently timed out before the command completed, so their contents were unavailable for review.

