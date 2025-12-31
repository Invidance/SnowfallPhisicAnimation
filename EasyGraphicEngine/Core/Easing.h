#pragma once
#include "raylib.h"
#include "raymath.h"

namespace Core
{
	class Easing
	{
	public:
		typedef enum
		{
			LINEAR = 0,
			SINE = 1,
			QUINT = 2,
			QUART = 3,
			QUAD = 4,
			EXPO = 5,
			ELASTIC = 6,
			CUBIC = 7,
			CIRC = 8,
			BOUNCE = 9,
			BACK = 10
		}EASING_TYPE;

		typedef enum
		{
			FUNC_IN = 0,
			FUNC_OUT = 1,
			FUNC_IN_OUT = 2,
		}EASING_FUNC;

		// --- LINEAR ---
		static float linear(float t) { return t; }

		// --- SINE ---
		static float sineIn(float t) { return 1.0f - cosf(t * PI / 2.0f); }
		static float sineOut(float t) { return sinf(t * PI / 2.0f); }
		static float sineInOut(float t) { return -0.5f * (cosf(PI * t) - 1.0f); }

		// --- QUAD ---
		static float quadIn(float t) { return t * t; }
		static float quadOut(float t) { return t * (2.0f - t); }
		static float quadInOut(float t) { return t < 0.5f ? 2.0f * t * t : -1.0f + (4.0f - 2.0f * t) * t; }

		// --- CUBIC ---
		static float cubicIn(float t) { return t * t * t; }
		static float cubicOut(float t) { return (--t) * t * t + 1.0f; }
		static float cubicInOut(float t) { return t < 0.5f ? 4.0f * t * t * t : (t - 1.0f) * (2.0f * t - 2.0f) * (2.0f * t - 2.0f) + 1.0f; }

		// --- QUART ---
		static float quartIn(float t) { return t * t * t * t; }
		static float quartOut(float t) { return 1.0f - (--t) * t * t * t; }
		static float quartInOut(float t) { return t < 0.5f ? 8.0f * t * t * t * t : 1.0f - 8.0f * (--t) * t * t * t; }

		// --- QUINT ---
		static float quintIn(float t) { return t * t * t * t * t; }
		static float quintOut(float t) { return 1.0f + (--t) * t * t * t * t; }
		static float quintInOut(float t) { return t < 0.5f ? 16.0f * t * t * t * t * t : 1.0f + 16.0f * (--t) * t * t * t * t; }

		// --- EXPO ---
		static float expoIn(float t) { return (t == 0.0f) ? 0.0f : powf(2.0f, 10.0f * (t - 1.0f)); }
		static float expoOut(float t) { return (t == 1.0f) ? 1.0f : 1.0f - powf(2.0f, -10.0f * t); }
		static float expoInOut(float t) {
			if (t == 0.0f || t == 1.0f) return t;
			if ((t *= 2.0f) < 1.0f) return 0.5f * powf(2.0f, 10.0f * (t - 1.0f));
			return 0.5f * (2.0f - powf(2.0f, -10.0f * (t - 1.0f)));
		}

		// --- CIRC ---
		static float circIn(float t) { return 1.0f - sqrtf(1.0f - t * t); }
		static float circOut(float t) { return sqrtf(1.0f - (--t) * t); }
		static float circInOut(float t) {
			if ((t *= 2.0f) < 1.0f) return -0.5f * (sqrtf(1.0f - t * t) - 1.0f);
			return 0.5f * (sqrtf(1.0f - (t -= 2.0f) * t) + 1.0f);
		}

		// --- BACK ---
		static float backIn(float t) { const float s = 1.70158f; return t * t * ((s + 1.0f) * t - s); }
		static float backOut(float t) { const float s = 1.70158f; return (--t) * t * ((s + 1.0f) * t + s) + 1.0f; }
		static float backInOut(float t) {
			float s = 1.70158f * 1.525f;
			if ((t *= 2.0f) < 1.0f) return 0.5f * (t * t * ((s + 1.0f) * t - s));
			return 0.5f * ((t -= 2.0f) * t * ((s + 1.0f) * t + s) + 2.0f);
		}

		// --- ELASTIC ---
		static float elasticIn(float t) {
			if (t == 0.0f || t == 1.0f) return t;
			return -powf(2.0f, 10.0f * (t - 1.0f)) * sinf((t - 1.1f) * 5.0f * PI);
		}
		static float elasticOut(float t) {
			if (t == 0.0f || t == 1.0f) return t;
			return powf(2.0f, -10.0f * t) * sinf((t - 0.1f) * 5.0f * PI) + 1.0f;
		}
		static float elasticInOut(float t) {
			if (t == 0.0f || t == 1.0f) return t;
			t *= 2.0f;
			if (t < 1.0f) return -0.5f * powf(2.0f, 10.0f * (t - 1.0f)) * sinf((t - 1.1f) * 5.0f * PI);
			return 0.5f * powf(2.0f, -10.0f * (t - 1.0f)) * sinf((t - 1.1f) * 5.0f * PI) + 1.0f;
		}

		// --- BOUNCE ---
		static float bounceOut(float t) {
			if (t < (1.0f / 2.75f)) return 7.5625f * t * t;
			else if (t < (2.0f / 2.75f)) return 7.5625f * (t -= (1.5f / 2.75f)) * t + 0.75f;
			else if (t < (2.5f / 2.75f)) return 7.5625f * (t -= (2.25f / 2.75f)) * t + 0.9375f;
			return 7.5625f * (t -= (2.625f / 2.75f)) * t + 0.984375f;
		}
		static float bounceIn(float t) { return 1.0f - bounceOut(1.0f - t); }
		static float bounceInOut(float t) {
			return t < 0.5f ? bounceIn(t * 2.0f) * 0.5f : bounceOut(t * 2.0f - 1.0f) * 0.5f + 0.5f;
		}

		static float get(EASING_TYPE in_type, EASING_FUNC in_func, float in_v);
		static void interpolate(Vector2 from_v, Vector2 to_v, Vector2& out_v, float in_t);
	};
}
	