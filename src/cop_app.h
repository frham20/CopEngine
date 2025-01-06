#pragma once

namespace cop {
class App
{
public:
	App() = default;
	~App() = default;

	bool Initialize(HINSTANCE hInstance);
	void Shutdown();

	int Run();

protected:
	static LRESULT CALLBACK MainWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	App(const App&) = delete;
	App& operator=(const App&) = delete;

	HINSTANCE m_hInstance;
	HWND m_hWnd;
};
} // namespace cop
