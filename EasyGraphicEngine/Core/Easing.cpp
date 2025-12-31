#include "Easing.h"
#include "raymath.h"

using namespace Core;

float Easing::get(EASING_TYPE in_type, EASING_FUNC in_func, float in_v)
{
	in_v = Clamp(in_v, 0.f, 1.f);
	if (in_type == LINEAR)
		return linear(in_v);

	if(in_func == FUNC_IN)
	{
		if (in_type == SINE) return sineIn(in_v);
		if (in_type == QUINT) return quintIn(in_v);
		if (in_type == QUART) return quartIn(in_v);
		if (in_type == QUAD) return quadIn(in_v);
		if (in_type == EXPO) return expoIn(in_v);
		if (in_type == ELASTIC) return elasticIn(in_v);
		if (in_type == CUBIC) return cubicIn(in_v);
		if (in_type == CIRC) return circIn(in_v);
		if (in_type == BOUNCE) return bounceIn(in_v);
		if (in_type == BACK) return backIn(in_v);
	}

	if (in_func == FUNC_OUT)
	{
		if (in_type == SINE) return sineOut(in_v);
		if (in_type == QUINT) return quintOut(in_v);
		if (in_type == QUART) return quartOut(in_v);
		if (in_type == QUAD) return quadOut(in_v);
		if (in_type == EXPO) return expoOut(in_v);
		if (in_type == ELASTIC) return elasticOut(in_v);
		if (in_type == CUBIC) return cubicOut(in_v);
		if (in_type == CIRC) return circOut(in_v);
		if (in_type == BOUNCE) return bounceOut(in_v);
		if (in_type == BACK) return backOut(in_v);
	}

	if (in_func == FUNC_IN_OUT)
	{
		if (in_type == SINE) return sineInOut(in_v);
		if (in_type == QUINT) return quintInOut(in_v);
		if (in_type == QUART) return quartInOut(in_v);
		if (in_type == QUAD) return quadInOut(in_v);
		if (in_type == EXPO) return expoInOut(in_v);
		if (in_type == ELASTIC) return elasticInOut(in_v);
		if (in_type == CUBIC) return cubicInOut(in_v);
		if (in_type == CIRC) return circInOut(in_v);
		if (in_type == BOUNCE) return bounceInOut(in_v);
		if (in_type == BACK) return backInOut(in_v);
	}

	return linear(in_v);
}

void Easing::interpolate(Vector2 from_v, Vector2 to_v, Vector2& out_v, float in_t)
{
	in_t = Clamp(in_t, 0.f, 1.f);

	out_v.x = from_v.x + (to_v.x - from_v.x) * in_t;
	out_v.y = from_v.y + (to_v.y - from_v.y) * in_t;
}