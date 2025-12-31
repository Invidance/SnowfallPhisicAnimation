#include "Dropdown.h"
#include "../Core/App.h"

using namespace Core;

Dropdown::Dropdown()
{
	clearParams();
}
Dropdown::~Dropdown()
{
	clearParams();
}
// VIRTUAL FUNCS
unsigned int Dropdown::getOption()
{
	return m_selected;
}
void Dropdown::setDesc(const char* in_value)
{
	if (m_desc != nullptr)
		m_desc->setText(in_value);
}
void Dropdown::updateOption(unsigned int key, std::string value)
{
	m_options[key] = value;
}
void Dropdown::init()
{
	m_desc = new TextObject();
	m_desc->setX(getX());
	m_desc->setY(getY() - 20.f);

	m_option_text = new TextObject();
	m_option_text->setX(getX() + 10.f);
	m_option_text->setY(getY() + getHeight() * 0.22f);
	m_option_text->setFontSize(18);
}
void Dropdown::draw()
{
	DrawRectangleRec(getRect(), getColor());
	DrawRectangleLinesEx(getRect(), 1, DARKGRAY);

	if (m_desc != nullptr)
		m_desc->draw();

	if (m_selected < m_options.size())
		m_option_text->setText(m_options[m_selected].c_str());

	if (m_option_text)
		m_option_text->draw();

	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		Vector2 mouse = GetMousePosition();

		if (m_is_opened)
		{
			for (int i = 0; i < m_options.size(); i++)
			{
				Rectangle itemRect = { getX(), getY() + (i + 1) * getHeight(), getWidth(), getHeight() };
				if (CheckCollisionPointRec(mouse, itemRect)) 
				{
					m_selected = i;
					m_is_opened = false;
				}
			}
		}
		else 
		{
			if (CheckCollisionPointRec(mouse, getRect()))
				m_is_opened = true;
		}
	}

	if (m_is_opened)
	{
		for (int i = 0; i < m_options.size(); i++)
		{
			Rectangle itemRect = { getX(), getY() + (i + 1) * getHeight(), getWidth(), getHeight() };

			Color bgColor = WHITE;
			if (CheckCollisionPointRec(GetMousePosition(), itemRect)) bgColor = BLUE;

			DrawRectangleRec(itemRect, bgColor);
			DrawRectangleLinesEx(itemRect, 1, LIGHTGRAY);
			Vector2 v = { float(itemRect.x + 10.f), float(itemRect.y + 4.f) };
			DrawTextEx(*Application::m_instance->getFont(), m_options[i].c_str(), v, 18, 18 / 10.f, BLACK);
		}
	}
}
// FUNCS
void Dropdown::clearParams()
{
	m_is_opened = false;
	m_selected = 0;
	m_desc = nullptr;
	m_option_text = nullptr;
}

