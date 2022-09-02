#include "pch.h"
#include "Controller/ListBox.h"
#include "ECS.h"
#include "item.h"

struct ivec2
{
	std::size_t x, y;

	ivec2(const std::size_t& x = 0, const std::size_t& y = 0) : x(x), y(y) {}

	ivec2(std::size_t&& x, std::size_t&& y) : x(std::move(x)), y(std::move(y)) {}

	ivec2(std::initializer_list<std::size_t> data_list)
	{
		std::uninitialized_copy(data_list.begin(), data_list.end(), &x);
	}

	operator std::string() const
	{
		return '[' + std::to_string(x) + ',' + std::to_string(y) + ']';
	}
};

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

struct ItemGeneralInfo
{
	ivec2 bag_size = { 1,1 };
	int weight = 0;
	int cur_stack = 0;
	int max_stack = 1;

	ItemGeneralInfo(int w = 0)
		:weight(w) {}
};

std::string general_info_description(ItemGeneralInfo const& generalInfo)
{
	return "weight:\t" + std::to_string(generalInfo.weight) + "\nbag size:\t" + static_cast<std::string>(generalInfo.bag_size) + "\nstack:\t" + std::to_string(generalInfo.cur_stack) + '/' + std::to_string(generalInfo.max_stack);
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

	registry.addComponent<TransformComponent>(e1).x = 10;
	registry.addComponent<VelocityComponent>(e2).x = 5;
	registry.addComponent<TransformComponent>(e2).x = 3;

	ItemGeneralInfo itemInfo1 = Attribute<ItemGeneralInfo>::getInstance("Item General Attribute", general_info_description, AttributeGroup::GeneralDescription).instantiate(100);

	ItemGeneralInfo itemInfo2 = Attribute<ItemGeneralInfo>::getInstance().instantiate(20);

	TransformComponent transforms1[] = { {1.f,2.f,3.f}, {2.f,3.f,4.f}, {5.f,4.f,3.f} };
	TransformComponent transforms2[] = { {11.f,12.f,13.f}, {12.f,13.f,14.f}, {15.f,14.f,13.f} };

	DenseArray<TransformComponent> transformArray(transforms1, 3);
	transformArray.resize(5);
	std::vector<TransformComponent> transformVector{ {1.f,2.f,3.f}, {2.f,3.f,4.f}, {5.f,4.f,3.f} };

	transformArray.emplace_back(transforms2, 3);
	transformArray.overwrite(transforms2, 3, 0);
	transformArray.overwrite({ { 12.f, 13.f, 29.f } }, 2);

	//transformArray.emplace_back({ { 1.f, 2.f, 3.f } });

	TransformComponent t2 = transformArray.at(2);


	DenseArray<TransformComponent> arr2({ { 1.f,2.f,3.f }, { 1.f,2.f,3.f } });
	TransformComponent t22 = arr2[1];

	std::size_t at = sizeof(TransformComponent);
	//std::size_t as = sizeof(&(transformArray.m_data));
	std::size_t av = sizeof(transformVector);

	Item item("Sword", "");

	item.addAttribute<ItemGeneralInfo>(12);
	item.modifyAttribute<ItemGeneralInfo>(13);
	ItemGeneralInfo myWeight3 = item.getAttribute<ItemGeneralInfo>();

	auto com = registry.getComponents<TransformComponent>();

	Attribute<ItemGeneralInfo>::getInstance().get_description(itemInfo1);

	std::string result = Attribute<ItemGeneralInfo>::getInstance().get_description(itemInfo1);

	HWND debugWnd = CreateWindowA("static", result.c_str(), WS_VISIBLE | WS_BORDER | WS_CHILD, 20, 230, 400, 300, hwnd, NULL, NULL, NULL);
}