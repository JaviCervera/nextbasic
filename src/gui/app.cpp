#include "app.h"
#include "internal.h"

// Event handler
void DummyHandler(int event, void* widget, int id) {}
wxEventHandler _nb_eventHandler = DummyHandler;

wxAppConsole *wxCreateApp() {
	wxAppConsole::CheckBuildOptions(WX_BUILD_OPTIONS_SIGNATURE, "your program");
    return new nbApp;
}

bool nbApp::OnInit() {
	wxImage::AddHandler(new wxBMPHandler);
	wxImage::AddHandler(new wxICOHandler);
	wxImage::AddHandler(new wxPNGHandler);
	wxImage::AddHandler(new wxJPEGHandler);
	_nb_eventHandler(EVENT_INIT, NULL, 0);
    return true;
}

extern "C" {

EXPORT int CALL RunApp(wxEventHandler handler) {
	wxDISABLE_DEBUG_SUPPORT();
	wxAppInitializer wxTheAppInitializer((wxAppInitializerFunction) wxCreateApp);
	if ( handler ) _nb_eventHandler = handler;
#ifdef _WIN32
	return wxEntry(NULL);
#else
	int argc = 0;
	return wxEntry(argc, (char**)NULL);
#endif
}

}	// extern "C"
