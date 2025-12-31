#include "App.h"
#include "Object.h"

using namespace Core;

Application* Application::m_instance = nullptr;
Application::Application()
{
	UnloadFont(m_font);

	m_instance = this;
	clearParams();
}
Application::~Application()
{
	m_active = false;
	if (m_instance == this)
		m_instance = nullptr;
	
	for (auto v : m_objects)
		v->destroy();
	
	m_objects.clear();

	clearParams();
}
// VIRTUAL FUNCS
Font* Application::getFont()
{
	return &m_font;
}
void Application::draw()
{
	for (size_t i = 0; i < m_objects.size(); i++)
	{
		m_objects[i]->draw();
	}
}
void Application::registerObject(IObject* in_obj)
{
	m_objects.push_back(in_obj);
}
void Application::unregisterObject(IObject* in_obj)
{
	if (!m_active)
		return;

	auto it = m_objects.begin();
	for (; it != m_objects.end(); ++it)
	{
		if (*it == in_obj)
		{
			m_objects.erase(it);
			return;
		}
	}
}
const std::vector<IObject*>& Application::getRegisteredObjects()
{
	return m_objects;
}
void Application::init()
{
	m_font = LoadFontEx("res/Roboto-Bold.ttf", 64, 0, 0);
	SetTextureFilter(m_font.texture, TEXTURE_FILTER_BILINEAR);
}

// FUNCS
void Application::clearParams()
{
	m_active = true;
}