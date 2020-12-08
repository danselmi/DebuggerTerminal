#include "DebuggerTerminalApp.h"

#include "DebuggerTerminalMain.h"
#include <wx/image.h>

IMPLEMENT_APP(DebuggerTerminalApp)

bool DebuggerTerminalApp::OnInit()
{
    wxInitAllImageHandlers();

    DebuggerTerminalFrame* Frame = new DebuggerTerminalFrame(0);
    Frame->Show();
    SetTopWindow(Frame);

    return true;

}
