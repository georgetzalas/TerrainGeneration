#include <core/input.h>

Core::Input* Core::Input::input = nullptr;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    Core::Input::GetInstance()->SetYScrollOffset(yoffset);
}

Core::Input::Input()
{

}

void Core::Input::Init()
{
	glfwSetScrollCallback(Core::Window::GetInstance()->GetWindow(), scroll_callback);
    glfwSetInputMode(Core::Window::GetInstance()->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    mouseWheelUp = false;
    mouseWheelDown = false;

	for(int i=0; i<KEYBOARD_KEYS; i++)
	{
		keyboardKeysDown[i] = false;
		keyboardKeysDownLastFrame[i] = false;
		keyboardKeysPressed[i] = false;
	}

	for(int i=0; i<MOUSE_KEYS; i++)
	{
		mouseKeysDown[i] = false;
		mouseKeysDownLastFrame[i] = false;
		mouseKeysPressed[i] = false;
	}

    int windowSizeX, windowSizeY;
	glfwGetWindowSize(Core::Window::GetInstance()->GetWindow(), &windowSizeX, &windowSizeY);

	mousePosX = (float)windowSizeX / 2.0f;
	mousePosY = (float)windowSizeY / 2.0f;

    Core::Logger::GetInstance()->Log(LogLevel::INFO, "Initialized Input System");
}

Core::Input* Core::Input::GetInstance()
{
    if(input == nullptr)
    {
        input = new Input();
    }
    return input;
}

bool Core::Input::IsKeyboardKeyPressed(uint32_t key)
{
    if(key >= KEYBOARD_KEYS)
    {
        std::cerr << "Key out of range" << std::endl;
        return false;
    }
    return keyboardKeysPressed[key];
}

bool Core::Input::IsKeyboardKeyDown(uint32_t key)
{
    if(key >= KEYBOARD_KEYS)
    {
        std::cerr << "Key out of range" << std::endl;
        return false;
    }
    return keyboardKeysDown[key];
}

bool Core::Input::IsMouseKeyPressed(uint32_t key)
{
    if(key >= MOUSE_KEYS)
    {
        std::cerr << "Key out of range" << std::endl;
        return false;
    }
    return mouseKeysPressed[key];
}

bool Core::Input::IsMouseKeyDown(uint32_t key)
{
    if(key >= MOUSE_KEYS)
    {
        std::cerr << "Key out of range" << std::endl;
        return false;
    }
    return mouseKeysDown[key];
}

void Core::Input::Update()
{
    mousePosXLastFrame = mousePosX;
    mousePosYLastFrame = mousePosY;

	glfwGetCursorPos(Core::Window::GetInstance()->GetWindow(), &mousePosX, &mousePosY);

	for(int key=GLFW_KEY_SPACE; key<=GLFW_KEY_LAST; key++)
	{
		if(glfwGetKey(Core::Window::GetInstance()->GetWindow(), key) == GLFW_PRESS)
			keyboardKeysDown[key] = true;
        else
            keyboardKeysDown[key] = false;
 
        if(keyboardKeysDown[key] && !keyboardKeysDownLastFrame[key])
            keyboardKeysPressed[key] = true;
        else
            keyboardKeysPressed[key] = false;

        keyboardKeysDownLastFrame[key] = keyboardKeysDown[key];
	}
	
	for(int key=GLFW_MOUSE_BUTTON_1; key<=GLFW_MOUSE_BUTTON_LAST; key++)
	{
        if(glfwGetMouseButton(Core::Window::GetInstance()->GetWindow(), key) == GLFW_PRESS)
			mouseKeysDown[key] = true;
        else
            mouseKeysDown[key] = false;
 
        if(mouseKeysDown[key] && !mouseKeysDownLastFrame[key])
            mouseKeysPressed[key] = true;
        else
            mouseKeysPressed[key] = false;

 
        mouseKeysDownLastFrame[key] = mouseKeysDown[key];
	}

    mouseWheelUp = false;
    mouseWheelDown = false;

    if(Core::Input::GetInstance()->GetYScrollOffset() < 0) mouseWheelDown = true;
    if(Core::Input::GetInstance()->GetYScrollOffset() > 0) mouseWheelUp = true;

    Input::GetInstance()->SetYScrollOffset(0);
}

void Core::Input::Destroy()
{
    delete input;
    Core::Logger::GetInstance()->Log(LogLevel::INFO, "Destoryed Input System");
}

double Core::Input::GetMousePosX()
{
    return mousePosX;
}

double Core::Input::GetMousePosY()
{
    return mousePosY;
}

double Core::Input::GetMousePosXLastFrame()
{
    return mousePosXLastFrame;
}

double Core::Input::GetMousePosYLastFrame()
{
    return mousePosYLastFrame;
}

double Core::Input::GetMouseOffsetX()
{
    return mousePosX - mousePosXLastFrame;
}

double Core::Input::GetMouseOffsetY()
{
    return mousePosYLastFrame - mousePosY;
}

bool Core::Input::IsMouseWheelUp()
{
    return mouseWheelUp;
}

bool Core::Input::IsMouseWheelDown()
{
    return mouseWheelDown;
}

int Core::Input::GetYScrollOffset()
{
    return yScrollOffset;
}

void Core::Input::SetYScrollOffset(int offset)
{
    yScrollOffset = offset;
}

void Core::Input::DisableCursor()
{
    glfwSetInputMode(Core::Window::GetInstance()->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Core::Input::EnableCursor()
{
    glfwSetInputMode(Core::Window::GetInstance()->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}
