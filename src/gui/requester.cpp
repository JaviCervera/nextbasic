#include "requester.h"
#include <wx/wx.h>

extern "C" {

EXPORT void CALL Notify(void* parent, const char* title, const char* text) {
	wxMessageBox(text, title, wxOK, (wxWindow*)parent);
}

}	// extern "C"