#include "cop.h"
#include "cop_window.h"
#include "resources/resource.h"

namespace cop {
std::wstring Window::m_className(L"CPWindowClass");

Window::Window() : m_hWnd(nullptr)
{
}

Window::~Window()
{
	if (m_hWnd)
	{
		DestroyWindow(m_hWnd);
	}
}

bool Window::Create(const wchar_t* title, int width, int height)
{
	if (!RegisterWindowClass())
		return false;

	const HINSTANCE hInstance = GetModuleHandle(nullptr);

	m_hWnd = CreateWindowW(
		m_className.c_str(),
		title,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0,
		width, height,
		nullptr, nullptr,
		hInstance,
		this);

	return m_hWnd != nullptr;
}

bool Window::RegisterWindowClass()
{
	const HINSTANCE hInstance = GetModuleHandle(nullptr);

	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = m_className.c_str();
	wcex.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);

	return RegisterClassExW(&wcex);
}

void Window::SetTitle(const wchar_t* title)
{
	SetWindowTextW(m_hWnd, title);
}

LRESULT CALLBACK Window::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Window* pThis = nullptr;

	if (message == WM_NCCREATE)
	{
		CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
		pThis = (Window*)pCreate->lpCreateParams;
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pThis);

		pThis->m_hWnd = hWnd;
	}
	else
	{
		pThis = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	}

	if (pThis)
	{
		switch (message)
		{
			case WM_PAINT:
				{
					PAINTSTRUCT ps;
					HDC hdc = BeginPaint(hWnd, &ps);
					EndPaint(hWnd, &ps);
					break;
				}
			case WM_ERASEBKGND:
				{
					// Prevent the window from erasing the background
					return 1;
				}
			case WM_SIZE:
				{
					g_GraphicsMgr.ResizeBuffers(LOWORD(lParam), HIWORD(lParam));
					break;
				}
			case WM_DESTROY:
				{
					PostQuitMessage(0);
					break;
				}
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	else
	{
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}
}
