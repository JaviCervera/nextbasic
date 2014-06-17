#include "menu.h"
#include <wx/wx.h>

extern "C" {

EXPORT void* CALL CreateMenuBar(void* win) {
	wxMenuBar* menuBar = new wxMenuBar;
	((wxFrame*)win)->SetMenuBar(menuBar);
	return (void*)menuBar;
}

EXPORT void* CALL AddMenuTitle(void* menubar, const char* title) {
	wxMenu* menu = new wxMenu;
	((wxMenuBar*)menubar)->Append(menu, title);
	return (void*)menu;
}

EXPORT void CALL AddMenuItem(void* menu, int id, const char* text) {
	((wxMenu*)menu)->Append(id, text);
}

EXPORT void CALL AddMenuSeparator(void* menu) {
	((wxMenu*)menu)->AppendSeparator();
}

EXPORT void* CALL AddSubMenu(void* menu, int id, const char* title) {
	wxMenu* submenu = new wxMenu;
	((wxMenu*)menu)->Append(id, title, submenu);
	return (void*)submenu;
}

}	// extern "C"