#include "statusbar.h"
#include <wx/wx.h>

extern "C" {

EXPORT void* CALL CreateStatusBar(void* parent) {
	return (void*)((wxFrame*)parent)->CreateStatusBar();
}

EXPORT void CALL SetStatusBarText(void* statusbar, const char* text) {
	((wxStatusBar*)statusbar)->SetStatusText(text);
}

EXPORT const char* CALL StatusBarText(void* statusbar) {
	return ((wxStatusBar*)statusbar)->GetStatusText().ToAscii();
}

}	// extern "C"