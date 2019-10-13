#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "wxwidgets_sampleApp.h"
#include "wxwidgets_sampleMain.h"

IMPLEMENT_APP(wxwidgets_sampleApp);

bool wxwidgets_sampleApp::OnInit()
{
    wxwidgets_sampleFrame* frame = new wxwidgets_sampleFrame(0L, _("wxWidgets Application Template"));
    
    frame->Show();
    
    return true;
}
