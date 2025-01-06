#include "cop.h"
#include "cop_app.h"

namespace cop {

bool App::Initialize(HINSTANCE hInstance)
{
	constexpr wchar_t wndClassName[] = L"CopMainWindow";
	constexpr wchar_t wndTitle[] = L"CopEngine";

	m_hInstance = hInstance;

	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = MainWindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInstance;
	wcex.hIcon = LoadIcon(m_hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = wndClassName;
	wcex.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);

	if (!RegisterClassExW(&wcex))
		return false;

	m_hWnd = CreateWindowW(
		wndClassName,
		wndTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0,
		1024, 768,
		nullptr, nullptr,
		m_hInstance,
		this);

	if (!m_hWnd)
		return false;

	g_GraphicsMgr.Initialize(m_hWnd);

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return true;
}

void App::Shutdown()
{
	g_GraphicsMgr.Shutdown();

	if (m_hWnd)
	{
		DestroyWindow(m_hWnd);
		m_hWnd = nullptr;
	}
}

int App::Run()
{
	MSG msg;
	while (true)
	{
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				return (int)msg.wParam;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		g_GraphicsMgr.Render();

		//every second, change the window title to show the frame rate
		static int frameCount = 0;
		static float elapsedTime = 0.0f;
		frameCount++;
		elapsedTime += cop::g_GraphicsMgr.GetFrameTime();
		if (elapsedTime >= 1.0f)
		{
			const float fps = (float)frameCount / elapsedTime;
			wchar_t windowTitle[256];
			swprintf_s(windowTitle, 256, L"CopEngine - %.2f FPS", fps);
			SetWindowTextW(m_hWnd, windowTitle);
			frameCount = 0;
			elapsedTime = 0.0f;
		}
	}

	return 0;
}

LRESULT CALLBACK App::MainWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

}