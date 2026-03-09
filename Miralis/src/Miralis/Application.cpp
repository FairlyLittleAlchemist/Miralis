#include "Application.h"
#include "Log.h"
#include <iostream>
#include"Miralis/Rendering/RenderCommands.h"
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace Miralis {


	std::vector<float> verticesVec = {
		//   X      Y       R     G     B
		-0.5f, -0.5f,   1.0f, 0.0f, 0.0f, // Bottom-Left (Red)
		 0.5f, -0.5f,   0.0f, 1.0f, 0.0f, // Bottom-Right (Green)
		 0.5f,  0.5f,   0.0f, 0.0f, 1.0f, // Top-Right (Blue)
		-0.5f,  0.5f,   1.0f, 1.0f, 1.0f  // Top-Left (White)
	 };

	struct UniformBufferObject {
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 proj;
	};


	std::vector<uint16_t> indices = {
	   0, 1, 2, 2, 3, 0
	};

	VertexBuffer* m_vertexBuffer;	
	VertexBuffer* m_vertexBuffer1;
	UnifromBuffer* myUnifromBuffer;
	PipeLine* MyShader;
	IndexBuffer* m_indexBuffer;
	ResourceSet* myResource;

	Application* Application::s_Instance = nullptr;
	Application::Application() {
		s_Instance = this;
		Miralis::Log::Init();
		m_Window = std::unique_ptr<Window> (Window::Create());
		m_Window->SetEventClassBack(std::bind(&Application::OnEvent, this, std::placeholders::_1));
		m_Window->m_Context->Init();

		VertexLayout layout = {
			0,{
					{ShaderDataType::Float2, "inPosition"},
					{ShaderDataType::Float3, "inColor"},
				  }
		};



		ResourceSetDescription mySetDec = {SetUpdate::UpdatePerFrame , {
			{ResourceType::UnifromBuffer, 1 , "Camera", 0},
			}
		};

		myResource = myResource = ResourceSet::Create(mySetDec);
		myUnifromBuffer = UnifromBuffer::Create(sizeof(UniformBufferObject));
		myResource->UpDateSet({myUnifromBuffer});
		static auto startTime = std::chrono::high_resolution_clock::now();



		m_vertexBuffer = VertexBuffer::Create(verticesVec.data(), verticesVec.size(),  layout );
		MyShader = PipeLine::Create(    std::string(SHADER_PATH) + "/Vertex/triangle.spv",
									    std::string(SHADER_PATH) + "/Fragment/triangle.spv",
									    {layout },
										{myResource}
									);

		m_indexBuffer = IndexBuffer::Create((uint32_t*)indices.data(), (uint32_t)indices.size());
		
		
	};
	void Application::Run()
	{
		UniformBufferObject ubo{};
		
		static auto startTime = std::chrono::high_resolution_clock::now();
		while(m_Running){

		m_Window->NewFrame();
			auto currentTime = std::chrono::high_resolution_clock::now();
			float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
			ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			ubo.proj = glm::perspective(glm::radians(45.0f), 800*2 / (float) 900*2, 0.1f, 10.0f);
            ubo.proj[1][1] *= -1;
			float* dataPtr = reinterpret_cast<float*>(&ubo);

			myUnifromBuffer->UploadUnifrom(dataPtr, sizeof(ubo));


		for (Layer* layer : m_LayerStack) {
			layer->OnUpdate();
		}

		RenderCommands::BeingDraw();
		RenderCommands::SetClearDraw(glm::vec4(0.0, 0.0, 0.0, 0.1));
		MyShader->Bind();
			myResource->Bind(MyShader);
		m_vertexBuffer->Bind();
		m_indexBuffer->Bind();
		RenderCommands::DrawIndexed(indices.size());
		RenderCommands::EndDraw();

		m_Window->m_Context->SwapBuffers();
		m_Window->OnUpdate();
		}
	};
	Application::~Application() {
	}
	bool Application::OnWindwClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.pushLayer(layer);
		layer->OnAttache();
	}
	void Application::PopLayer(Layer* layer)
	{
		m_LayerStack.popLayer(layer);

	}
	;

	 
	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindwClose, this, std::placeholders::_1));
			for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
		--it;

				(*it)->OnEvent(e);
				if (e.Handeld) {
					break;
				}
			}
	}
}