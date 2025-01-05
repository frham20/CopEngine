#pragma once

namespace cop {
class Window
{
public:
	Window();
	~Window();

	bool Create(const wchar_t* title, int width, int height);
	HWND GetHwnd() const;
	void SetTitle(const wchar_t* title);
	void Show(bool show);

protected:
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	bool RegisterWindowClass();

	HWND m_hWnd;
	static std::wstring m_className;
};

inline HWND Window::GetHwnd() const
{
	return m_hWnd;
}

inline void Window::Show(bool show)
{
	ShowWindow(m_hWnd, show ? SW_SHOW : SW_HIDE);
}

}
