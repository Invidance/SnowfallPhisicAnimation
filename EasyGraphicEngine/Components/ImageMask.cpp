#include "stdafx.h"
#include "ImageMask.h"
#include "../Core/App.h"

using namespace Core;

ImageMask::ImageMask()
{
	clearParams();
}
ImageMask::~ImageMask()
{
	clearParams();
}
// VIRTUAL FUNCS
void ImageMask::init(const char* in_text, int in_font_size)
{
	m_mask_image = GenImageColor((int)getWidth(), (int)getHeight(), BLANK);
	
	ImageDrawTextEx(&m_mask_image, *Application::m_instance->getFont(), in_text, { getWidth() / 2.f - MeasureTextEx(*Application::m_instance->getFont(), in_text, (float)in_font_size, 2).x / 2.f, getHeight() / 2 - in_font_size / 2 }, (float)in_font_size, 2, WHITE);

	m_mask_texture = LoadTextureFromImage(m_mask_image);

	m_pixels = LoadImageColors(m_mask_image);
}

void ImageMask::unloadTextures()
{
	UnloadImage(m_mask_image);
	UnloadTexture(m_mask_texture);
	UnloadImageColors(m_pixels);
}
void ImageMask::draw()
{
	DrawTexturePro(m_mask_texture, { 0.0f, 0.0f, (float)m_mask_texture.width, (float)m_mask_texture.height }, getRect(), { 0.f, 0.f }, 0.f, getColor());
}
bool ImageMask::isPixelSolid(Vector2 in_pos)
{
	in_pos -= getPos();
	in_pos.x = float((int)in_pos.x);
	in_pos.y = float((int)in_pos.y);
	if (in_pos.x < 0 || in_pos.x >= getWidth() || in_pos.y < 0 || in_pos.y >= getHeight())
		return false;
	
	return m_pixels[int(in_pos.y * getWidth()) + (int)in_pos.x].a > 100;
}
// FUNCS
void ImageMask::clearParams()
{
	m_pixels = nullptr;
}

