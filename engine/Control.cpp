#include "Control.h"

void GLAPIENTRY
MessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
}

Control::~Control()
{
	delete(m_WINDOW);
	delete(m_RENDERER);
}

const unsigned char* Control::GetVersion()
{
	return glGetString(GL_VERSION);
}

bool Control::GetWindowOpen()
{
	return m_WINDOW->WindowOpen();
}

void Control::WindowClose()
{
	m_WINDOW->Terminate();
}

int Control::GetWindowWidth()
{
	return m_WINDOW->getWidth();
}

int Control::GetWindowHeight()
{
	return m_WINDOW->getHeight();
}

void Control::SetWindowWidth(int width)
{
}

void Control::SetWindowHeight(int height)
{
}

bool Control::GetWindowBlending()
{
	return false;
}

void Control::SetWindowBlending(bool blending)
{
	m_WINDOW->SetBlending(blending);
}

int Control::GetRenderedObjCount()
{
	return 0;
}

void Control::WindowClear(Color color)
{
	m_WINDOW->Clear(color);
}

void Control::RenderClear()
{
	m_RENDERER->Clear();
}

void Control::Update()
{
	m_WINDOW->SwapBuffers();
	m_WINDOW->PollEvents();
}

void Control::EnableDebug()
{
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);
}

void Control::AddRender(Renderable& renderable)
{
}
