#include "Checkbox.h"
#include "../Core/App.h"

using namespace Core;

Checkbox::Checkbox()
{
	clearParams();
}
Checkbox::~Checkbox()
{
	if (m_checked_ctrl != nullptr)
		delete m_checked_ctrl;

	if (m_desc != nullptr)
		delete m_desc;
	clearParams();
}
// VIRTUAL FUNCS
void Checkbox::setDesc(const char* in_value)
{
	if (m_desc != nullptr)
		m_desc->setText(in_value);
}
void Checkbox::setChecked(bool in_value)
{
	m_is_checked = in_value;
}
bool Checkbox::getChecked()
{
	return m_is_checked;
}
void Checkbox::init()
{
	m_desc = new TextObject();
	m_desc->setX(getX() + getWidth() + 10.f);
	m_desc->setY(getY() + 3.f);

	m_checked_ctrl = new BasicObject();
	m_checked_ctrl->setX(getX() + 3.f);
	m_checked_ctrl->setWidth(getWidth() - 6.f);
	m_checked_ctrl->setY(getY() + 3.f);
	m_checked_ctrl->setHeight(getHeight() - 6.f);
	m_checked_ctrl->setColor(DARKGRAY);
}
void Checkbox::draw()
{
	DrawRectangleRec(getRect(), getColor());
	DrawRectangleLinesEx(getRect(), 1, DARKGRAY);

	if (m_desc != nullptr)
		m_desc->draw();

	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		Vector2 mouse = GetMousePosition();
		if (CheckCollisionPointRec(mouse, getRect()))
			m_is_checked = !m_is_checked;
	}

	if (m_is_checked && m_checked_ctrl != nullptr)
		m_checked_ctrl->draw();
}
// FUNCS
void Checkbox::clearParams()
{
	m_is_checked = false;
	m_desc = nullptr;
	m_checked_ctrl = nullptr;
}

