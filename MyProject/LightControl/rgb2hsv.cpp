#include <math.h>

#include "rgb2hsv.h"

static bool float_equal(float x1, float x2)
{
	return fabs(x1 - x2) < 0.01f;
}

HSV rgb2hsv(const RGB& rgb)
{
	float _R = rgb.r / 255.0f;
	float _G = rgb.g / 255.0f;
	float _B = rgb.b / 255.0f;

	float CMax = fmax(fmax(_R, _G), _B);
	float CMin = fmin(fmin(_R, _G), _B);
	float delta = CMax - CMin;

	int h = 0;

	if (float_equal(delta, 0))
		h = 0;

	else if (float_equal(CMax, _R))
		h = 60 * (((_G - _B) / delta));
	else if (float_equal(CMax, _G))
		h = 60 * (((_B - _R) / delta) + 2);
	else
		h = 60 * (((_R - _G) / delta) + 4);

	float s = 0;

	if (float_equal(CMax, 0))
		s = 0;
	else
		s = delta / CMax;

	float v = CMax;

	HSV result;

	result.h = h;
	result.s = s;
	result.v = v;

	return result;
}

RGB hsv2rgb(const HSV& hsv)
{

	float c = hsv.v * hsv.s;

	float x = c * (1.0 - fabs(fmod(hsv.h / 60.0, 2) - 1.0));

	float m = hsv.v - c;

	int h = hsv.h;

	float _r = 0;
	float _g = 0;
	float _b = 0;

	if (h >= 0 && h < 60)
	{
		_r = c;
		_g = x;
		_b = 0;
	}
	else if (h >= 60 && h < 120)
	{
		_r = x;
		_g = c;
		_b = 0;
	}
	else if (h >= 120 && h < 180)
	{
		_r = 0;
		_g = c;
		_b = x;
	}
	else if (h >= 180 && h < 240)
	{

		_r = 0;
		_g = x;
		_b = c;
	}
	else if (h >= 240 && h < 300)
	{
		_r = x;
		_g = 0;
		_b = c;
	}
	else
	{
		_r = c;
		_g = 0;
		_b = x;
	}

	int r = 0;
	int g = 0;
	int b = 0;

	r = (_r + m) * 255;
	g = (_g + m) * 255;
	b = (_b + m) * 255;

	RGB re;

	re.r = r;
	re.g = g;
	re.b = b;

	return re;
}

int rgb2_16bit(const RGB &rgb)
{
	int result = 0x0;

	result += rgb.g;
	result <<= 8;

	result += rgb.r;
	result <<= 8;

	result += rgb.b;

	return result;
}
