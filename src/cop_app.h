#pragma once

namespace cop {
class App
{
public:
	App() = default;
	~App() = default;
	int Run();

protected:
	bool Initialize();

private:
	App(const App&) = delete;
	App& operator=(const App&) = delete;

	HINSTANCE m_hInstance;
	Window m_window;
};
} // namespace cop
