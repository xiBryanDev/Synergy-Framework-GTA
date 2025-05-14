#pragma once
#include "stdafx.h"


struct Rect
{
	double x, y, width, height;

	// Construtor com valores padrão para width e height
	Rect(double x = 0, double y = 0, double width = 0, double height = 0)
		: x(x), y(y), width(width), height(height) {}

	Rect(double relX, double relY, double relWidth, double relHeight, bool fix)
	{
		if (fix)
		{
			x = relX / 1280;
			y = relY / 1080;
			width = relWidth / 1280;
			height = relHeight / 1080;
		}
		else
		{
			x = relX;
			y = relY;
			width = relWidth;
			height = relHeight;
		}
		
	}

	void SetPosition(double newX, double newY) { x = newX; y = newY; }
	void SetSize(double newWidth, double newHeight) { width = newWidth; height = newHeight; }
	void Set(double newX, double newY, double newWidth = 0, double newHeight = 0)
	{
		x = newX; y = newY; width = newWidth; height = newHeight;
	}
};

enum UI_Anchor
{
	UI_ANCHOR_CENTER = 0,
	UI_ANCHOR_LEFT = (1 << 0),
	UI_ANCHOR_RIGHT = (1 << 1),
	UI_ANCHOR_TOP = (1 << 2),
	UI_ANCHOR_BOTTOM = (1 << 3),

	UI_ANCHOR_TOP_LEFT = (UI_ANCHOR_TOP | UI_ANCHOR_LEFT),
	UI_ANCHOR_TOP_RIGHT = (UI_ANCHOR_TOP | UI_ANCHOR_RIGHT),
	UI_ANCHOR_TOP_CENTER = (UI_ANCHOR_TOP | UI_ANCHOR_CENTER),
	UI_ANCHOR_BOTTOM_LEFT = (UI_ANCHOR_BOTTOM | UI_ANCHOR_LEFT),
	UI_ANCHOR_BOTTOM_RIGHT = (UI_ANCHOR_BOTTOM | UI_ANCHOR_RIGHT),
	UI_ANCHOR_BOTTOM_CENTER = (UI_ANCHOR_BOTTOM | UI_ANCHOR_CENTER),
	UI_ANCHOR_CENTER_LEFT = (UI_ANCHOR_CENTER | UI_ANCHOR_LEFT),
	UI_ANCHOR_CENTER_RIGHT = (UI_ANCHOR_CENTER | UI_ANCHOR_RIGHT),

	UI_ANCHOR_MASK_HORIZONTAL = (UI_ANCHOR_LEFT | UI_ANCHOR_RIGHT),
	UI_ANCHOR_MASK_VERTICAL = (UI_ANCHOR_TOP | UI_ANCHOR_BOTTOM)
};




namespace UIElement
{
	void DrawRect(const Rect& rect, Color color, int anchor = 0);


	void DrawRectOutline(const Rect& rect, Color borderColor, float borderThickness, int anchor);
	void DrawRectOutlineWithBackground(const Rect& rect, Color borderColor, float borderThickness, Color backgroundColor, int anchor);

	void DrawText(const char* text, int font, const Rect& rect, Color color, int anchor);
	void DrawSprite(const char* Streamedtexture, const char* textureName, const Rect& rect, float rotation, Color color, int anchor);

};

