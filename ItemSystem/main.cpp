#include "pch.h"
#include "Controller/ListBox.h"
#include "ECS.h"

void AddController(HWND hwnd);

LRESULT CALLBACK WindowProc(HWND hwnd, UINT umsg, WPARAM wp, LPARAM lp);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	WNDCLASSA wc = {};

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInst;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = MAIN_WINDOW_CLASSNAME;
	wc.hCursor = LoadCursor(hInst, IDC_ARROW);

	RegisterClassA(&wc);

	HWND hwnd = CreateWindowExA(0, MAIN_WINDOW_CLASSNAME, "main window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 500, 600, NULL, NULL, NULL, NULL);

	ShowWindow(hwnd, cmdshow);

	MSG msg = {};
	while (GetMessageA(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}


	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT umsg, WPARAM wp, LPARAM lp)
{
	switch (umsg)
	{
	case WM_COMMAND:
		switch (wp)
		{
		default:
			break;
		}
	case WM_CREATE:
		AddController(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProcA(hwnd, umsg, wp, lp);
	}
	return 0;
}

void AddController(HWND hwnd)
{
	HWND lb = ListBox::Create(hwnd, 20, 20, 300, 200);
	ListBox::AddString(lb, "sword");
	ListBox::AddString(lb, "axe");

	Registry registry;
	EntityID e1 = registry.createEntity();
	EntityID e2 = registry.createEntity();

	struct TransformComponent
	{
		float x, y, z;
		TransformComponent()
			: x(0.0f), y(0.0f), z(0.0f) {}
		TransformComponent(float x, float y, float z)
			: x(x), y(y), z(z) {}
	};

	struct VelocityComponent
	{
		float x, y, z;
		VelocityComponent()
			: x(0.0f), y(0.0f), z(0.0f) {}
		VelocityComponent(float x, float y, float z)
			: x(x), y(y), z(z) {}
	};

	registry.addComponent<TransformComponent>(e1)->x = 10;
	registry.addComponent<VelocityComponent>(e2)->x = 5;
	registry.addComponent<TransformComponent>(e2)->x = 3;
	auto com = registry.getComponents<TransformComponent>();

	std::string result = std::to_string(registry.getComponent<VelocityComponent>(e2)->x);

	HWND debugWnd = CreateWindowA("static", result.c_str(), WS_VISIBLE | WS_BORDER | WS_CHILD, 20, 230, 400, 300, hwnd, NULL, NULL, NULL);
}