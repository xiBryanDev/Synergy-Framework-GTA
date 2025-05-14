#include "Graphics.h"
#include "Native.h"


namespace UIElement // gta 5 render 
{

    void SetPositionAnchor(float& x, float& y, float width, float height, int anchor)
    {
        // Ajusta x baseado no ancoramento horizontal
        switch (anchor & UI_ANCHOR_MASK_HORIZONTAL)
        {
        case UI_ANCHOR_CENTER:
            // Já está no centro, não precisa ajustar
            break;
        case UI_ANCHOR_LEFT:
            x += width * 0.5f; // Move para a esquerda adicionando metade da largura
            break;
        case UI_ANCHOR_RIGHT:
            x -= width * 0.5f; // Move para a direita subtraindo metade da largura
            break;
        }

        // Ajusta y baseado no ancoramento vertical
        switch (anchor & UI_ANCHOR_MASK_VERTICAL)
        {
        case UI_ANCHOR_CENTER:
            // Já está no centro, não precisa ajustar
            break;
        case UI_ANCHOR_TOP:
            y += height * 0.5f; // Move para cima adicionando metade da altura
            break;
        case UI_ANCHOR_BOTTOM:
            y -= height * 0.5f; // Move para baixo subtraindo metade da altura
            break;
        }
    }

    void DrawRect(const Rect& rect, Color color, int anchor)
    {
        float x = rect.x;
        float y = rect.y;
        float width = rect.width;
        float height = rect.height;

        if (anchor != 0)
            SetPositionAnchor(x, y, width, height, anchor);

        invoke<void*>(0xDD2BFC77, x, y, width, height, color.r, color.g, color.b, color.a);
    }

    void DrawRectOutline(const Rect& rect, Color borderColor, float borderThickness, int anchor)
    {
        float x = rect.x;
        float y = rect.y;
        float width = rect.width;
        float height = rect.height;

        if (anchor != 0)
            SetPositionAnchor(x, y, width, height, anchor);

        // Borda superior
        DrawRect({ x + width * 0.5f, y + borderThickness * 0.5f, width, borderThickness }, borderColor);
        // Borda inferior
        DrawRect({ x + width * 0.5f, y + height - borderThickness * 0.5f, width, borderThickness }, borderColor);
        // Borda esquerda (usa a altura total)
        DrawRect({ x + borderThickness * 0.5f, y + height * 0.5f, borderThickness, height }, borderColor);
        // Borda direita (usa a altura total)
        DrawRect({ x + width - borderThickness * 0.5f, y + height * 0.5f, borderThickness, height }, borderColor);
    }

    void DrawRectOutlineWithBackground(const Rect& rect, Color borderColor, float borderThickness, Color backgroundColor, int anchor)
    {

        float x = rect.x;
        float y = rect.y;
        float width = rect.width;
        float height = rect.height;

        if (anchor != 0)
        SetPositionAnchor(x, y, width, height, anchor);

        float bgWidth = width - (borderThickness * 2.0f);
        float bgHeight = height - (borderThickness * 2.0f);

        // Desenha o fundo ajustado
        DrawRect({ x + width * 0.5f, y + height * 0.5f, bgWidth, bgHeight, false }, backgroundColor);

        // Borda superior
        DrawRect({ x + width * 0.5f, y + borderThickness * 0.5f, width, borderThickness, false }, borderColor);

        // Borda inferior
        DrawRect({ x + width * 0.5f, y + height - borderThickness * 0.5f, width, borderThickness, false }, borderColor);
       // DrawRect({ x + width * 0.5f, y + height - borderThickness * 0.5f, width, borderThickness, false }, borderColor);

        // Borda esquerda (usa a altura total)
        DrawRect({ x + borderThickness * 0.5f, y + height * 0.5f, borderThickness, height, false }, borderColor);

        // Borda direita (usa a altura total)
        DrawRect({ x + width - borderThickness * 0.5f, y + height * 0.5f, borderThickness, height, false }, borderColor);
    }


    void DrawText(const char* text, int font, const Rect& rect, Color color, int anchor) {

        float x = rect.x;
        float y = rect.y;
        float width = rect.width;
        float height = rect.height;

        SetPositionAnchor(x, y, width, height, anchor);


        UI::SET_TEXT_FONT(font);
        UI::SET_TEXT_SCALE(width, height);
        UI::SET_TEXT_COLOUR(color.r, color.g, color.b, color.a);
        UI::SET_TEXT_WRAP(0.0f, 1.0f);
        UI::SET_TEXT_CENTRE(false);
        UI::SET_TEXT_DROPSHADOW(5, 5, 5, 0, 80);
        UI::SET_TEXT_EDGE(2, 255, 255, 255, 150);
        UI::SET_TEXT_OUTLINE();
        UI::_SET_TEXT_ENTRY("STRING");
        UI::_ADD_TEXT_COMPONENT_STRING(text);
        UI::_DRAW_TEXT(x, y);
    }

    static Any NETWORK_IS_IN_SESSION() { return invoke<Any>(0x4BC4105E); } // 0x4BC4105E


    void DrawSprite(const char* Streamedtexture, const char* textureName, const Rect& rect, float rotation, Color color, int anchor)
    {
        float x = rect.x;
        float y = rect.y;
        float width = rect.width;
        float height = rect.height;

        SetPositionAnchor(x, y, width, height, anchor);
		GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(Streamedtexture, false);
		if (GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(Streamedtexture))
			GRAPHICS::DRAW_SPRITE(Streamedtexture, textureName, x, y, width, height, rotation, color.r, color.g, color.b, color.a);
    }
};
