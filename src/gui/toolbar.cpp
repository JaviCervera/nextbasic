#include "toolbar.h"
#include "event.h"
#include "internal.h"

extern "C" {

EXPORT void* CALL CreateToolBar(void* parent) {
	return (void*)((wxFrame*)parent)->CreateToolBar();
}

EXPORT void CALL AddToolBarButton(void* toolbar, int id, void* icon, const char* tooltip) {
	((wxToolBar*)toolbar)->AddTool(id, "", *(wxBitmap*)icon, tooltip);
	((nbFrame*)((wxToolBar*)toolbar)->GetParent())->ConnectToolBarEventId(id);
	((wxToolBar*)toolbar)->Realize();
}

EXPORT void CALL AddToolBarSeparator(void* toolbar) {
	((wxToolBar*)toolbar)->AddSeparator();
	((wxToolBar*)toolbar)->Realize();
}

EXPORT void CALL AddToolBarWidget(void* toolbar, void* widget) {
	((wxToolBar*)toolbar)->AddControl((wxControl*)widget);
	((wxToolBar*)toolbar)->Realize();
}

}	// extern "C"