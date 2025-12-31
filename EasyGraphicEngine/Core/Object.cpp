#include "Object.h"
#include "App.h"

using namespace Core;

IObject::IObject()
{
	clearParams();
}
IObject::~IObject()
{
	clearParams();
}
// VIRTUAL FUNCS
Rectangle IObject::getRect()
{
	Rectangle rect = {m_x, m_y, m_width, m_height};
	return rect;
}
Color IObject::getColor()
{
	return m_color;
}
void IObject::setColor(Color in_color)
{
	m_color = in_color;
}
float IObject::getWidth()
{
	return m_width;
}
void IObject::setWidth(float in_value)
{
	m_width = in_value;
}
float IObject::getHeight()
{
	return m_height;
}
void IObject::setHeight(float in_value)
{
	m_height = in_value;
}
float IObject::getX()
{
	return m_x;
}
void IObject::setX(float in_value)
{
	m_x = in_value;
}
float IObject::getY()
{
	return m_y;
}
void IObject::setY(float in_value)
{
	m_y = in_value;
}
Vector2 IObject::getPos()
{
	return { getX(), getY() };
}
void IObject::destroy()
{
	delete this;
}
// FUNCS
void IObject::clearParams()
{
	m_x = 0.f;
	m_y = 0.f;
	m_width = 0.f;
	m_height = 0.f;
}

// ============ BaseObject ===========
BasicObject::BasicObject()
{
	clearParams();
}
BasicObject::~BasicObject()
{
	clearParams();
}
// VIRTUAL FUNCS
void BasicObject::draw()
{
	if (m_texture != nullptr)
	{
		Rectangle source = { 0.0f, 0.0f, (float)m_texture->width, (float)m_texture->height };

		DrawTexturePro(*m_texture, source, getRect(), { getWidth() * 0.5f, getHeight() * 0.5f }, 0.f, getColor());
	}
	else
	if (m_radius > 0.001f)
	{
		DrawCircleV(getPos(), m_radius, getColor());
		if (m_border_size > 0)
			DrawCircleLinesV(getPos(), m_radius + m_border_size, DARKGRAY);
	}
	else
	{
		DrawRectangleRec(getRect(), getColor());
		if (m_border_size > 0)
			DrawRectangleLinesEx(getRect(), m_border_size, DARKGRAY);
	}
}
void BasicObject::setBorderSize(float in_value)
{
	m_border_size = in_value;
}
void BasicObject::setRadius(float in_value)
{
	m_radius = in_value;
}
void BasicObject::setTexture(Texture2D* in_texture)
{
	m_texture = in_texture;
}
// FUNCS
void BasicObject::clearParams()
{
	m_border_size = 0.f;
	m_radius = 0.f;
	m_texture = nullptr;
}

// ============ TextObject ===========
TextObject::TextObject()
{
	clearParams();
}
TextObject::~TextObject()
{
	clearParams();
}
// VIRTUAL FUNCS
const char* TextObject::getText()
{
	return m_text.c_str();
}
void TextObject::setText(const char* in_value)
{
	m_text = in_value;
}
int TextObject::getFontSize()
{
	return m_font_size;
}
void TextObject::setFontSize(int in_value)
{
	m_font_size = in_value;
}
void TextObject::draw()
{
	if (!m_text.empty())
	{
		DrawTextEx(*Application::m_instance->getFont(), m_text.c_str(), getPos(), (float)m_font_size, m_font_size / 10.f, getColor());
	}
}
// FUNCS
void TextObject::clearParams()
{
	m_font_size = 20;
	setColor(DARKGRAY);
}