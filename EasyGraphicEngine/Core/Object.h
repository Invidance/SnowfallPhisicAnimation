#pragma once
#include "raylib.h"
#include <string>

namespace Core
{
	class IObject
	{
	public:
		virtual Rectangle getRect();
		virtual Color getColor();
		virtual void setColor(Color in_color);

		virtual float getX();
		virtual void setX(float in_value);
		virtual float getY();
		virtual void setY(float in_value);

		virtual Vector2 getPos();

		virtual float getWidth();
		virtual void setWidth(float in_value);
		virtual float getHeight();
		virtual void setHeight(float in_value);

		virtual void draw() = 0;
		virtual void destroy();

	protected:
		IObject();
		virtual ~IObject();

		float m_x;
		float m_y;
	
		float m_width;
		float m_height;

		Color m_color;

	private:
		void clearParams();
	};

	class BasicObject : public IObject
	{
	public:
		BasicObject();
		virtual ~BasicObject();

		virtual void draw();
		virtual void setBorderSize(float in_value);
		virtual void setRadius(float in_value);
		virtual void setTexture(Texture2D* in_texture);

	protected:
		Texture2D* m_texture;
		float m_border_size;
		float m_radius;

	private:
		void clearParams();
	};

	class TextObject : public IObject
	{
	public:
		TextObject();
		virtual ~TextObject();

		virtual const char* getText();
		virtual void setText(const char*);

		virtual int getFontSize();
		virtual void setFontSize(int in_value);

		virtual void draw();

	protected:
		int m_font_size;
		std::string m_text;

	private:
		void clearParams();
	};
}