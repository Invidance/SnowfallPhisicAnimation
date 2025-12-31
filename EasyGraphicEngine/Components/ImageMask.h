#pragma once
#include "raylib.h"
#include "../Core/Object.h"

namespace Core
{
	class ImageMask : public IObject
	{
	public:
		ImageMask();
		virtual ~ImageMask();

		virtual void init(const char* in_text, int in_font_size);
		virtual void unloadTextures();
		virtual bool isPixelSolid(Vector2 in_pos);

		virtual void draw();

	protected:
		Image m_mask_image;
		Texture2D m_mask_texture;
		Color* m_pixels;

	private:
		void clearParams();
	};
}
