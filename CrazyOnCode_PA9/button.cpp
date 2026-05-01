//primary programmer: Noah Julius
#include "button.hpp"

Button::Button(const std::string& label, const Vector2& position,
    const float& width, const float& height,
    const Color& buttonColor, const Color& textColor)
    : RectangleEntity(position, 0, 0, width, height),
    label(label), buttonColor(buttonColor), textColor(textColor), isHovered(false) {}

bool Button::checkPress()
{
    Rectangle bounds = getBounds();
    Vector2 mousePos = GetMousePosition();

    if (CheckCollisionPointRec(mousePos, bounds))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            return true;
        }
    }
    return false;
}

void Button::update()
{
    isHovered = CheckCollisionPointRec(GetMousePosition(), getBounds());
}

void Button::draw()
{
    Rectangle bounds = getBounds();

    // draw button background, slightly lighter when hovered
    DrawRectangleRec(bounds, isHovered ? GRAY : buttonColor);
    DrawRectangleLinesEx(bounds, 1.0f, WHITE);

    // center text on button
    int fontSize = 80;
    int textWidth = MeasureText(label.c_str(), fontSize);
    DrawText(label.c_str(), (int)(getCenter().x - textWidth / 2), (int)(getCenter().y - fontSize / 2), fontSize, textColor);
}