#include "editor.h"
#include <wx/wx.h>
#include <wx/richtext/richtextctrl.h>

extern "C" {

EXPORT void* CALL CreateEditor(void* parent, int readonly) {
    long style = wxRE_MULTILINE;
    if ( readonly ) style |= wxRE_READONLY;
    return (void*)new wxRichTextCtrl((wxWindow*)parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, style);
}

EXPORT int CALL EditorColumn(void* editor) {
    long column, line;
    ((wxRichTextCtrl*)editor)->PositionToXY(EditorCursorPos(editor), &column, &line);
    return column;
}

EXPORT void CALL EditorCopy(void* editor) {
    ((wxRichTextCtrl*)editor)->Copy();
}

EXPORT int CALL EditorCursorPos(void* editor) {
    return (int)((wxRichTextCtrl*)editor)->GetCaretPosition();
}

EXPORT void CALL EditorCut(void* editor) {
    ((wxRichTextCtrl*)editor)->Cut();
}

EXPORT int CALL EditorLine(void* editor) {
    long column, line;
    ((wxRichTextCtrl*)editor)->PositionToXY(EditorCursorPos(editor), &column, &line);
    return line;
}

EXPORT void CALL EditorPaste(void* editor) {
    ((wxRichTextCtrl*)editor)->Paste();
}

EXPORT int CALL EditorSelectionLen(void* editor) {
    return ((wxRichTextCtrl*)editor)->GetStringSelection().Length();
}

EXPORT int CALL EditorSelectionPos(void* editor) {
    return (int)((wxRichTextCtrl*)editor)->GetSelectionAnchor();
}

EXPORT void CALL EditorRedo(void* editor) {
    ((wxRichTextCtrl*)editor)->Redo();
}

EXPORT int CALL EditorCanRedo(void* editor) {
    return ((wxRichTextCtrl*)editor)->CanRedo();
}

EXPORT const char* CALL EditorText(void* editor) {
    return ((wxRichTextCtrl*)editor)->GetValue().ToAscii();
}

EXPORT void CALL EditorUndo(void* editor) {
    ((wxRichTextCtrl*)editor)->Undo();
}

EXPORT int CALL EditorCanUndo(void* editor) {
    return ((wxRichTextCtrl*)editor)->CanUndo();
}

EXPORT void CALL SelectEditorText(void* editor, int pos, int len) {
    ((wxRichTextCtrl*)editor)->SetSelectionRange(wxRichTextRange(pos, pos+len));
}

EXPORT void CALL SetEditorCursorPos(void* editor, int pos) {
    ((wxRichTextCtrl*)editor)->SetCaretPosition(pos);
}

EXPORT void CALL SetEditorFont(void* editor, void* font) {
	((wxRichTextCtrl*)editor)->SetFont(*((wxFont*)font));
}

EXPORT void CALL SetEditorTabSize(void* editor, int tabsize) {
    // TODO: Add this
}

EXPORT void CALL SetEditorText(void* editor, const char* text) {
    ((wxRichTextCtrl*)editor)->SetValue(text);
}

}   // extern "C"
