#pragma once
#include "../pch.h"

namespace ListBox
{
	HWND Create(HWND& hWndParent, int X, int Y, int Width, int Height)
	{
		return CreateWindowExA(WS_EX_CLIENTEDGE, "Listbox", NULL, WS_VISIBLE | WS_CHILD, X, Y, Width, Height, hWndParent, NULL, NULL, NULL);
	}

	LRESULT AddString(HWND& listbox, const char* string)
	{
		return SendMessageA(listbox, LB_ADDSTRING, 0, (LPARAM)string);
	}
}
