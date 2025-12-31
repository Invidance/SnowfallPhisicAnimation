#pragma once
#include "raylib.h"
#include "../Core/Object.h"
#include <map>
#include <string>

namespace Core
{
	class Dropdown : public IObject
	{
	public:
		Dropdown();
		virtual ~Dropdown();

		virtual void draw();
		virtual void init();
		virtual void setDesc(const char* in_value);
		virtual unsigned int getOption();

		virtual void updateOption(unsigned int key, std::string value);

	protected:
		bool m_is_opened;
		TextObject* m_desc;
		TextObject* m_option_text;
		unsigned int m_selected;
		std::map<unsigned int, std::string> m_options;

	private:
		void clearParams();
	};
}
