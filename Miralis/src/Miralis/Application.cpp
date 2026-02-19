#include "Application.h"
#include "Log.h"
#include <iostream>
#include"Miralis/Rendering/RenderCommands.h"
namespace Miralis {

	std::vector<float> verticesVec = {
		0.0f, -0.5f,  1.0f, 0.0f, 0.0f,
		0.5f, 0.5f,   0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f,   0.0f, 0.0f, 1.0f
	};


	std::vector<uint16_t> indices = {
	   0, 1, 2, 2, 3, 0
	};

	VertexBuffer* m_vertexBuffer;	
	VertexBuffer* m_vertexBuffer1;

	PipeLine* MyShader;
	IndexBuffer* m_indexBuffer;
	  

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
	
		ResourceSet* myResource = ResourceSet::Create(mySetDec);

		m_vertexBuffer = VertexBuffer::Create(verticesVec.data(), verticesVec.size(),  layout );

		MyShader = PipeLine::Create(std::string("../Miralis/src/Miralis/Shaders/Compiled/Vertex/triangle.spv"),
									std::string("../Miralis/src/Miralis/Shaders/Compiled/Fragment/triangle.spv"), 
									{ layout }
									);

		m_indexBuffer = IndexBuffer::Create((uint32_t*)indices.data(), (uint32_t)indices.size());
		
		
	};
	void Application::Run()
	{
		

		while(m_Running){

		m_Window->NewFrame();


		for (Layer* layer : m_LayerStack) {
			layer->OnUpdate();
		}

		RenderCommands::BeingDraw();
		RenderCommands::SetClearDraw(glm::vec4(0.0, 0.0, 0.0, 0.1));
		MyShader->Bind();
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
				(*it)->OnEvent(e);
				if (e.Handeld) {
					break;
				}
			}
	}
}