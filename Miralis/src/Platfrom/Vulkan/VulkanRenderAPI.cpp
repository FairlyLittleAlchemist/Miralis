#include "Platfrom/Vulkan/VulkanRenderAPI.h"
#include "Platfrom/Vulkan/VulkanContext.h"
#include "Miralis/Window.h"

namespace Miralis {

	void Miralis::VulkanRendererAPI::SetClearColor(float r , float g , float b , float a)
	{
		VulkanContext* vkContext = static_cast<VulkanContext*>(Miralis::Window::m_Context.get());

		VkRenderPassBeginInfo renderPassInfo{} ;
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = vkContext->renderPass;
		renderPassInfo.framebuffer = vkContext->swapChainFramebuffers[vkContext->imageIndex];
		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = vkContext->swapChainExtent;

		VkViewport viewport{};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = static_cast<float>(vkContext->swapChainExtent.width);
		viewport.height = static_cast<float>(vkContext->swapChainExtent.height);
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;
		vkCmdSetViewport(vkContext->commandBuffers[vkContext->currentFrame], 0, 1, &viewport);

		VkRect2D scissor{};
		scissor.offset = { 0, 0 };
		scissor.extent = vkContext->swapChainExtent;
		vkCmdSetScissor(vkContext->commandBuffers[vkContext->currentFrame], 0, 1, &scissor);

		VkClearValue clearColor = { {{r, g, b, a}} };
		renderPassInfo.clearValueCount = 1;
		renderPassInfo.pClearValues = &clearColor;
		vkCmdBeginRenderPass(vkContext->commandBuffers[vkContext->currentFrame], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
		
	}
	void VulkanRendererAPI::DrawIndexed(uint32_t count)
	{
		VulkanContext* vkContext = static_cast<VulkanContext*>(Miralis::Window::m_Context.get());

		vkCmdDrawIndexed(vkContext->commandBuffers[vkContext->currentFrame], static_cast<uint32_t>(count), 1, 0, 0, 0);

	}
	void VulkanRendererAPI::BeingDraw()
	{
		VulkanContext* vkContext = static_cast<VulkanContext*>(Miralis::Window::m_Context.get());
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		ImGui::Render();


		vkWaitForFences(vkContext->device, 1, &vkContext->inFlightFences[vkContext->currentFrame], VK_TRUE, UINT64_MAX);


		VkResult result = vkAcquireNextImageKHR(vkContext->device, vkContext->swapChain, UINT64_MAX, vkContext->imageAvailableSemaphores[vkContext->currentFrame], VK_NULL_HANDLE, &vkContext->imageIndex);
		if (result == VK_ERROR_OUT_OF_DATE_KHR) {
			vkContext->recreateSwapChain();
			return;
		}
		vkResetFences(vkContext->device, 1, &vkContext->inFlightFences[vkContext->currentFrame]);
		vkResetCommandBuffer(vkContext->commandBuffers[vkContext->currentFrame], 0);
		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = 0; // Optional
		beginInfo.pInheritanceInfo = nullptr; // Optional
		MR_CORE_ASSERT(vkBeginCommandBuffer(vkContext->commandBuffers[vkContext->currentFrame], &beginInfo) == VK_SUCCESS, "Failed to record Command Buffer");
	}
	void VulkanRendererAPI::EndDraw()
	{
		VulkanContext* vkContext = static_cast<VulkanContext*>(Miralis::Window::m_Context.get());

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), vkContext->commandBuffers[vkContext->currentFrame]);
		vkCmdEndRenderPass(vkContext->commandBuffers[vkContext->currentFrame]);
		MR_CORE_ASSERT(vkEndCommandBuffer(vkContext->commandBuffers[vkContext->currentFrame]) == VK_SUCCESS, "Failed to record Command buffer")


		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

		VkSemaphore waitSemaphores[] = { vkContext->imageAvailableSemaphores[vkContext->currentFrame] };
		VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = waitSemaphores;
		submitInfo.pWaitDstStageMask = waitStages;

		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &vkContext->commandBuffers[vkContext->currentFrame];

		VkSemaphore signalSemaphores[] = { vkContext->renderFinishedSemaphores[vkContext->currentFrame] };
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = signalSemaphores;
		MR_CORE_ASSERT(vkQueueSubmit(vkContext->graphicsQueue, 1, &submitInfo, vkContext->inFlightFences[vkContext->currentFrame]) == VK_SUCCESS, "failed to submit draw command buffer");
		VkPresentInfoKHR presentInfo{};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = signalSemaphores;

		VkSwapchainKHR swapChains[] = { vkContext->swapChain };
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = swapChains;

		presentInfo.pImageIndices = &vkContext->imageIndex;

		VkResult result = vkQueuePresentKHR(vkContext->presentQueue, &presentInfo);

		if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR) {
			vkContext->recreateSwapChain();
		}
		vkContext->currentFrame = (vkContext->currentFrame + 1) % vkContext->MAX_FRAMES_IN_FLIGHT;
		// Update and Render additional Platform Windows
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
	}
}