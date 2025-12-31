#pragma once
#include "raylib.h"
#include "Core/Object.h"
#include <map>
#include <functional>

namespace Core
{
	class Canvas;
	class Slider;
	class Dropdown;
	class Checkbox;
	class Sidebar : public IObject
	{
	public:
		Sidebar();
		virtual ~Sidebar();

		virtual void draw();
		virtual void init();

		virtual void getParameter(unsigned int, double& out_value);
		virtual void updateParameter(unsigned int, double out_value);
		virtual void registerCallback(Canvas* in_canvas);

	protected:
		float m_margin;
		TextObject* m_title;
		Slider* m_duration_slider;
		Slider* m_timescale;
		Dropdown* m_type_dropdown;
		Dropdown* m_func_dropdown;
		Checkbox* m_is_draw_grid;
		Canvas* m_ref_canvas;
		std::map<unsigned int, double> m_parameters;

		virtual Vector2 getSafePos();
		virtual int getSafeX();
		virtual int getSafeY();

	private:
		void clearParams();
	};
}
