#pragma once
#include "raylib.h"
#include <vector>

namespace Core
{
	class IObject;
	class Application
	{
	public:
		Application();
		virtual ~Application();

		static Application* m_instance;

		virtual Font* getFont();
		virtual void draw();
		virtual void init();

		virtual void registerObject(IObject* in_obj);
		virtual void unregisterObject(IObject* in_obj);
		virtual const std::vector<IObject*>& getRegisteredObjects();
	protected:
		Font m_font;
		bool m_active;
		std::vector<IObject*> m_objects;

	private:
		void clearParams();
	};
}