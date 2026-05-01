//primary programmer: Noah Julius
#pragma once
#include "entity.hpp"
#include <string>

#define BUTTONHEIGHT 100
#define BUTTONWIDTH 250

class Button : public RectangleEntity
{
    std::string label;
    Color buttonColor;
    Color textColor;
    bool isHovered;

public:
    Button(const std::string& label, const Vector2& position = { 0,0 },
        const float& width = BUTTONWIDTH, const float& height = BUTTONHEIGHT,
        const Color& buttonColor = DARKGRAY, const Color& textColor = WHITE);
    ~Button() = default;

    bool checkPress(); // returns true when clicked

    void update() override;
    void draw() override;
};