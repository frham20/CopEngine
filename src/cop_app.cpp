#include "cop.h"
#include "cop_app.h"

namespace cop {

bool App::Initialize()
{
	m_hInstance = GetModuleHandle(nullptr);

	m_window.Create(L"Copilot Test", 800, 600);
	g_GraphicsMgr.Initialize(m_window.GetHwnd());

	m_window.Show(true);

	return true;
}

int App::Run()
{
	if (!Initialize())
		return -1;

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
			swprintf_s(windowTitle, 256, L"Copilot Test - %.2f FPS", fps);
			m_window.SetTitle(windowTitle);

			frameCount = 0;
			elapsedTime = 0.0f;
		}
	}

	return 0;
}

}