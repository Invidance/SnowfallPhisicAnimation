#include "stdafx.h"
#include "Particle.h"
#include "Components/ImageMask.h"
#include "Core/Object.h"

using namespace Core;

// ============ Emmiter ===========
Emmiter::Emmiter()
{
	clearParams();
}
Emmiter::~Emmiter()
{
	clearParams();
}
// VIRTUAL FUNCS
void Emmiter::update(float dt)
{
	if (m_lifetime <= 0.001f || m_ref_particle == nullptr)
	{
		finish();
		return;
	}

	if (m_is_stacked)
		return;

	m_velocity.x += m_ref_particle->m_gravity.x * dt;
	m_velocity.y += m_ref_particle->m_gravity.y * dt;

	m_pos.x += m_velocity.x * dt;
	m_pos.y += m_velocity.y * dt;

	m_time += dt;

	float t = m_time / m_lifetime;

	Vector2 new_pos;
	new_pos.x = m_pos.x + (float)cos(t * m_ref_particle->m_vibration_speed) * m_ref_particle->m_vibration_dt;
	new_pos.y = m_pos.y + (float)sin(t * m_ref_particle->m_vibration_speed) * m_ref_particle->m_vibration_dt;

	if (m_ref_particle->m_image_mask != nullptr)
	{
		bool prev_res = m_ref_particle->m_image_mask->isPixelSolid(m_prev_pos);
		bool new_res = m_ref_particle->m_image_mask->isPixelSolid(new_pos);
		if (new_res && prev_res != new_res)
		{
			int v = GetRandomValue(0, 100);
			if (v > 50)
			{
				m_is_stacked = true;
				m_velocity = { 0.f, 0.f };
			}
		}
	}

	if (m_render_target != nullptr)
	{
		m_render_target->setX(new_pos.x);
		m_render_target->setY(new_pos.y);
	}

	m_prev_pos = new_pos;

	if (t >= 1.f)
		finish();
}
void Emmiter::draw()
{
	if (m_render_target != nullptr)
		m_render_target->draw();
}
void Emmiter::start()
{
	m_time = 0.f;
	m_is_complete = false;
	if (m_render_target == nullptr)
		m_render_target = new BasicObject();

	if (m_ref_particle != nullptr)
		m_render_target->setTexture(&m_ref_particle->m_texture);
	m_render_target->setWidth(4.f);
	m_render_target->setHeight(4.f);
}
void Emmiter::finish()
{
	m_is_complete = true;
}
// FUNCS
void Emmiter::clearParams()
{
	m_is_stacked = false;
	m_is_complete = false;
	m_render_target = nullptr;
	m_ref_particle = nullptr;
	m_time = 0.f;
	m_lifetime = 0.f;
	m_pos.x = 0.f;
	m_pos.y = 0.f;
}

// ============ ParticleSystem ===========
ParticleSystem::ParticleSystem()
{
	clearParams();
}
ParticleSystem::~ParticleSystem()
{
	clearParams();
}
// VIRTUAL FUNCS
void ParticleSystem::draw()
{
	if (!m_is_started)
		return;

	if(m_image_mask != nullptr)
		m_image_mask->draw();

	float dt = GetFrameTime() * m_time_scale;
	auto it = m_emiters.begin();
	for (; it != m_emiters.end(); ++it)
	{
		(*it)->update(dt);
		if ((*it)->m_is_complete)
			m_emiters_pool.push_back((*it));
		else
			(*it)->draw();
	}

	m_emiters.erase(std::remove_if(m_emiters.begin(), m_emiters.end(),
		[](Emmiter* e) { return e->m_is_complete; }), m_emiters.end());

	m_timer += dt;
	if (m_timer > m_spawn_rate)
	{
		m_timer = 0.f;
		createEmmiter();
	}
}
void ParticleSystem::start()
{
	m_image_mask = new ImageMask();
	m_image_mask->setX(-600.f);
	m_image_mask->setY(-100.f);
	m_image_mask->setWidth((float)1200.f);
	m_image_mask->setHeight((float)200.f);
	m_image_mask->setColor({255,255,255,0});
	m_image_mask->init("Let it snow", 200);

	m_is_started = true;
	for (int i = 0; i < m_start_emiter_count; i += 1)
		createEmmiter(true);
}
void ParticleSystem::finish()
{

}
void ParticleSystem::createEmmiter(bool in_is_simulated /* = false */)
{
	Emmiter* emiter = nullptr;
	if (m_emiters_pool.size() > 0)
	{
		emiter = m_emiters_pool.front();
		m_emiters_pool.erase(m_emiters_pool.begin());
	}
	else
		emiter = new Emmiter();

	emiter->m_lifetime = m_lifetime;
	emiter->m_velocity = m_initial_force + m_initial_force * (GetRandomValue(-(int)m_random_force_prc, (int)m_random_force_prc) / 100.f);
	emiter->m_ref_particle = this;
	emiter->m_pos.x = (float)GetRandomValue((int)m_create_range.x, (int)(m_create_range.x + m_create_range.width));
	emiter->m_pos.y = (float)GetRandomValue((int)m_create_range.y, (int)(m_create_range.y + m_create_range.height));
	emiter->start();
	if (m_colors.size() > 0 && emiter->m_render_target != nullptr)
	{
		Color c = m_colors[GetRandomValue(0, (int)m_colors.size() - 1)];
		emiter->m_render_target->setColor(c);
	}

	if (in_is_simulated)
	{
		float t = GetRandomValue(0, int(emiter->m_lifetime * 100.f)) / 100.f;
		emiter->update(t);
	}

	m_emiters.push_back(emiter);
}
// FUNCS
void ParticleSystem::clearParams()
{
	m_timer = 0.f;
	m_is_started = false;
	m_image_mask = nullptr;
	m_spawn_rate = 1.f;
	m_lifetime = 3.f;
	m_create_range.x = 0.f;
	m_create_range.y = 0.f;
	m_random_force_prc = 0.f;
	m_vibration_dt = 0.f;
	m_vibration_speed = 1.f;
	m_gravity.y = 9.8f;
	m_start_emiter_count = 0;
	m_time_scale = 2.f;
}