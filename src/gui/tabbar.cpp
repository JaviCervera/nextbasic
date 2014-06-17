#include "tabbar.h"
#include "event.h"
#include <wx/notebook.h>

extern "C" {

EXPORT void* CALL CreateTabBar(void* parent) {
	return (void*)new wxNotebook((wxWindow*)parent, wxID_ANY);
}

EXPORT void CALL AddTabBarItem(void* tabbar, void* item, const char* text) {
	((wxNotebook*)tabbar)->AddPage((wxWindow*)item, text);
}

EXPORT int CALL CountTabBarItems(void* tabbar) {
	return ((wxNotebook*)tabbar)->GetPageCount();
}

EXPORT void CALL RemoveTabBarItem(void* tabbar, int index) {
	((wxNotebook*)tabbar)->DeletePage(index);
}

EXPORT void CALL SetTabBarIndex(void* tabbar, int index) {
	((wxNotebook*)tabbar)->SetSelection(index);
}

EXPORT int CALL TabBarIndex(void* tabbar) {
	return ((wxNotebook*)tabbar)->GetSelection();
}

EXPORT void CALL SetTabText(void* tabbar, int index, const char* text) {
	((wxNotebook*)tabbar)->SetPageText(index, text);
}

EXPORT const char* CALL TabText(void* tabbar, int index) {
	return ((wxNotebook*)tabbar)->GetPageText(index).ToAscii();
}

EXPORT void* CALL TabWidget(void* tabbar, int index) {
	return ((wxNotebook*)tabbar)->GetPage(index);
}

}	// extern "C"