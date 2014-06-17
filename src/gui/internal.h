#ifndef GUIINTERNAL_H
#define GUIINTERNAL_H

#include <wx/wx.h>

class nbApp: public wxApp {
public:
    virtual bool OnInit();
};

class nbFrame: public wxFrame {
public:
    nbFrame(wxWindow* parent, const wxPoint& pos, const wxSize& size, long style);
    void ConnectToolBarEventId(int id);
private:
	void OnMenuEvent(wxCommandEvent& event);
    wxDECLARE_EVENT_TABLE();
};

#endif // GUIINTERNAL_H