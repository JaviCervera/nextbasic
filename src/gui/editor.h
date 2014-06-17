#ifndef GUIEDITOR_H
#define GUIEDITOR_H

#include "../common/defs.h"

#ifdef __cplusplus
extern "C" {
#endif

EXPORT void* CALL CreateEditor(void* parent, int readonly);
EXPORT int CALL EditorColumn(void* editor);
EXPORT void CALL EditorCopy(void* editor);
EXPORT int CALL EditorCursorPos(void* editor);
EXPORT void CALL EditorCut(void* editor);
EXPORT int CALL EditorLine(void* editor);
EXPORT void CALL EditorPaste(void* editor);
EXPORT int CALL EditorSelectionLen(void* editor);
EXPORT int CALL EditorSelectionPos(void* editor);
EXPORT void CALL EditorRedo(void* editor);
EXPORT int CALL EditorCanRedo(void* editor);
EXPORT const char* CALL EditorText(void* editor);
EXPORT void CALL EditorUndo(void* editor);
EXPORT int CALL EditorCanUndo(void* editor);
EXPORT void CALL SelectEditorText(void* editor, int pos, int len);
EXPORT void CALL SetEditorCursorPos(void* editor, int pos);
EXPORT void CALL SetEditorFont(void* editor, void* font);
EXPORT void CALL SetEditorTabSize(void* editor, int tabsize);
EXPORT void CALL SetEditorText(void* editor, const char* text);

#ifdef __cplusplus
}
#endif

#endif // GUIEDITOR_H
