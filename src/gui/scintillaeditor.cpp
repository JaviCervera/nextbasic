#include "scintillaeditor.h"
#include <wx/stc/stc.h>

extern "C" {

EXPORT void* CALL CreateScintillaEditor(void* parent) {
	return (void*)new wxStyledTextCtrl((wxWindow*)parent);
}

}	// extern "C"