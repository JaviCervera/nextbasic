#ifndef GUIWIDGET_H
#define GUIWIDGET_H

#include "../common/defs.h"

#ifdef __cplusplus
extern "C" {
#endif

EXPORT void* CALL FreeWidget(void* widget);
EXPORT void CALL LayoutWidget(void* widget, int x, int y, int width, int height);
EXPORT int CALL WidgetX(void* widget);
EXPORT int CALL WidgetY(void* widget);
EXPORT int CALL WidgetWidth(void* widget);
EXPORT int CALL WidgetHeight(void* widget);
EXPORT void CALL EnableWidget(void* widget, BOOL enable);
EXPORT void CALL ShowWidget(void* widget, BOOL show);
EXPORT void CALL FocusWidget(void* widget);
EXPORT void* CALL WidgetOSHandle(void* widget);
EXPORT void CALL SetWidgetStyleSheet(void* widget, const char* sheet);
EXPORT void CALL SetWidgetProperty(void* widget, const char* property, void* value);
EXPORT void* CALL WidgetProperty(void* widget, const char* property);

#ifdef __cplusplus
}
#endif

#endif // GUIWIDGET_H