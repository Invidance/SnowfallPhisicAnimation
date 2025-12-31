#include "raylib.h"
#include "Slider.h"
#include "../Core/App.h"

using namespace Core;

Slider::Slider()
{
	clearParams();
}
Slider::~Slider()
{
	if (m_knob != nullptr)
		delete m_knob;

	if (m_text != nullptr)
		delete m_text;

	if (m_desc != nullptr)
		delete m_desc;

	clearParams();
}
// VIRTUAL FUNCS
float Slider::getValue()
{
	return m_value;
}
float Slider::getMultiplier()
{
	return m_multiplier;
}
TextObject* Slider::getTextObject()
{
	return m_text;
}
void Slider::setDesc(const char* in_value)
{
	if (m_desc != nullptr)
		m_desc->setText(in_value);
}
void Slider::setMultiplier(float in_value)
{
	m_multiplier = in_value;
}
void Slider::init(float in_value)
{
	m_value = in_value;

	m_knob = new BasicObject();
	m_knob->setWidth(12.f);
	m_knob->setHeight(getHeight() + 6.f);
	m_knob->setColor(ORANGE);

	m_filled_back = new BasicObject();
	m_filled_back->setWidth(getWidth());
	m_filled_back->setHeight(getHeight());
	m_filled_back->setColor(getColor());

	m_text = new TextObject();
	m_text->setX(getX() + getWidth() * 0.5f);
	m_text->setY(getY() - 20.f);

	m_desc = new TextObject();
	m_desc->setX(getX());
	m_desc->setY(getY() - 20.f);
}
void Slider::draw()
{
	bool valueChanged = false;
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
	{
		Vector2 mousePos = GetMousePosition();
		if (CheckCollisionPointRec(mousePos, getRect()))
		{
			float normalized = (mousePos.x - getX()) / getWidth();

			if (normalized < 0.0f) normalized = 0.0f;
			if (normalized > 1.0f) normalized = 1.0f;

			m_value = m_min_value + normalized * (m_max_value - m_min_value);
			valueChanged = true;
		}
	}

	DrawRectangleRec(getRect(), DARKGRAY);
	if (m_filled_back != nullptr)
	{
		m_filled_back->setX(getX());
		m_filled_back->setY(getY());
		m_filled_back->setWidth(getWidth() * getValue());
		m_filled_back->draw();
	}

	if (m_knob != nullptr)
	{
		m_knob->setX(getX() + (getWidth() * m_value) - m_knob->getWidth() * 0.5f);
		m_knob->setY(getY() + getHeight() * 0.5f - m_knob->getHeight() * 0.5f);

		m_knob->draw();
	}

	if (m_text != nullptr)
	{
		m_text->setText(std::to_string(m_value * m_multiplier).c_str());
		m_text->draw();
	}

	if (m_desc != nullptr)
		m_desc->draw();
}
// FUNCS
void Slider::clearParams()
{
	m_multiplier = 1.f;
	m_value = 0.f;
	m_min_value = 0.f;
	m_max_value = 1.f;
	m_knob = nullptr;
	m_text = nullptr;
	m_desc = nullptr;
	m_filled_back = nullptr;
}

