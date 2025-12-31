#include "stdafx.h"
#include "raylib.h"
#include "Canvas.h"
#include "Sidebar.h"
#include "Particle.h"
#include "Core/App.h"

using namespace Core;

Canvas::FlyData::FlyData()
{
	m_scale = 1.f;
	m_pos.x = 0.f;
	m_pos.y = 0.f;
}
Canvas::Canvas()
{
	clearParams();
}
Canvas::~Canvas()
{
	if (m_title != nullptr)
		delete m_title;

	if (m_ctrl != nullptr)
		delete m_ctrl;

	if (m_particle_system != nullptr)
	{
		UnloadTexture(m_particle_system->m_texture);
		delete m_particle_system;
	}

	clearParams();
}
// VIRTUAL FUNCS
void Canvas::init()
{
	m_camera.target.x = 0.f;
	m_camera.target.y = 0.f;
	m_camera.offset.x = getWidth() / 2.f;
	m_camera.offset.y = getHeight() / 2.f;
	m_camera.rotation = 0.f;
	m_camera.zoom = 1.f;

	m_title = new TextObject();
	m_title->setText("Simulation View");
	m_title->setX(getX() + 10.f);
	m_title->setY(getY() + 10.f);
	m_title->setColor(RAYWHITE);
	m_title->setFontSize(20);

	/*m_ctrl = new BasicObject();
	m_ctrl->setRadius(15.f);
	m_ctrl->setColor(MAGENTA);*/

	m_particle_system = new ParticleSystem();
	m_particle_system->m_create_range.x = -getWidth();
	m_particle_system->m_create_range.width = getWidth() * 2.f;
	m_particle_system->m_create_range.y = getHeight() * -0.5f;
	m_particle_system->m_create_range.height = 0.f;
	m_particle_system->m_spawn_rate = 0.03f;
	m_particle_system->m_lifetime = 20.f;
	m_particle_system->m_initial_force.x = 40.f;
	m_particle_system->m_initial_force.y = 110.f;
	m_particle_system->m_random_force_prc = 50.f;
	m_particle_system->m_gravity.x = 0.f;
	m_particle_system->m_gravity.y = 1.5f;
	m_particle_system->m_vibration_dt = 10.f;
	m_particle_system->m_vibration_speed = 35.f;
	m_particle_system->m_start_emiter_count = 150;
	m_particle_system->m_texture = LoadTexture("res/images/snowflake.png");

	m_particle_system->m_colors.push_back({ 255, 255, 255, 255 });
	m_particle_system->m_colors.push_back({ 207, 195, 255, 255 });
	m_particle_system->m_colors.push_back({ 195, 213, 255, 255 });
	m_particle_system->m_colors.push_back({ 233, 239, 255, 255 });
	
	m_particle_system->start();
}
void Canvas::draw()
{
	if (m_sidebar == nullptr)
	{
		const std::vector<IObject*>& objs = Application::m_instance->getRegisteredObjects();
		for (auto obj : objs)
		{
			m_sidebar = dynamic_cast<Sidebar*>(obj);
			if (m_sidebar != nullptr)
				break;
		}
	}

	BeginScissorMode((int)getX(), (int)getY(), (int)getWidth(), (int)getHeight());

	ClearBackground({0,0,0,255});

	BeginMode2D(m_camera);

	//if(m_is_draw_grid)
	//	drawGrid();

	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
	{
		if(!m_is_pressed)
		{
			m_is_pressed = true;
			Vector2 mousePos = GetMousePosition();
			if (CheckCollisionPointRec(mousePos, getRect()))
			{
				Vector2 normalized = { mousePos.x - getX() - getWidth() / 2.f, mousePos.y - getY() - getHeight() / 2.f };
				m_next_data.m_pos = normalized;

				refreshParameters();

				if (m_ctrl != nullptr)
				{
					if (m_duration > 0.01f)
					{
						m_prev_data.m_pos = m_ctrl->getPos();
						m_time = 0.f;
					}
					else
					{
						m_ctrl->setX(normalized.x);
						m_ctrl->setY(normalized.y);
					}
				}
			}
		}
	}
	else
		m_is_pressed = false;

	update();

	if (m_ctrl != nullptr)
		m_ctrl->draw();

	if (m_particle_system != nullptr)
		m_particle_system->draw();

	EndMode2D();

	DrawRectangleLinesEx(getRect(), 2, BLACK);
	
	if (m_title != nullptr)
		m_title->draw();

	EndScissorMode();
}
void Canvas::drawGrid()
{
	int step = 50;
	int gridSize = (int)(getWidth() / step) * step;
	
	for (int i = -gridSize; i <= gridSize; i += step)
	{
		if(i == 0)
			continue;

		DrawLine(i, -gridSize, i, gridSize, GRAY);
		DrawLine(-gridSize, i, gridSize, i, GRAY);
	}

	DrawLine(0, -gridSize, 0, gridSize, GREEN);
	DrawLine(-gridSize, 0, gridSize, 0, RED);
}
void Canvas::update()
{
	if (m_ctrl == nullptr)
		return;

	if (m_time >= m_duration)
		return;

	float dt = GetFrameTime();
	m_time += dt;
	float t = float(m_time / m_duration);

	Vector2 pos;
	Easing::interpolate(m_prev_data.m_pos, m_next_data.m_pos, pos, Easing::get(m_type, m_func, t));
	m_ctrl->setX(pos.x);
	m_ctrl->setY(pos.y);
}
void Canvas::refreshParameters()
{
	if (m_sidebar != nullptr)
	{
		m_sidebar->getParameter(CONSTS::PARAMETER_DURATION, m_duration);
		double v = 0;
		m_sidebar->getParameter(CONSTS::PARAMETER_TWEEN_FUNC, v);
		m_func = (Easing::EASING_FUNC)(int)v;

		m_sidebar->getParameter(CONSTS::PARAMETER_TWEEN_TYPE, v);
		m_type = (Easing::EASING_TYPE)(int)v;

		m_sidebar->getParameter(CONSTS::PARAMETER_SHOW_GRID, v);
		m_is_draw_grid = (bool)(int)v;

		m_sidebar->getParameter(CONSTS::PARAMETER_TIMESCALE, v);
		m_particle_system->m_time_scale = (float)v;
	}
}
// FUNCS
void Canvas::clearParams()
{
	m_sidebar = nullptr;
	m_title = nullptr;
	m_ctrl = nullptr;
	m_particle_system = nullptr;
	m_is_pressed = false;
	m_is_draw_grid = false;
	m_time = 0.f;
	m_duration = 0.f;
	m_func = Easing::FUNC_IN;
	m_type = Easing::LINEAR;
}

