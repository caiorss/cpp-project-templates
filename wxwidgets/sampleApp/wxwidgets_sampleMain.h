#ifndef WXWIDGETS_SAMPLEMAIN_H
#define WXWIDGETS_SAMPLEMAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "wxwidgets_sampleApp.h"

class wxwidgets_sampleFrame: public wxFrame
{
    public:
        wxwidgets_sampleFrame(wxFrame *frame, const wxString& title);
        ~wxwidgets_sampleFrame();
    private:
        enum
        {
            idMenuQuit = 1000,
            idMenuAbout
        };
        void OnClose(wxCloseEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        DECLARE_EVENT_TABLE()
};


#endif // WXWIDGETS_SAMPLEMAIN_H
