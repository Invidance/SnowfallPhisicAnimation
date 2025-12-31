#pragma once
#include "Core/App.h"

namespace Core
{
	class SnowfallApp : public Application
	{
	public:
		SnowfallApp();
		virtual ~SnowfallApp();

		virtual void init();

	protected:

	private:
		void clearParams();
	};
}