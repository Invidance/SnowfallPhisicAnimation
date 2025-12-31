#pragma once
#include "raylib.h"
#include "Core/Easing.h"
#include "Core/Object.h"
#include <vector>

namespace Core
{
	class Sidebar;
	class ParticleSystem;
	class Canvas : public IObject
	{
	public:
		Canvas();
		virtual ~Canvas();

		virtual void draw();
		virtual void init();
		virtual void refreshParameters();

	protected:
		struct FlyData
		{
			FlyData();

			Vector2 m_pos;
			float m_scale;
		};

		double m_time;
		double m_duration;
		Easing::EASING_FUNC m_func;
		Easing::EASING_TYPE m_type;
		bool m_is_pressed;
		bool m_is_draw_grid;
		FlyData m_prev_data;
		FlyData m_next_data;

		Sidebar* m_sidebar;
		BasicObject* m_ctrl;
		TextObject* m_title;
		ParticleSystem* m_particle_system;
		Camera2D m_camera;
		std::vector<TextObject> m_legends;

		void drawGrid();
		void update();
	private:
		void clearParams();
	};
}
