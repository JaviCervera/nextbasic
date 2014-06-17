#include "window.h"
#include "event.h"
#include "internal.h"

wxBEGIN_EVENT_TABLE(nbFrame, wxFrame)
	EVT_MENU(wxID_ANY, nbFrame::OnMenuEvent)
wxEND_EVENT_TABLE()

nbFrame::nbFrame(wxWindow* parent, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, wxID_ANY, "", pos, size, style) {
}

void nbFrame::ConnectToolBarEventId(int id) {
	Connect(id, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(nbFrame::OnMenuEvent));
}

void nbFrame::OnMenuEvent(wxCommandEvent& event) {
	_nb_eventHandler(EVENT_MENU, this, event.GetId());
}


// Module functions


extern "C" {

EXPORT void* CALL CreateWindow(void* parent, int x, int y, int width, int height, int flags) {
	// Fix default flags
	if ( flags == 0 ) flags = WINDOW_TITLEBAR | WINDOW_RESIZABLE;
	
	// Set wxWidgets style based on flags
	long style = wxCLIP_CHILDREN;
	if ( flags & WINDOW_TITLEBAR )	style = style | wxCAPTION | wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX;
	if ( flags & WINDOW_RESIZABLE)	style = style | wxMAXIMIZE_BOX | wxRESIZE_BORDER;
	if ( flags & WINDOW_TOOL)		style = style | wxFRAME_TOOL_WINDOW;
	if ( flags & WINDOW_MODAL )		style = style | wxFRAME_FLOAT_ON_PARENT;

	// Create frame
	nbFrame *frame = new nbFrame((wxWindow*)parent, wxPoint(x, y), wxSize(width, height), style);
	
	// Check if it needs to be centered
	if ( flags & WINDOW_CENTER ) frame->Centre();
	
	return (void*) frame;
}

EXPORT void CALL SetWindowTitle(void* window, const char* title) {
	((nbFrame*)window)->SetTitle(title);
}

}	// extern "C"
