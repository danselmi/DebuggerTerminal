#include <wx/socket.h>
#include <wx/msgdlg.h>
#include <wx/app.h>

//Creat a SocketServer retuning 0 on error
wxSocketServer* wxtcp_uartServerSocket (int port =4242)
{
    wxIPV4address addr;
    if(!addr.Service(4242))
        return NULL;

        wxSocketServer* pServerSocket = new wxSocketServer(addr);

        if(!pServerSocket->Ok())
        {
            if(pServerSocket->LastError() == wxSOCKET_INVPORT)
                wxMessageBox(wxT("Port in use!"));
            pServerSocket->Destroy();
            return NULL;
        }
        return pServerSocket;
}

// recieving clients

void wxtSocketEvents(wxSocketServer* pServerSocket,wxEvtHandler* pHandler)
{
    wxASSERT_MSG (pHandler != NULL || wxTheApp != NULL,wxT("NO EVENT HANDLER!"));

    if (pHandler == NULL)
        pHandler = wxTheApp;

    pServerSocket->SetEventHandler(*pHandler, ID_SERVER);

    pHandler->Connect(ID_SERVER, wxEVT_SOCKET, (wxObjectEventFunction) & wxMyServer::OnSocketEvent)

}
