#pragma once
#include "raylib.h"
#include "../Core/Object.h"

namespace Core
{
	class Checkbox : public IObject
	{
	public:
		Checkbox();
		virtual ~Checkbox();

		virtual void draw();
		virtual void init();
		virtual void setDesc(const char* in_value);
		virtual void setChecked(bool in_value);
		virtual bool getChecked();

	protected:
		bool m_is_checked;
		TextObject* m_desc;
		BasicObject* m_checked_ctrl;

	private:
		void clearParams();
	};
}
