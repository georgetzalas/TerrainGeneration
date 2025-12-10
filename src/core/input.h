#pragma once

#include <iostream>
#include <core/window.h>

#define KEYBOARD_KEYS 1024
#define MOUSE_KEYS    32

namespace Core
{
    class Input
    {
    public:
        static Input* GetInstance();

        bool IsKeyboardKeyPressed(uint32_t key);
        bool IsKeyboardKeyDown(uint32_t key);

        bool IsMouseKeyPressed(uint32_t key);
        bool IsMouseKeyDown(uint32_t key);

        void Init();
        void Update();
        void Destroy();

        double GetMousePosX();
        double GetMousePosY();

        double GetMousePosXLastFrame();
        double GetMousePosYLastFrame();

        double GetMouseOffsetX();
        double GetMouseOffsetY();

        bool IsMouseWheelUp();
        bool IsMouseWheelDown();

        int  GetYScrollOffset();
        void SetYScrollOffset(int offset);

        void DisableCursor();
        void EnableCursor();

    private:
        Input();

        Input(const Input&) = delete;
        Input& operator=(const Input&) = delete;

    private:
        static Input* input;

        bool keyboardKeysDown[KEYBOARD_KEYS];
        bool keyboardKeysDownLastFrame[KEYBOARD_KEYS];
        bool keyboardKeysPressed[KEYBOARD_KEYS];

        bool mouseKeysDown[MOUSE_KEYS];
        bool mouseKeysDownLastFrame[MOUSE_KEYS];
        bool mouseKeysPressed[MOUSE_KEYS];

        double mousePosX;
        double mousePosY;

        double mousePosXLastFrame;
        double mousePosYLastFrame;

        double mouseOffetX;
        double mouseOffetY;

        bool mouseWheelUp;
        bool mouseWheelDown;

        int yScrollOffset = 0;
    };
};
