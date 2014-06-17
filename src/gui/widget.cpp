#include "widget.h"
#include <wx/wx.h>

extern "C" {

EXPORT void* CALL FreeWidget(void* widget) {
	((wxWindow*)widget)->Destroy();
}

EXPORT void CALL LayoutWidget(void* widget, int x, int y, int width, int height) {
	((wxWindow*)widget)->SetSize(x, y, width, height);
}

EXPORT int CALL WidgetX(void* widget) {
	return ((wxWindow*)widget)->GetScreenRect().GetPosition().x;
}

EXPORT int CALL WidgetY(void* widget) {
	return ((wxWindow*)widget)->GetScreenRect().GetPosition().y;
}

EXPORT int CALL WidgetWidth(void* widget) {
	return ((wxWindow*)widget)->GetScreenRect().GetSize().GetWidth();
}

EXPORT int CALL WidgetHeight(void* widget) {
	return ((wxWindow*)widget)->GetScreenRect().GetSize().GetHeight();
}

EXPORT void CALL EnableWidget(void* widget, BOOL enable) {
	((wxWindow*)widget)->Enable(enable);
}

EXPORT void CALL ShowWidget(void* widget, BOOL show) {
	((wxWindow*)widget)->Show(show);
}

EXPORT void CALL FocusWidget(void* widget) {
	((wxWindow*)widget)->SetFocus();
}

EXPORT void* CALL WidgetOSHandle(void* widget) {
	return (void*)((wxWindow*)widget)->GetHandle();
}

EXPORT void CALL SetWidgetProperty(void* widget, const char* property, void* value) {
	// *** TODO
}

EXPORT void* CALL WidgetProperty(void* widget, const char* property) {
	// *** TODO
	return NULL;
}

}	// extern "C"