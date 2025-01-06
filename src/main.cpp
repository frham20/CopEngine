#include "cop.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR    lpCmdLine, _In_ int       nCmdShow)
{
	cop::App app;
	if (!app.Initialize(hInstance))
		return -1;

	int retValue = app.Run();
	
	app.Shutdown();

	return retValue;
}
