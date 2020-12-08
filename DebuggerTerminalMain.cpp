#include "DebuggerTerminalMain.h"
#include <wx/msgdlg.h>
#include <wx/menu.h>
#include <wx/valgen.h>

#include <wx/intl.h>
#include <wx/string.h>
#include <wx/stattext.h>

#include <wx/numdlg.h>
#include <wx/filedlg.h>
#include <wx/fileconf.h>

#include "SelectFontSizeDialog.h"
#include <libserialport.h>

const long DebuggerTerminalFrame::ID_MENU_QUIT = wxNewId();
const long DebuggerTerminalFrame::ID_MENU_ABOUT = wxID_ABOUT;

const long DebuggerTerminalFrame::ID_RXDATA_PANEL = wxNewId();
const long DebuggerTerminalFrame::ID_TXDATA_PANEL = wxNewId();
const long DebuggerTerminalFrame::ID_INPUTCTRL_PANEL = wxNewId();

const long DebuggerTerminalFrame::ID_CONNECTION_TOOLBAR = wxNewId();
const long DebuggerTerminalFrame::ID_CONNECT_TOGGLEBUTTON = wxNewId();
const long DebuggerTerminalFrame::ID_PORT_CHOICE = wxNewId();
const long DebuggerTerminalFrame::ID_PORT_RESCAN_BUTTON = wxNewId();
const long DebuggerTerminalFrame::ID_BAUDRATE_COMBOBOX = wxNewId();
const long DebuggerTerminalFrame::ID_DATA_WIDTH_CHOICE = wxNewId();
const long DebuggerTerminalFrame::ID_STOPBITS_CHOICE = wxNewId();
const long DebuggerTerminalFrame::ID_PARITY_CHOICE = wxNewId();
const long DebuggerTerminalFrame::ID_CTSFLOW_CHECKBOX = wxNewId();
const long DebuggerTerminalFrame::ID_TCP_PORT = wxNewId();
const long DebuggerTerminalFrame::ID_STREAMCOUNTER_TOOLBAR = wxNewId();
const long DebuggerTerminalFrame::ID_STREAMCOUNTER_RX_TEXT = wxNewId();
const long DebuggerTerminalFrame::ID_STREAMCOUNTER_TX_TEXT = wxNewId();
const long DebuggerTerminalFrame::ID_STREAMCOUNTER_RX_BUTTON = wxNewId();
const long DebuggerTerminalFrame::ID_STREAMCOUNTER_TX_BUTTON = wxNewId();

const long DebuggerTerminalFrame::ID_USERCHARCOUNTER_TOOLBAR = wxNewId();
const long DebuggerTerminalFrame::ID_USERCHARCOUNTER_SPINCTRL = wxNewId();
const long DebuggerTerminalFrame::ID_USERCHARCOUNTER_TEXT = wxNewId();
const long DebuggerTerminalFrame::ID_USERCHARCOUNTER_BUTTON = wxNewId();

const long DebuggerTerminalFrame::ID_NEWLINECONTROL_TOOLBAR = wxNewId();
const long DebuggerTerminalFrame::ID_NEWLINECONTROL_CHOICE = wxNewId();
const long DebuggerTerminalFrame::ID_NEWLINECONTROL_CHECKBOX = wxNewId();

const long DebuggerTerminalFrame::ID_CLEAR_TOOLBAR = wxNewId();
const long DebuggerTerminalFrame::ID_CLEARRECEIVED_BUTTON = wxNewId();
const long DebuggerTerminalFrame::ID_CLEARTRANSMITTED_BUTTON = wxNewId();

const long DebuggerTerminalFrame::ID_OUTPUTFORMAT_TOOLBAR = wxNewId();
const long DebuggerTerminalFrame::ID_OUTPUTFORMAT_ASCII_CHECKBOX = wxNewId();
const long DebuggerTerminalFrame::ID_OUTPUTFORMAT_HEX_CHECKBOX = wxNewId();
const long DebuggerTerminalFrame::ID_OUTPUTFORMAT_DEC_CHECKBOX = wxNewId();
const long DebuggerTerminalFrame::ID_OUTPUTFORMAT_BIN_CHECKBOX = wxNewId();
const long DebuggerTerminalFrame::ID_INPUTFORMAT_TOOLBAR = wxNewId();
const long DebuggerTerminalFrame::ID_INPUTFORMAT_ASCII_CHECKBOX = wxNewId();
const long DebuggerTerminalFrame::ID_INPUTFORMAT_HEX_CHECKBOX = wxNewId();
const long DebuggerTerminalFrame::ID_INPUTFORMAT_DEC_CHECKBOX = wxNewId();
const long DebuggerTerminalFrame::ID_INPUTFORMAT_BIN_CHECKBOX = wxNewId();

const long DebuggerTerminalFrame::ID_SAVEOUTPUT_TOOLBAR = wxNewId();
const long DebuggerTerminalFrame::ID_SAVEOUTPUT_BUTTON = wxNewId();
const long DebuggerTerminalFrame::ID_SAVEOUTPUT_SETTINGS_BUTTON = wxNewId();

const long DebuggerTerminalFrame::ID_CLEARATCHAR_TOOLBAR = wxNewId();
const long DebuggerTerminalFrame::ID_CLEARATCHAR_CHECKBOX = wxNewId();
const long DebuggerTerminalFrame::ID_CLEARATCHAR_SPINCTRL = wxNewId();

const long DebuggerTerminalFrame::ID_AUTOINSERTNEWLIN_TOOLBAR = wxNewId();
const long DebuggerTerminalFrame::ID_AUTOINSERTNEWLIN_SPINCTRL = wxNewId();

const long DebuggerTerminalFrame::ID_OUTPUTOPTIONS_TOOLBAR = wxNewId();
const long DebuggerTerminalFrame::ID_OUTPUTOPTIONS_AUTOSCROLL_CHECKBOX = wxNewId();
const long DebuggerTerminalFrame::ID_OUTPUTOPTIONS_SHOWERR_CHECKBOX = wxNewId();

const long DebuggerTerminalFrame::ID_NEWLINEBYPAUSE_TOOLBAR = wxNewId();
const long DebuggerTerminalFrame::ID_NEWLINEBYPAUSE_SPINCTRL = wxNewId();

const long DebuggerTerminalFrame::ID_STATUSLINES_TOOLBAR = wxNewId();
const long DebuggerTerminalFrame::ID_STATUSLINES_CTSLED = wxNewId();
const long DebuggerTerminalFrame::ID_STATUSLINES_DSRLED = wxNewId();
const long DebuggerTerminalFrame::ID_STATUSLINES_RILED = wxNewId();
const long DebuggerTerminalFrame::ID_STATUSLINES_DCDLED = wxNewId();

const long DebuggerTerminalFrame::ID_SETSTATUSLINES_TOOLBAR = wxNewId();
const long DebuggerTerminalFrame::ID_SETSTATUSLINES_DTR_TOGGLEBUTTON = wxNewId();
const long DebuggerTerminalFrame::ID_SETSTATUSLINES_RTS_TOGGLEBUTTON = wxNewId();

const long DebuggerTerminalFrame::ID_SENDFILE_TOOLBAR = wxNewId();
const long DebuggerTerminalFrame::ID_SENDFILE_BUTTON = wxNewId();

const long DebuggerTerminalFrame::ID_SENDONENTER_TOOLBAR = wxNewId();
const long DebuggerTerminalFrame::ID_SENDONENTER_CHOICE = wxNewId();

const long DebuggerTerminalFrame::ID_MENU_SHOW_RULER = wxNewId();
const long DebuggerTerminalFrame::ID_MENU_SET_RULER_START = wxNewId();
const long DebuggerTerminalFrame::ID_MENU_CLEAR_ALL = wxNewId();
const long DebuggerTerminalFrame::ID_MENU_CONNECTONFOCUS = wxNewId();
const long DebuggerTerminalFrame::ID_MENU_CHANGERX_FONT = wxNewId();
const long DebuggerTerminalFrame::ID_MENU_CHANGETX_FONT = wxNewId();
const long DebuggerTerminalFrame::ID_MENU_MODIFY_NEWLINE_AT = wxNewId();
const long DebuggerTerminalFrame::ID_MENU_MODIFY_SEND_ON_ENTER = wxNewId();

//const long DebuggerTerminalFrame::ID_MENU_RECEIVE_BITMASK = wxNewId();
const long DebuggerTerminalFrame::ID_MENU_RECEIVE_BITMASK_NONE = wxNewId();
const long DebuggerTerminalFrame::ID_MENU_RECEIVE_BITMASK_8 = wxNewId();
const long DebuggerTerminalFrame::ID_MENU_RECEIVE_BITMASK_8_7 = wxNewId();
const long DebuggerTerminalFrame::ID_MENU_RECEIVE_BITMASK_8_6 = wxNewId();
const long DebuggerTerminalFrame::ID_MENU_RECEIVE_BITMASK_8_5 = wxNewId();

const long DebuggerTerminalFrame::ID_MENU_SHOW_ALL_PANES = wxNewId();
const long DebuggerTerminalFrame::ID_MENU_DEFAULT_LAYOUT = wxNewId();
const long DebuggerTerminalFrame::ID_MENU_SAVE_LAYOUT = wxNewId();
const long DebuggerTerminalFrame::ID_MENU_LOAD_LAYOUT = wxNewId();

const long DebuggerTerminalFrame::ID_INPUTCONTROL_TOOLBAR = wxNewId();
const long DebuggerTerminalFrame::ID_INPUTCONTROL_CHOICE = wxNewId();
const long DebuggerTerminalFrame::ID_INPUTCONTROL_TEXT = wxNewId();
const long DebuggerTerminalFrame::ID_INPUTCONTROL_BUTTON = wxNewId();

const long DebuggerTerminalFrame::ID_RX_TIMER = wxNewId();
const long DebuggerTerminalFrame::ID_SERVER_RX_TIMER = wxNewId();
const long DebuggerTerminalFrame::ID_TX_TIMER = wxNewId();
//}

wxString last_port;

BEGIN_EVENT_TABLE(DebuggerTerminalFrame,wxFrame)
    EVT_TIMER       (ID_RX_TIMER,                          DebuggerTerminalFrame::OnRxTimer)
    EVT_TIMER       (ID_TX_TIMER,                          DebuggerTerminalFrame::OnTxTimer)
    EVT_TIMER       (ID_SERVER_RX_TIMER,                   DebuggerTerminalFrame::OnServerReadTimer)
    EVT_BUTTON      (ID_PORT_RESCAN_BUTTON,                DebuggerTerminalFrame::OnPortRescan)
    EVT_TOGGLEBUTTON(ID_CONNECT_TOGGLEBUTTON,              DebuggerTerminalFrame::OnConnectToggle)
    EVT_UPDATE_UI   (ID_CONNECT_TOGGLEBUTTON,              DebuggerTerminalFrame::OnUpdateConnectToggle)
    EVT_UPDATE_UI   (ID_PORT_CHOICE,                       DebuggerTerminalFrame::OnUpdateConnectControls )
    EVT_UPDATE_UI   (ID_PORT_RESCAN_BUTTON,                DebuggerTerminalFrame::OnUpdateConnectControls )
    EVT_UPDATE_UI   (ID_BAUDRATE_COMBOBOX,                 DebuggerTerminalFrame::OnUpdateConnectControls )
    EVT_UPDATE_UI   (ID_DATA_WIDTH_CHOICE,                 DebuggerTerminalFrame::OnUpdateConnectControls )
    EVT_UPDATE_UI   (ID_STOPBITS_CHOICE,                   DebuggerTerminalFrame::OnUpdateConnectControls )
    EVT_UPDATE_UI   (ID_PARITY_CHOICE,                     DebuggerTerminalFrame::OnUpdateConnectControls )
    EVT_UPDATE_UI   (ID_CTSFLOW_CHECKBOX,                  DebuggerTerminalFrame::OnUpdateConnectControls )
    EVT_UPDATE_UI   (ID_TCP_PORT,                          DebuggerTerminalFrame::OnUpdateConnectControls )
    EVT_MENU        (ID_MENU_QUIT,                         DebuggerTerminalFrame::OnQuit)
    EVT_MENU        (ID_MENU_ABOUT,                        DebuggerTerminalFrame::OnAbout)
    EVT_ACTIVATE    (                                      DebuggerTerminalFrame::OnActivate)
    EVT_BUTTON      (ID_CLEARRECEIVED_BUTTON,              DebuggerTerminalFrame::OnClearReceived)
    EVT_BUTTON      (ID_CLEARTRANSMITTED_BUTTON,           DebuggerTerminalFrame::OnClearTransmitted)

    EVT_BUTTON      (ID_USERCHARCOUNTER_BUTTON,            DebuggerTerminalFrame::OnResetUserStreamCounter)
    EVT_BUTTON      (ID_STREAMCOUNTER_TX_BUTTON,           DebuggerTerminalFrame::OnResetTxStreamCounter)
    EVT_BUTTON      (ID_STREAMCOUNTER_RX_BUTTON,           DebuggerTerminalFrame::OnResetRxStreamCounter)
    EVT_CHECKBOX    (ID_OUTPUTOPTIONS_AUTOSCROLL_CHECKBOX, DebuggerTerminalFrame::OnCheckBoxAutoscroll)

    EVT_CHECKBOX    (ID_OUTPUTFORMAT_ASCII_CHECKBOX,       DebuggerTerminalFrame::OnCheckBoxOutputFormat)
    EVT_CHECKBOX    (ID_OUTPUTFORMAT_HEX_CHECKBOX,         DebuggerTerminalFrame::OnCheckBoxOutputFormat)
    EVT_CHECKBOX    (ID_OUTPUTFORMAT_DEC_CHECKBOX,         DebuggerTerminalFrame::OnCheckBoxOutputFormat)
    EVT_CHECKBOX    (ID_OUTPUTFORMAT_BIN_CHECKBOX,         DebuggerTerminalFrame::OnCheckBoxOutputFormat)
    EVT_CHECKBOX    (ID_INPUTFORMAT_ASCII_CHECKBOX,        DebuggerTerminalFrame::OnCheckBoxInputFormat)
    EVT_CHECKBOX    (ID_INPUTFORMAT_HEX_CHECKBOX,          DebuggerTerminalFrame::OnCheckBoxInputFormat)
    EVT_CHECKBOX    (ID_INPUTFORMAT_DEC_CHECKBOX,          DebuggerTerminalFrame::OnCheckBoxInputFormat)
    EVT_CHECKBOX    (ID_INPUTFORMAT_BIN_CHECKBOX,          DebuggerTerminalFrame::OnCheckBoxInputFormat)

    EVT_MENU        (ID_MENU_SET_RULER_START,              DebuggerTerminalFrame::OnSetRulerStart)
    EVT_MENU        (ID_MENU_SHOW_RULER,                   DebuggerTerminalFrame::OnMenuShowRuler)
    EVT_UPDATE_UI   (ID_MENU_SHOW_RULER,                   DebuggerTerminalFrame::OnUpdateShowRuler)
    EVT_MENU        (ID_MENU_CLEAR_ALL,                    DebuggerTerminalFrame::OnMenuClearAll)

    EVT_MENU        (ID_MENU_CHANGERX_FONT,                DebuggerTerminalFrame::OnMenuChangeFont)
    EVT_MENU        (ID_MENU_CHANGETX_FONT,                DebuggerTerminalFrame::OnMenuChangeFont)
    EVT_TOGGLEBUTTON(ID_SETSTATUSLINES_DTR_TOGGLEBUTTON,   DebuggerTerminalFrame::OnToggleLinestate)
    EVT_TOGGLEBUTTON(ID_SETSTATUSLINES_RTS_TOGGLEBUTTON,   DebuggerTerminalFrame::OnToggleLinestate)
    EVT_BUTTON      (ID_SENDFILE_BUTTON,                   DebuggerTerminalFrame::OnSendFile)
    EVT_UPDATE_UI   (ID_SENDFILE_BUTTON,                   DebuggerTerminalFrame::OnUpdateSendFile)

    EVT_MENU        (ID_MENU_DEFAULT_LAYOUT,               DebuggerTerminalFrame::OnDefaultLayout)
    EVT_MENU        (ID_MENU_SHOW_ALL_PANES,               DebuggerTerminalFrame::OnShowAll)

    EVT_TEXT_ENTER  (ID_INPUTCONTROL_TEXT,                 DebuggerTerminalFrame::OnInputControlTextEnter)

    EVT_MENU        (ID_RXDATA_PANEL,                      DebuggerTerminalFrame::OnShowOrHidePanel)
    EVT_MENU        (ID_TXDATA_PANEL,                      DebuggerTerminalFrame::OnShowOrHidePanel)
    EVT_MENU        (ID_CONNECTION_TOOLBAR,                DebuggerTerminalFrame::OnShowOrHidePanel)
    EVT_MENU        (ID_STATUSLINES_TOOLBAR,               DebuggerTerminalFrame::OnShowOrHidePanel)
    EVT_MENU        (ID_STREAMCOUNTER_TOOLBAR,             DebuggerTerminalFrame::OnShowOrHidePanel)
    EVT_MENU        (ID_NEWLINEBYPAUSE_TOOLBAR,            DebuggerTerminalFrame::OnShowOrHidePanel)
    EVT_MENU        (ID_AUTOINSERTNEWLIN_TOOLBAR,          DebuggerTerminalFrame::OnShowOrHidePanel)
    EVT_MENU        (ID_NEWLINECONTROL_TOOLBAR,            DebuggerTerminalFrame::OnShowOrHidePanel)
    EVT_MENU        (ID_OUTPUTOPTIONS_TOOLBAR,             DebuggerTerminalFrame::OnShowOrHidePanel)
    EVT_MENU        (ID_CLEARATCHAR_TOOLBAR,               DebuggerTerminalFrame::OnShowOrHidePanel)
    EVT_MENU        (ID_OUTPUTFORMAT_TOOLBAR,              DebuggerTerminalFrame::OnShowOrHidePanel)
    EVT_MENU        (ID_USERCHARCOUNTER_TOOLBAR,           DebuggerTerminalFrame::OnShowOrHidePanel)
    EVT_MENU        (ID_CLEAR_TOOLBAR,                     DebuggerTerminalFrame::OnShowOrHidePanel)
    EVT_MENU        (ID_SENDFILE_TOOLBAR,                  DebuggerTerminalFrame::OnShowOrHidePanel)
    EVT_MENU        (ID_SETSTATUSLINES_TOOLBAR,            DebuggerTerminalFrame::OnShowOrHidePanel)
    EVT_MENU        (ID_INPUTFORMAT_TOOLBAR,               DebuggerTerminalFrame::OnShowOrHidePanel)
    EVT_MENU        (ID_SENDONENTER_TOOLBAR,               DebuggerTerminalFrame::OnShowOrHidePanel)
    EVT_MENU        (ID_INPUTCONTROL_TOOLBAR,              DebuggerTerminalFrame::OnShowOrHidePanel)

    EVT_UPDATE_UI   (ID_RXDATA_PANEL,                      DebuggerTerminalFrame::OnUpdateShowOrHidePanel)
    EVT_UPDATE_UI   (ID_TXDATA_PANEL,                      DebuggerTerminalFrame::OnUpdateShowOrHidePanel)
    EVT_UPDATE_UI   (ID_CONNECTION_TOOLBAR,                DebuggerTerminalFrame::OnUpdateShowOrHidePanel)
    EVT_UPDATE_UI   (ID_STATUSLINES_TOOLBAR,               DebuggerTerminalFrame::OnUpdateShowOrHidePanel)
    EVT_UPDATE_UI   (ID_STREAMCOUNTER_TOOLBAR,             DebuggerTerminalFrame::OnUpdateShowOrHidePanel)
    EVT_UPDATE_UI   (ID_NEWLINEBYPAUSE_TOOLBAR,            DebuggerTerminalFrame::OnUpdateShowOrHidePanel)
    EVT_UPDATE_UI   (ID_AUTOINSERTNEWLIN_TOOLBAR,          DebuggerTerminalFrame::OnUpdateShowOrHidePanel)
    EVT_UPDATE_UI   (ID_NEWLINECONTROL_TOOLBAR,            DebuggerTerminalFrame::OnUpdateShowOrHidePanel)
    EVT_UPDATE_UI   (ID_OUTPUTOPTIONS_TOOLBAR,             DebuggerTerminalFrame::OnUpdateShowOrHidePanel)
    EVT_UPDATE_UI   (ID_CLEARATCHAR_TOOLBAR,               DebuggerTerminalFrame::OnUpdateShowOrHidePanel)
    EVT_UPDATE_UI   (ID_OUTPUTFORMAT_TOOLBAR,              DebuggerTerminalFrame::OnUpdateShowOrHidePanel)
    EVT_UPDATE_UI   (ID_USERCHARCOUNTER_TOOLBAR,           DebuggerTerminalFrame::OnUpdateShowOrHidePanel)
    EVT_UPDATE_UI   (ID_CLEAR_TOOLBAR,                     DebuggerTerminalFrame::OnUpdateShowOrHidePanel)
    EVT_UPDATE_UI   (ID_SENDFILE_TOOLBAR,                  DebuggerTerminalFrame::OnUpdateShowOrHidePanel)
    EVT_UPDATE_UI   (ID_SETSTATUSLINES_TOOLBAR,            DebuggerTerminalFrame::OnUpdateShowOrHidePanel)
    EVT_UPDATE_UI   (ID_INPUTFORMAT_TOOLBAR,               DebuggerTerminalFrame::OnUpdateShowOrHidePanel)
    EVT_UPDATE_UI   (ID_SENDONENTER_TOOLBAR,               DebuggerTerminalFrame::OnUpdateShowOrHidePanel)
    EVT_UPDATE_UI   (ID_INPUTCONTROL_TOOLBAR,              DebuggerTerminalFrame::OnUpdateShowOrHidePanel)
    EVT_CHOICE      (ID_INPUTCONTROL_CHOICE,               DebuggerTerminalFrame::OnChoiceInputctrlFormat)
    EVT_MENU        (ID_MENU_RECEIVE_BITMASK_NONE,         DebuggerTerminalFrame::OnReceiveBitmaskSelected)
    EVT_MENU        (ID_MENU_RECEIVE_BITMASK_8,            DebuggerTerminalFrame::OnReceiveBitmaskSelected)
    EVT_MENU        (ID_MENU_RECEIVE_BITMASK_8_7,          DebuggerTerminalFrame::OnReceiveBitmaskSelected)
    EVT_MENU        (ID_MENU_RECEIVE_BITMASK_8_6,          DebuggerTerminalFrame::OnReceiveBitmaskSelected)
    EVT_MENU        (ID_MENU_RECEIVE_BITMASK_8_5,          DebuggerTerminalFrame::OnReceiveBitmaskSelected)
    EVT_UPDATE_UI   (ID_MENU_RECEIVE_BITMASK_NONE,         DebuggerTerminalFrame::OnUpdateReceiveBitmask)
    EVT_UPDATE_UI   (ID_MENU_RECEIVE_BITMASK_8,            DebuggerTerminalFrame::OnUpdateReceiveBitmask)
    EVT_UPDATE_UI   (ID_MENU_RECEIVE_BITMASK_8_7,          DebuggerTerminalFrame::OnUpdateReceiveBitmask)
    EVT_UPDATE_UI   (ID_MENU_RECEIVE_BITMASK_8_6,          DebuggerTerminalFrame::OnUpdateReceiveBitmask)
    EVT_UPDATE_UI   (ID_MENU_RECEIVE_BITMASK_8_5,          DebuggerTerminalFrame::OnUpdateReceiveBitmask)
END_EVENT_TABLE()

DebuggerTerminalFrame::DebuggerTerminalFrame(wxWindow* parent, wxWindowID id):
    wxFrame(parent, id, _T("ourMainFrame"), wxDefaultPosition, wxSize(800, 600)),
    tcpserver_(new TcpServer(&tcp_port_, io_service_)),
    initDone_(false),
    pauseCounter_(0),
    txStreamCount_(0),
    rxStreamCount_(0),
    userStreamCount_(0),
    serialPort_(nullptr),
    portConfig_(nullptr),
    wasConnected_(false),
    currentPort_(-1),
    rxLastChar_(-1),
    txLastChar_(-1)
{
    SetTitle(_T("DebuggerTerminal"));
    //SetIcon(const wxIcon& icon);
    wxConfigBase::Set(new wxFileConfig());

    sp_new_config(&portConfig_);

    int x=10, y=10, h=800, w=600;

    wxConfigBase::Get()->Read(_T("FrameSizeX"), &w);
    wxConfigBase::Get()->Read(_T("FrameSizeY"), &h);
    wxConfigBase::Get()->Read(_T("FramePosX"), &x);
    wxConfigBase::Get()->Read(_T("FramePosY"), &y);

    bool b=false;
    wxConfigBase::Get()->Read(_T("FrameMaximized"), &b);
    Maximize(b);
    if(b)Fit();
    b=false;
    wxConfigBase::Get()->Read(_T("FrameIconized"), &b);
    Iconize(b);

    wxSize size(w,h);
    SetSize(size);

    auiManager_ = new wxAuiManager(this, wxAUI_MGR_DEFAULT);

    int txfontsize = wxConfigBase::Get()->Read(_T("TxFontSize"), 9);
    txDataPanel_ = new DataPanel(this, ID_TXDATA_PANEL, txfontsize);
    int rxfontsize = wxConfigBase::Get()->Read(_T("RxFontSize"), 9);
    rxDataPanel_ = new DataPanel(this, ID_RXDATA_PANEL, rxfontsize);

//    m_AuiManager->AddPane(txDataPanel_, wxAuiPaneInfo().
//                          Name(_T("TxDataPane")).
//                          Caption(_("Transmitted Data")).
//                          CaptionVisible().
//                          //Float()
//                          FloatingSize(600, 400).
//                          Center()
//                          //DockFixed(false).
//                          //Movable(true).
//                          //Floatable(true)
//                          //PinButton()
//                          );
//    wins.push_back(txDataPanel_);
//
//    m_AuiManager->AddPane(rxDataPanel_, wxAuiPaneInfo().
//                          Name(_T("RxDataPane")).
//                          Caption(_("Received Data")).
//                          CaptionVisible().
//                          //Float()
//                          FloatingSize(600, 400).
//                          Center()
//                          //DockFixed(false).
//                          //Movable(true).
//                          //Floatable(true)
//                          //PinButton()
//                          );
//    wins.push_back(rxDataPanel_);

    int bitmask=0x000000ff;
    wxConfigBase::Get()->Read(_T("ReceiverBitmask"), &bitmask, bitmask);
    rxDataPanel_->SetBitMask((char)(bitmask&0x00ff));

    //layer 12
    CreateConnectionToolBar();
    CreateStatuslinesToolBar();

    // layer 10
    CreateStreamCounterToolBar();
    CreateNewLineControlToolBar();
    CreateAutoInserNewlineToolBar();
    CreateNewlineByPauseToolBar();

    //layer 8
    CreateClearInputOutputToolBar();
    CreateUserCharCounterToolBar();
    CreateOutputFormatToolBar();
    CreateClearAtCharToolBar();
    CreateOutputOptionsToolBar();

    //CreatesaveOutputToolBar_();
    //bottom
    //layer 8
    CreateSendOnEnterToolBar();
    CreateInputFormatToolBar();
    CreateSetStatuslinesToolBar();
    CreateSendFileToolBar();

    //layer 10
    CreateInputControlToolBar();

    InitMenuBar();
    CreateStatusBar(4);
    SetStatusText(_T("Disconnected"));

    rxTimer_.SetOwner(this, ID_RX_TIMER);
    txTimer_.SetOwner(this, ID_TX_TIMER);
    serverRxTimer_.SetOwner(this, ID_SERVER_RX_TIMER);

    UpdatePortList();
    UpdateOutputFormats();
    UpdateInputFormats();
    UpdateUserStreamCounter();
    UpdateRxStreamCounter();
    UpdateTxStreamCounter();
    rxDataPanel_->EnableRuler(true);
    txDataPanel_->EnableRuler(true);
    rxDataPanel_->SetRulerStart(1);
    txDataPanel_->SetRulerStart(1);
    bool enableautoscroll;
    wxConfigBase::Get()->Read(_T("AutoScroll"), &enableautoscroll, true);
    rxDataPanel_->DoAutoscroll(enableautoscroll);
    txDataPanel_->DoAutoscroll(enableautoscroll);

    sendFileBuffer_ = 0;

    defaultPerspective_ = auiManager_->SavePerspective();
    wxString configuredPerspective = wxConfigBase::Get()->Read(_T("Perspective"), wxEmptyString);
    if (!configuredPerspective.IsEmpty())
        auiManager_->LoadPerspective(configuredPerspective);

    auiNotebook_ = new wxAuiNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_NB_TOP | wxAUI_NB_TAB_SPLIT | wxAUI_NB_TAB_MOVE | wxAUI_NB_SCROLL_BUTTONS );
    auiNotebook_->AddPage(txDataPanel_,_("Transmitted Data"));
    auiNotebook_->AddPage(rxDataPanel_, _("Received Data"));
    auiManager_->AddPane(auiNotebook_, wxAuiPaneInfo().CentrePane());

    auiManager_->Update();
    initDone_ = true;
}

DebuggerTerminalFrame::~DebuggerTerminalFrame()
{
    wxConfigBase::Get()->Write(_T("Perspective"), auiManager_->SavePerspective());

    wxConfigBase::Get()->Write(_T("TxFontSize"), txDataPanel_->GetFontSize());
    wxConfigBase::Get()->Write(_T("RxFontSize"), rxDataPanel_->GetFontSize());

    wxConfigBase::Get()->Write(_T("FrameMaximized"), IsMaximized());
    wxConfigBase::Get()->Write(_T("FrameIconized"), IsIconized());

    wxSize size = GetSize();
    wxConfigBase::Get()->Write(_T("FrameSizeX"), size.x);
    wxConfigBase::Get()->Write(_T("FrameSizeY"), size.y);
    wxPoint pos = GetPosition();
    wxConfigBase::Get()->Write(_T("FramePosX"), pos.x);
    wxConfigBase::Get()->Write(_T("FramePosY"), pos.y);

    sp_free_config(portConfig_);

    auiManager_->UnInit();
}

void DebuggerTerminalFrame::CreateConnectionToolBar()
{
    wxStaticText *StaticText;

    wxAuiToolBar *connectionToolBar = new wxAuiToolBar(this, ID_CONNECTION_TOOLBAR);

    connectToggleButton_ = new wxToggleButton(connectionToolBar, ID_CONNECT_TOGGLEBUTTON, _("Disconnect"));
    connectionToolBar->AddControl(connectToggleButton_);
    connectToggleButton_->SetLabel(_T("Connect"));

    StaticText = new wxStaticText(connectionToolBar, wxID_ANY, _("Port"));
    connectionToolBar->AddControl(StaticText);

    portChoice_ = new wxChoice(connectionToolBar, ID_PORT_CHOICE);//, wxDefaultPosition, wxSize(100, 28) );
    //portChoice_->Append(_T("/dev/tty1000USB0"));
    portChoice_->SetMinSize(wxSize(150, -1));
    connectionToolBar->AddControl(portChoice_);
    //portChoice_->Clear();

    wxButton *portRescanButton = new wxButton(connectionToolBar, ID_PORT_RESCAN_BUTTON, _("R"), wxDefaultPosition, wxSize(34,28));
    portRescanButton->SetToolTip(_("Refresh port list"));
    connectionToolBar->AddControl(portRescanButton);

    StaticText = new wxStaticText(connectionToolBar, wxID_ANY, _("Baud"));
    connectionToolBar->AddControl(StaticText);

    baudRateComboBox_ = new wxComboBox(connectionToolBar, ID_BAUDRATE_COMBOBOX);
    //{
    baudRateComboBox_->Append(_T("50"));
    baudRateComboBox_->Append(_T("110"));
    baudRateComboBox_->Append(_T("150"));
    baudRateComboBox_->Append(_T("300"));
    baudRateComboBox_->Append(_T("600"));
    baudRateComboBox_->Append(_T("1200"));
    baudRateComboBox_->Append(_T("2400"));
    baudRateComboBox_->Append(_T("4800"));
    baudRateComboBox_->Append(_T("9600"));
    baudRateComboBox_->Append(_T("14400"));
    baudRateComboBox_->Append(_T("19200"));
    baudRateComboBox_->Append(_T("38400"));
    baudRateComboBox_->Append(_T("57600"));
    baudRateComboBox_->SetSelection( baudRateComboBox_->Append(_T("115200")) );
    baudRateComboBox_->Append(_T("128000"));
    baudRateComboBox_->Append(_T("230400"));
    baudRateComboBox_->Append(_T("256000"));
    baudRateComboBox_->Append(_T("460800"));
    baudRateComboBox_->Append(_T("500000"));
    baudRateComboBox_->Append(_T("921600"));
    baudRateComboBox_->Append(_T("1228800"));//}
    connectionToolBar->AddControl(baudRateComboBox_);

    StaticText = new wxStaticText(connectionToolBar, wxID_ANY, _("Data"));
    connectionToolBar->AddControl(StaticText);

    dataWidthChoice_ = new wxChoice(connectionToolBar, ID_DATA_WIDTH_CHOICE);
    dataWidthChoice_->Append(_T("5"));
    dataWidthChoice_->Append(_T("6"));
    dataWidthChoice_->Append(_T("7"));
    dataWidthChoice_->SetSelection( dataWidthChoice_->Append(_T("8")) );
    dataWidthChoice_->SetToolTip(_("Set number of databits"));
    connectionToolBar->AddControl(dataWidthChoice_);

    StaticText = new wxStaticText(connectionToolBar, wxID_ANY, _("Stop"));
    connectionToolBar->AddControl(StaticText);

    stopBitsChoice_ = new wxChoice(connectionToolBar, ID_STOPBITS_CHOICE);
    stopBitsChoice_->SetSelection( stopBitsChoice_->Append(_T("1")) );
    /*#ifdef __WXMSW__
        stopBitsChoice_->Append(_T("1.5"));
    #endif*/
    stopBitsChoice_->Append(_T("2"));
    stopBitsChoice_->SetToolTip(_("Set number of stopbits"));
    connectionToolBar->AddControl(stopBitsChoice_);

    StaticText = new wxStaticText(connectionToolBar, wxID_ANY, _("Parity"));
    connectionToolBar->AddControl(StaticText);

    parityChoice_ = new wxChoice(connectionToolBar, ID_PARITY_CHOICE);
    parityChoice_->SetSelection( parityChoice_->Append(_("None")) );
    parityChoice_->Append(_T("Even"));
    parityChoice_->Append(_T("Odd"));
    parityChoice_->Append(_T("Mark"));
    parityChoice_->Append(_T("Space"));
    parityChoice_->SetToolTip(_("Set parity mode"));
    connectionToolBar->AddControl(parityChoice_);

    StaticText = new wxStaticText(connectionToolBar, wxID_ANY, _("Tcp Port"));
    connectionToolBar->AddControl(StaticText);

    port_tcp_ = new wxChoice(connectionToolBar, ID_TCP_PORT);
    port_tcp_->Append(_T("4242"));
    port_tcp_->Append(_T("4243"));
    port_tcp_->SetSelection( port_tcp_->Append(_("4244")) );
    connectionToolBar->AddControl(port_tcp_);

    ctsFlowCheckBox_ = new wxCheckBox(connectionToolBar, ID_CTSFLOW_CHECKBOX, _("CTS Flow control"));
    ctsFlowCheckBox_->SetValue(false);
    ctsFlowCheckBox_->SetToolTip(_("Activate hardware flow control\n (regulate transmission by CTS signal)"));
    connectionToolBar->AddControl(ctsFlowCheckBox_);

    connectionToolBar->Realize();

    auiManager_->AddPane(connectionToolBar, wxAuiPaneInfo().Name(_T("ConnectionControlToolBar")).ToolbarPane().Caption(_("Connecttion control")).Layer(12).Top().Gripper());
    windows_.push_back(connectionToolBar);
}

void DebuggerTerminalFrame::CreateStreamCounterToolBar()
{
    wxStaticText *StaticText;

    wxAuiToolBar *streamCounterToolBar = new wxAuiToolBar(this, ID_STREAMCOUNTER_TOOLBAR);

    StaticText = new wxStaticText(streamCounterToolBar, wxID_ANY, _("Rx"));
    streamCounterToolBar->AddControl(StaticText);

    streamRxCounterTextCtrl_ = new wxTextCtrl(streamCounterToolBar, ID_STREAMCOUNTER_RX_TEXT, _T("0") );
    streamRxCounterTextCtrl_->Enable(false);
    streamRxCounterTextCtrl_->SetToolTip(_("Received bytes"));
    streamCounterToolBar->AddControl(streamRxCounterTextCtrl_);

    wxButton *streamRxCounterButton = new wxButton(streamCounterToolBar, ID_STREAMCOUNTER_RX_BUTTON, _("Reset"), wxDefaultPosition, wxSize(50,-1));
    streamCounterToolBar->AddControl(streamRxCounterButton);

    streamCounterToolBar->AddSeparator();

    StaticText = new wxStaticText(streamCounterToolBar, wxID_ANY, _("Tx"));
    streamCounterToolBar->AddControl(StaticText);

    streamTxCounterTextCtrl_ = new wxTextCtrl(streamCounterToolBar,ID_STREAMCOUNTER_TX_TEXT, _T("0") );
    streamTxCounterTextCtrl_->Enable(false);
    streamTxCounterTextCtrl_->SetToolTip(_("transmitted bytes"));
    streamCounterToolBar->AddControl(streamTxCounterTextCtrl_);

    wxButton *streamTxCounterButton = new wxButton(streamCounterToolBar, ID_STREAMCOUNTER_TX_BUTTON, _("Reset"), wxDefaultPosition, wxSize(50,-1));
    streamCounterToolBar->AddControl(streamTxCounterButton);

    streamCounterToolBar->Realize();

    auiManager_->AddPane(streamCounterToolBar, wxAuiPaneInfo().Name(_T("StreamCounterToolBar")).ToolbarPane().Caption(_("Stream counter")).Layer(10).Top().Gripper());
    windows_.push_back(streamCounterToolBar);
}

void DebuggerTerminalFrame::CreateUserCharCounterToolBar()
{
    wxStaticText *StaticText;

    wxAuiToolBar *userCharCounterToolBar = new wxAuiToolBar(this, ID_USERCHARCOUNTER_TOOLBAR);//, wxPoint(124,225), wxDefaultSize, wxAUI_TB_DEFAULT_STYLE);

    StaticText = new wxStaticText(userCharCounterToolBar, wxID_ANY, _("Count"));
    userCharCounterToolBar->AddControl(StaticText);

    userCharCounterSpin_ = new wxSpinCtrl(userCharCounterToolBar, ID_USERCHARCOUNTER_SPINCTRL, _T("1"));
    userCharCounterSpin_->SetToolTip(_("Count this byte in\nreceived datastream"));
    userCharCounterSpin_->SetRange(0,255);
    userCharCounterToolBar->AddControl(userCharCounterSpin_);

    userCharCounterTextCltr_ = new wxTextCtrl(userCharCounterToolBar, ID_USERCHARCOUNTER_TEXT, _T("0"));
    userCharCounterTextCltr_->Enable(false);
    userCharCounterToolBar->AddControl(userCharCounterTextCltr_);

    wxButton *userCharCounterResetButton = new wxButton(userCharCounterToolBar, ID_USERCHARCOUNTER_BUTTON, _("Reset"), wxDefaultPosition, wxSize(50,-1));
    userCharCounterToolBar->AddControl(userCharCounterResetButton);

    userCharCounterToolBar->Realize();

    auiManager_->AddPane(userCharCounterToolBar, wxAuiPaneInfo().Name(_T("UserCharCounterToolBar")).ToolbarPane().Caption(_("User char counter")).Layer(8).Top().Gripper());
    windows_.push_back(userCharCounterToolBar);
}

void DebuggerTerminalFrame::CreateNewLineControlToolBar()
{
    wxStaticText *StaticText;

    wxAuiToolBar *newLineControlToolBar_ = new wxAuiToolBar(this, ID_NEWLINECONTROL_TOOLBAR);

    StaticText = new wxStaticText(newLineControlToolBar_, wxID_ANY, _("Newline at"));
    newLineControlToolBar_->AddControl(StaticText);

    newLineControlChoice_ = new wxChoice(newLineControlToolBar_, ID_NEWLINECONTROL_CHOICE);
    newLineControlChoice_->SetSelection(newLineControlChoice_->Append(_("None")));
    newLineControlChoice_->Append(_("CR"));
    newLineControlChoice_->Append(_("LF"));
    newLineControlChoice_->Append(_("CR+LF"));
    newLineControlChoice_->Append(_("Null"));
    newLineControlChoice_->Append(_("ETX"));
    newLineControlChoice_->SetToolTip(_("Do a line break when\nthis sequence is received"));
    newLineControlToolBar_->AddControl(newLineControlChoice_);

//    NewLineControlCheckBox = new wxCheckBox(newLineControlToolBar_, ID_NEWLINECONTROL_CHECKBOX, _("Show newline\n characters"));
//    NewLineControlCheckBox->SetValue(true);
//    NewLineControlCheckBox->SetToolTip(_("Show line break sequence "));
//    newLineControlToolBar_->AddControl(NewLineControlCheckBox);

    newLineControlToolBar_->Realize();

    auiManager_->AddPane(newLineControlToolBar_, wxAuiPaneInfo().Name(_T("NewLineControlToolBar")).ToolbarPane().Caption(_("Newline control")).Layer(10).Top().Gripper());
    windows_.push_back(newLineControlToolBar_);
}

void DebuggerTerminalFrame::CreateClearInputOutputToolBar()
{
    wxAuiToolBar *clearInputOutputToolBar = new wxAuiToolBar(this, ID_CLEAR_TOOLBAR);

    wxButton *clearOutputButton = new wxButton(clearInputOutputToolBar, ID_CLEARRECEIVED_BUTTON, _("Clear received"));
    clearInputOutputToolBar->AddControl(clearOutputButton);

    wxButton *clearInputButton = new wxButton(clearInputOutputToolBar, ID_CLEARTRANSMITTED_BUTTON, _("Clear transmitted"));
    clearInputOutputToolBar->AddControl(clearInputButton);

    clearInputOutputToolBar->Realize();

    auiManager_->AddPane(clearInputOutputToolBar, wxAuiPaneInfo().Name(_T("ClearInputOutputToolBar")).ToolbarPane().Caption(_("Clear output")).Layer(8).Top().Gripper());
    windows_.push_back(clearInputOutputToolBar);
}

void DebuggerTerminalFrame::CreateOutputFormatToolBar()
{
    wxAuiToolBar *outputFormatToolBar = new wxAuiToolBar(this, ID_OUTPUTFORMAT_TOOLBAR);

    int format = DataPanelAsciiFormat;
    wxConfigBase::Get()->Read(_T("OutputFormat"), &format);

    outputFormatASCIICheckBox_ = new wxCheckBox(outputFormatToolBar, ID_OUTPUTFORMAT_ASCII_CHECKBOX, _T("Ascii"));
    outputFormatASCIICheckBox_->SetValue(format & DataPanelAsciiFormat);
    outputFormatToolBar->AddControl(outputFormatASCIICheckBox_);

    outputFormatHEXCheckBox_ = new wxCheckBox(outputFormatToolBar, ID_OUTPUTFORMAT_HEX_CHECKBOX, _T("HEX"));
    outputFormatHEXCheckBox_->SetValue(format & DataPanelHexFormat);
    outputFormatToolBar->AddControl(outputFormatHEXCheckBox_);

    outputFormatDECCheckBox_ = new wxCheckBox(outputFormatToolBar, ID_OUTPUTFORMAT_DEC_CHECKBOX, _T("Dec"));
    outputFormatDECCheckBox_->SetValue(format & DataPanelDecFormat);
    outputFormatToolBar->AddControl(outputFormatDECCheckBox_);

    outputFormatBINCheckBox_ = new wxCheckBox(outputFormatToolBar, ID_OUTPUTFORMAT_BIN_CHECKBOX, _T("Bin"));
    outputFormatBINCheckBox_->SetValue(format & DataPanelBinFormat);
    outputFormatToolBar->AddControl(outputFormatBINCheckBox_);

    outputFormatToolBar->Realize();

    auiManager_->AddPane(outputFormatToolBar, wxAuiPaneInfo().Name(_T("OutputFormatToolBar")).ToolbarPane().Caption(_("Output format")).Layer(8).Top().Gripper());
    windows_.push_back(outputFormatToolBar);
}

void DebuggerTerminalFrame::CreateInputFormatToolBar()
{
    int format = DataPanelAsciiFormat;
    wxConfigBase::Get()->Read(_T("InputFormat"), &format);

    wxAuiToolBar *inputFormatToolBar = new wxAuiToolBar(this, ID_INPUTFORMAT_TOOLBAR);

    inputFormatASCIICheckBox_ = new wxCheckBox(inputFormatToolBar, ID_INPUTFORMAT_ASCII_CHECKBOX, _T("Ascii"));
    inputFormatASCIICheckBox_->SetValue(format & DataPanelAsciiFormat);
    inputFormatToolBar->AddControl(inputFormatASCIICheckBox_);

    inputFormatHEXCheckBox_ = new wxCheckBox(inputFormatToolBar, ID_INPUTFORMAT_HEX_CHECKBOX, _T("HEX"));
    inputFormatHEXCheckBox_->SetValue(format & DataPanelHexFormat);
    inputFormatToolBar->AddControl(inputFormatHEXCheckBox_);

    inputFormatDECCheckBox_ = new wxCheckBox(inputFormatToolBar, ID_INPUTFORMAT_DEC_CHECKBOX, _T("Dec"));
    inputFormatDECCheckBox_->SetValue(format & DataPanelDecFormat);
    inputFormatToolBar->AddControl(inputFormatDECCheckBox_);

    inputFormatBINCheckBox_ = new wxCheckBox(inputFormatToolBar, ID_INPUTFORMAT_BIN_CHECKBOX, _T("Bin"));
    inputFormatBINCheckBox_->SetValue(format & DataPanelBinFormat);
    inputFormatToolBar->AddControl(inputFormatBINCheckBox_);

    inputFormatToolBar->Realize();

    auiManager_->AddPane(inputFormatToolBar, wxAuiPaneInfo().Name(_T("InputFormatToolBar")).ToolbarPane().Caption(_("Input format")).Layer(8).Bottom().Gripper());
    windows_.push_back(inputFormatToolBar);
}

void DebuggerTerminalFrame::CreateSaveOutputToolBar()
{
    wxAuiToolBar *saveOutputToolBar = new wxAuiToolBar(this, ID_SAVEOUTPUT_TOOLBAR);

    wxButton *saveOutputButton = new wxButton(saveOutputToolBar, ID_SAVEOUTPUT_BUTTON, _("Save output"));
    saveOutputToolBar->AddControl(saveOutputButton);

    wxButton *saveOutputSettingsButton = new wxButton(saveOutputToolBar, ID_SAVEOUTPUT_SETTINGS_BUTTON, _("..."));
    saveOutputToolBar->AddControl(saveOutputSettingsButton);

    saveOutputToolBar->Realize();

    auiManager_->AddPane(saveOutputToolBar, wxAuiPaneInfo().Name(_T("SaveOutputToolBar")).ToolbarPane().Caption(_("Save output options")).Layer(9).Top().Gripper());
    windows_.push_back(saveOutputToolBar);
}

void DebuggerTerminalFrame::CreateClearAtCharToolBar()
{
    wxAuiToolBar *clearAtCharToolBar = new wxAuiToolBar(this, ID_CLEARATCHAR_TOOLBAR);

    clearAtCharCheckBox_ = new wxCheckBox(clearAtCharToolBar, ID_CLEARATCHAR_CHECKBOX, _("Clear at") );
    clearAtCharCheckBox_->SetToolTip(_("Enable to clear received data when receiving the given byte"));
    clearAtCharToolBar->AddControl(clearAtCharCheckBox_);

    clearAtCharCheckSpinCtrl_ = new wxSpinCtrl(clearAtCharToolBar, ID_CLEARATCHAR_SPINCTRL, _("0") );
    clearAtCharCheckSpinCtrl_->SetRange(0,255);
    clearAtCharCheckSpinCtrl_->SetToolTip(_("Enable to clear received data when receiving the given byte"));
    clearAtCharToolBar->AddControl(clearAtCharCheckSpinCtrl_);


    clearAtCharToolBar->Realize();

    auiManager_->AddPane(clearAtCharToolBar, wxAuiPaneInfo().Name(_T("ClearAtCharToolBar")).ToolbarPane().Caption(_("Clear at character")).Layer(8).Top().Gripper());
    windows_.push_back(clearAtCharToolBar);
}

void DebuggerTerminalFrame::CreateAutoInserNewlineToolBar()
{
    wxAuiToolBar *autoInsertNewlineToolBar = new wxAuiToolBar(this, ID_AUTOINSERTNEWLIN_TOOLBAR);

    wxStaticText *StaticText = new wxStaticText(autoInsertNewlineToolBar, wxID_ANY, _("Newline every\n ... character"));
    autoInsertNewlineToolBar->AddControl(StaticText);

    autoInsertNewlineSpinCtrl_ = new wxSpinCtrl(autoInsertNewlineToolBar, ID_AUTOINSERTNEWLIN_SPINCTRL, _T("0"));
    autoInsertNewlineSpinCtrl_->SetRange(0, 1000);
    autoInsertNewlineToolBar->AddControl(autoInsertNewlineSpinCtrl_);

    autoInsertNewlineToolBar->Realize();

    auiManager_->AddPane(autoInsertNewlineToolBar, wxAuiPaneInfo().Name(_T("AutoInsertNewlineToolBar")).ToolbarPane().Caption(_("Auto insert newline")).Layer(10).Top().Gripper());
    windows_.push_back(autoInsertNewlineToolBar);
}

void DebuggerTerminalFrame::CreateOutputOptionsToolBar()
{
    wxAuiToolBar *outputOptionsToolBar = new wxAuiToolBar(this, ID_OUTPUTOPTIONS_TOOLBAR);

    wxCheckBox *outputOptionsAutoscrollCheckBox = new wxCheckBox(outputOptionsToolBar, ID_OUTPUTOPTIONS_AUTOSCROLL_CHECKBOX, _("Autoscroll"));
    outputOptionsAutoscrollCheckBox->SetToolTip(_("Enables automatic scrolling in receive/transmit data window"));

    bool enableautoscroll;
    wxConfigBase::Get()->Read(_T("AutoScroll"), &enableautoscroll, true);
    outputOptionsAutoscrollCheckBox->SetValue(enableautoscroll);
    outputOptionsToolBar->AddControl(outputOptionsAutoscrollCheckBox);

    wxCheckBox *outputOptionsShowErrCheckBox = new wxCheckBox(outputOptionsToolBar, ID_OUTPUTOPTIONS_SHOWERR_CHECKBOX, _("Show error"));
    outputOptionsShowErrCheckBox->SetValue(false);
    outputOptionsShowErrCheckBox->SetToolTip(_("Highlight errors in received data (parity, frame, ...)"));
    outputOptionsShowErrCheckBox->Enable(false);
    outputOptionsToolBar->AddControl(outputOptionsShowErrCheckBox);

    outputOptionsToolBar->Realize();

    auiManager_->AddPane(outputOptionsToolBar, wxAuiPaneInfo().Name(_T("OutputOptionsToolBar")).ToolbarPane().Caption(_("Output options")).Layer(8).Top().Gripper());
    windows_.push_back(outputOptionsToolBar);
}

void DebuggerTerminalFrame::CreateNewlineByPauseToolBar()
{
    wxAuiToolBar *newlineByPauseToolBar = new wxAuiToolBar(this, ID_NEWLINEBYPAUSE_TOOLBAR);
    wxStaticText *StaticText= new wxStaticText(newlineByPauseToolBar, wxID_ANY, _("Newline after ... ms\nreceive pause (0=off)"));
    newlineByPauseToolBar->AddControl(StaticText);

    newlineByPauseSpinCtrl_ = new wxSpinCtrl(newlineByPauseToolBar, ID_NEWLINEBYPAUSE_SPINCTRL, _T("0"));
    newlineByPauseSpinCtrl_->SetRange(0, 10000);
    newlineByPauseToolBar->AddControl(newlineByPauseSpinCtrl_);

    newlineByPauseToolBar->Realize();

    auiManager_->AddPane(newlineByPauseToolBar, wxAuiPaneInfo().Name(_T("NewlineByPauseToolBar")).ToolbarPane().Caption(_("Newline by Pause option")).Layer(10).Top().Gripper());
    windows_.push_back(newlineByPauseToolBar);
}

void DebuggerTerminalFrame::CreateStatuslinesToolBar()
{
    wxAuiToolBar *statuslinesToolBar = new wxAuiToolBar(this, ID_STATUSLINES_TOOLBAR);
    auto genLed = [&](const long id, const wxString &label) -> wxLed*
    {
        statuslinesToolBar->AddControl(new wxStaticText(statuslinesToolBar, wxID_ANY, label));
        wxLed *pLed = new wxLed(statuslinesToolBar, id);
        pLed->SwitchOn();
        pLed->Disable();
        pLed->SetMinSize(wxSize(22,22));
        statuslinesToolBar->AddControl(pLed);
        return pLed;
    };
    statuslineCTSLed_ = genLed(ID_STATUSLINES_CTSLED, _("CTS:"));
    statuslineDSRLed_ = genLed(ID_STATUSLINES_DSRLED, _("DSR:"));
    statuslineRILed_  = genLed(ID_STATUSLINES_RILED, _("RI:"));
    statuslineDCDLed_ = genLed(ID_STATUSLINES_DCDLED, _("DCD:"));
    statuslinesToolBar->Realize();
    auiManager_->AddPane(statuslinesToolBar, wxAuiPaneInfo().Name(_T("StatuslinesToolBar")).ToolbarPane().Caption(_("Incoming statuslines")).Layer(12).Top().Gripper());
    windows_.push_back(statuslinesToolBar);
}

void DebuggerTerminalFrame::CreateSetStatuslinesToolBar()
{
    wxAuiToolBar *setStatuslinesToolBar = new wxAuiToolBar(this, ID_SETSTATUSLINES_TOOLBAR);

    setStatuslineDTRToggleButton_ = new wxToggleButton(setStatuslinesToolBar, ID_SETSTATUSLINES_DTR_TOGGLEBUTTON, _("DTR"));
    setStatuslinesToolBar->AddControl(setStatuslineDTRToggleButton_);

    setStatuslineRTSToggleButton_ = new wxToggleButton(setStatuslinesToolBar, ID_SETSTATUSLINES_RTS_TOGGLEBUTTON, _("RTS"));
    setStatuslinesToolBar->AddControl(setStatuslineRTSToggleButton_);

    setStatuslinesToolBar->Realize();

    auiManager_->AddPane(setStatuslinesToolBar, wxAuiPaneInfo().Name(_T("SetStatuslinesToolBar")).ToolbarPane().Caption(_("Outgoing statuslines")).Layer(8).Bottom().Gripper());
    windows_.push_back(setStatuslinesToolBar);
}

void DebuggerTerminalFrame::CreateSendFileToolBar()
{
    wxAuiToolBar *sendFileToolBar = new wxAuiToolBar(this, ID_SENDFILE_TOOLBAR);

    wxButton *sendFileButton = new wxButton(sendFileToolBar, ID_SENDFILE_BUTTON, _T("Send file ..."));
    sendFileToolBar->AddControl(sendFileButton);

    sendFileToolBar->Realize();

    auiManager_->AddPane(sendFileToolBar, wxAuiPaneInfo().Name(_T("SendFileToolBar")).ToolbarPane().Caption(_("Send file")).Layer(8).Bottom().Gripper());
    windows_.push_back(sendFileToolBar);
}

void DebuggerTerminalFrame::CreateSendOnEnterToolBar()
{
    wxStaticText *staticText;

    wxAuiToolBar *sendOnEnterToolBar = new wxAuiToolBar(this, ID_SENDONENTER_TOOLBAR);

    staticText = new wxStaticText(sendOnEnterToolBar, wxID_ANY, _T("Send on enter"));
    sendOnEnterToolBar->AddControl(staticText);

    sendOnEnterChoice_ = new wxChoice(sendOnEnterToolBar, ID_SENDONENTER_CHOICE);
    sendOnEnterChoice_->SetSelection( sendOnEnterChoice_->Append(_("None")));
    sendOnEnterChoice_->Append(_T("CR"));
    sendOnEnterChoice_->Append(_T("LF"));
    sendOnEnterChoice_->Append(_T("CR+LF"));
    sendOnEnterChoice_->Append(_T("Space"));
    sendOnEnterChoice_->Append(_T("STX/ETX"));
    sendOnEnterChoice_->Append(_T("NULL"));
    sendOnEnterToolBar->AddControl(sendOnEnterChoice_);

    sendOnEnterToolBar->Realize();

    auiManager_->AddPane(sendOnEnterToolBar, wxAuiPaneInfo().Name(_T("SendOnEnterToolBar")).ToolbarPane().Caption(_("Send on enter")).Layer(8).Bottom().Gripper());
    windows_.push_back(sendOnEnterToolBar);
}

void DebuggerTerminalFrame::CreateInputControlToolBar()
{
    wxAuiToolBar *inputControlToolBar = new wxAuiToolBar(this, ID_INPUTCONTROL_TOOLBAR);

    inputControlChoice_ = new wxChoice(inputControlToolBar, ID_INPUTCONTROL_CHOICE);
    inputControlChoice_->SetSelection(inputControlChoice_->Append(_T("ASC")));
    inputControlChoice_->Append(_T("HEX"));
    inputControlChoice_->Append(_T("BIN"));
    inputControlToolBar->AddControl(inputControlChoice_);

    inputControlText_ = new DataInputControl(inputControlToolBar, ID_INPUTCONTROL_TEXT);
    inputControlText_->SetMinSize(wxSize(1000, -1));
    inputControlToolBar->AddControl(inputControlText_);

    wxButton *inputControlASendButton = new wxButton(inputControlToolBar, ID_INPUTCONTROL_BUTTON, _T("ASend"));
    inputControlToolBar->AddControl(inputControlASendButton);

    inputControlToolBar->Realize();

    auiManager_->AddPane(inputControlToolBar, wxAuiPaneInfo().Name(_T("InputControlToolBar")).ToolbarPane().Caption(_("Input control")).Layer(10).Bottom().Gripper());
    windows_.push_back(inputControlToolBar);
}

void DebuggerTerminalFrame::InitMenuBar()
{
    wxMenu *menu;
    wxMenuItem *menuItem;

    wxMenuBar *MenuBar = new wxMenuBar();

    menu = new wxMenu();
    menuItem = new wxMenuItem(menu, ID_MENU_QUIT, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    menu->Append(menuItem);
    MenuBar->Append(menu, _("&File"));

    menu = new wxMenu();
    menuItem = new wxMenuItem(menu, ID_MENU_SHOW_RULER, _("Show ruler"), wxEmptyString, wxITEM_CHECK);
    menu->Append(menuItem);
    menuItem = new wxMenuItem(menu, ID_MENU_SET_RULER_START, _("Set ruler start..."), wxEmptyString, wxITEM_NORMAL);
    menu->Append(menuItem);
    menu->AppendSeparator();
    menuItem = new wxMenuItem(menu, ID_MENU_CLEAR_ALL, _("Clear all"), wxEmptyString, wxITEM_NORMAL);
    menu->Append(menuItem);
    disconnectOnLostFocus_ = new wxMenuItem(menu, ID_MENU_CONNECTONFOCUS, _("Disconnect on lost focus"), wxEmptyString, wxITEM_CHECK);
    menu->Append(disconnectOnLostFocus_);
    menu->AppendSeparator();
    menuItem = new wxMenuItem(menu, ID_MENU_CHANGERX_FONT, _("Receive font size"), wxEmptyString, wxITEM_NORMAL);
    menu->Append(menuItem);
    menuItem = new wxMenuItem(menu, ID_MENU_CHANGETX_FONT, _("Transmit font size"), wxEmptyString, wxITEM_NORMAL);
    menu->Append(menuItem);
    menu->AppendSeparator();
    menuItem = new wxMenuItem(menu, ID_MENU_MODIFY_NEWLINE_AT, _("Modify newline at..."), wxEmptyString, wxITEM_NORMAL);
    menu->Append(menuItem);
    menuItem = new wxMenuItem(menu, ID_MENU_MODIFY_SEND_ON_ENTER, _("Modify send on enter..."), wxEmptyString, wxITEM_NORMAL);
    menu->Append(menuItem);
    menu->AppendSeparator();

    wxMenu *bitmaskMenu = new wxMenu();
    char bitmask = rxDataPanel_->GetBitMask();
    rxDataPanel_->SetBitMask(bitmask);
    menuItem = new wxMenuItem(bitmaskMenu, ID_MENU_RECEIVE_BITMASK_NONE,_("none"), wxEmptyString, wxITEM_CHECK);
    bitmaskMenu->Append(menuItem);
    menuItem->Check(bitmask == 0xff);
    bitmaskMenu->Append(menuItem);
    menuItem = new wxMenuItem(bitmaskMenu, ID_MENU_RECEIVE_BITMASK_8,_("8"), wxEmptyString, wxITEM_CHECK);
    bitmaskMenu->Append(menuItem);
    menuItem->Check(bitmask == 0x7f);
    bitmaskMenu->Append(menuItem);
    menuItem = new wxMenuItem(bitmaskMenu, ID_MENU_RECEIVE_BITMASK_8_7,_("8:7"), wxEmptyString, wxITEM_CHECK);
    bitmaskMenu->Append(menuItem);
    menuItem->Check(bitmask == 0x3f);
    bitmaskMenu->Append(menuItem);
    menuItem = new wxMenuItem(bitmaskMenu, ID_MENU_RECEIVE_BITMASK_8_6,_("8:6"), wxEmptyString, wxITEM_CHECK);
    bitmaskMenu->Append(menuItem);
    menuItem->Check(bitmask == 0x1f);
    bitmaskMenu->Append(menuItem);
    menuItem = new wxMenuItem(bitmaskMenu, ID_MENU_RECEIVE_BITMASK_8_5,_("8:5"), wxEmptyString, wxITEM_CHECK);
    bitmaskMenu->Append(menuItem);
    menuItem->Check(bitmask == 0x0f);
    bitmaskMenu->Append(menuItem);
    menu->AppendSubMenu(bitmaskMenu, _("Receive bitmask..."), wxEmptyString);
    MenuBar->Append(menu, _("Options"));


    menu = new wxMenu();
    menuItem = new wxMenuItem(menu, ID_MENU_SHOW_ALL_PANES, _("Show all panes"), wxEmptyString, wxITEM_NORMAL);
    menu->Append(menuItem);
    menuItem = new wxMenuItem(menu, ID_MENU_DEFAULT_LAYOUT, _("Default layout"), wxEmptyString, wxITEM_NORMAL);
    menu->Append(menuItem);
    menu->AppendSeparator();
//    menuItem = new wxMenuItem(menu, ID_RXDATA_PANEL, _("Show rx data panel"), wxEmptyString, wxITEM_CHECK);
//    menu->Append(menuItem);
//    menuItem = new wxMenuItem(menu, ID_TXDATA_PANEL, _("Show tx data panel"), wxEmptyString, wxITEM_CHECK);
//    menu->Append(menuItem);
    menuItem = new wxMenuItem(menu, ID_CONNECTION_TOOLBAR, _("Show connection toolbar"), wxEmptyString, wxITEM_CHECK);
    menu->Append(menuItem);
    menuItem = new wxMenuItem(menu, ID_STATUSLINES_TOOLBAR, _("Show statuslines toolbar"), wxEmptyString, wxITEM_CHECK);
    menu->Append(menuItem);
    menuItem = new wxMenuItem(menu, ID_STREAMCOUNTER_TOOLBAR, _("Show streamcounter toolbar"), wxEmptyString, wxITEM_CHECK);
    menu->Append(menuItem);
    menuItem = new wxMenuItem(menu, ID_NEWLINEBYPAUSE_TOOLBAR, _("Show newline by pause options toolbar"), wxEmptyString, wxITEM_CHECK);
    menu->Append(menuItem);
    menuItem = new wxMenuItem(menu, ID_AUTOINSERTNEWLIN_TOOLBAR, _("Show auto insert newline toolbar"), wxEmptyString, wxITEM_CHECK);
    menu->Append(menuItem);
    menuItem = new wxMenuItem(menu, ID_NEWLINECONTROL_TOOLBAR, _("Show newline control toolbar"), wxEmptyString, wxITEM_CHECK);
    menu->Append(menuItem);
    menuItem = new wxMenuItem(menu, ID_OUTPUTOPTIONS_TOOLBAR, _("Show output options toolbar"), wxEmptyString, wxITEM_CHECK);
    menu->Append(menuItem);
    menuItem = new wxMenuItem(menu, ID_CLEARATCHAR_TOOLBAR, _("Show clear at character toolbar"), wxEmptyString, wxITEM_CHECK);
    menu->Append(menuItem);
    menuItem = new wxMenuItem(menu, ID_OUTPUTFORMAT_TOOLBAR, _("Show output format toolbar"), wxEmptyString, wxITEM_CHECK);
    menu->Append(menuItem);
    menuItem = new wxMenuItem(menu, ID_USERCHARCOUNTER_TOOLBAR, _("Show user char counter toolbar"), wxEmptyString, wxITEM_CHECK);
    menu->Append(menuItem);
    menuItem = new wxMenuItem(menu, ID_CLEAR_TOOLBAR, _("Shwo clear output toolbar"), wxEmptyString, wxITEM_CHECK);
    menu->Append(menuItem);
    menuItem = new wxMenuItem(menu, ID_SENDFILE_TOOLBAR, _("Show send file toolbar"), wxEmptyString, wxITEM_CHECK);
    menu->Append(menuItem);
    menuItem = new wxMenuItem(menu, ID_SETSTATUSLINES_TOOLBAR, _("Show outgoing statuslines toolbar"), wxEmptyString, wxITEM_CHECK);
    menu->Append(menuItem);
    menuItem = new wxMenuItem(menu, ID_INPUTFORMAT_TOOLBAR, _("Show input format toolbar"), wxEmptyString, wxITEM_CHECK);
    menu->Append(menuItem);
    menuItem = new wxMenuItem(menu, ID_SENDONENTER_TOOLBAR, _("Show send on enter toolbar"), wxEmptyString, wxITEM_CHECK);
    menu->Append(menuItem);
    menuItem = new wxMenuItem(menu, ID_INPUTCONTROL_TOOLBAR, _("Show input control toolbar"), wxEmptyString, wxITEM_CHECK);
    menu->Append(menuItem);
    menu->AppendSeparator();
    menuItem = new wxMenuItem(menu, ID_MENU_SAVE_LAYOUT, _("Save layout"), wxEmptyString, wxITEM_NORMAL);
    menu->Append(menuItem);
    menuItem = new wxMenuItem(menu, ID_MENU_LOAD_LAYOUT, _("Load layout"), wxEmptyString, wxITEM_NORMAL);
    menu->Append(menuItem);
    MenuBar->Append(menu, _("View"));

    menu = new wxMenu();
    menuItem = new wxMenuItem(menu, ID_MENU_ABOUT, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    menu->Append(menuItem);
    MenuBar->Append(menu, _("Help"));

    SetMenuBar(MenuBar);
}

void DebuggerTerminalFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close();
}

void DebuggerTerminalFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox(_("DebuggerTerminal"), _("Welcome to..."));
}

void DebuggerTerminalFrame::initPortsList()
{
    struct sp_port **portList;

    ports_.Clear();

    sp_list_ports(&portList);
    if(!portList) return;

    for(int i = 0; portList[i] ; ++i)
        ports_.Add(wxString::FromUTF8(sp_get_port_name(portList[i])));

    ports_.Sort();

    sp_free_port_list(portList);
}

void DebuggerTerminalFrame::UpdatePortList()
{
    portChoice_->Freeze();
    wxString currentPort = portChoice_->GetStringSelection();

    portChoice_->Clear();

    initPortsList();

    int sel = -1;
    for (unsigned int i = 0; i < ports_.size(); ++i)
    {
        int id = portChoice_->Append(ports_[i]);
        if ( ports_[i] == currentPort)
            sel = id;
    }
//    if (PortIsOpen())
//        sel = portChoice_->Append(currentPort);// add the port opened by us

    if (sel == -1)
        sel = 0;
    portChoice_->SetSelection(sel);
    if ( currentPort_ != -1 )
        currentPort_ = sel;

    portChoice_->Thaw();
}

void DebuggerTerminalFrame::OnPortRescan(wxCommandEvent &WXUNUSED(event))
{
    UpdatePortList();
}

void DebuggerTerminalFrame::Connect()
{
    if ( ports_.size() == 0 )
    {
        connectToggleButton_->SetValue(false);
        wxMessageBox(_("no ports available"));
        SetStatusText(_T("Disconnected, no ports available"));
        return;
    }

    long baudrate = 115200;
    baudRateComboBox_->GetStringSelection().ToLong(&baudrate);
    sp_set_config_baudrate(portConfig_, baudrate);

    wxString statusTextPar;
    switch(parityChoice_->GetSelection())
    {
    default:
    case 0:
        sp_set_config_parity(portConfig_, SP_PARITY_NONE);
        statusTextPar = _T("N");
        break;
    case 1:
        sp_set_config_parity(portConfig_, SP_PARITY_EVEN);
        statusTextPar = _T("E");
        break;
    case 2:
        sp_set_config_parity(portConfig_, SP_PARITY_ODD);
        statusTextPar = _T("O");
        break;
    case 3:
        sp_set_config_parity(portConfig_, SP_PARITY_MARK);
        statusTextPar = _T("M");
        break;
    case 4:
        sp_set_config_parity(portConfig_, SP_PARITY_SPACE);
        statusTextPar = _T("S");
        break;
    }

    switch(port_tcp_->GetSelection())
    {
    default:
    case 0:
        tcp_port_ = 4243;
        break;
    case 1:
        tcp_port_ = 4242;
        break;
    case 2:
        tcp_port_ = 4244;
        break;
    }

    if ( ctsFlowCheckBox_->GetValue() )
    {
        sp_set_config_flowcontrol(portConfig_, SP_FLOWCONTROL_RTSCTS);
        setStatuslineRTSToggleButton_->Disable();
    }
    else
    {
        sp_set_config_flowcontrol(portConfig_, SP_FLOWCONTROL_NONE);
        setStatuslineRTSToggleButton_->Enable();
    }
    sp_set_config_stopbits(portConfig_, stopBitsChoice_->GetSelection() + 1);

    pauseCounter_ = 0;
    rxLastChar_ = -1;
    txLastChar_ = -1;

    if(sp_get_port_by_name( ports_[portChoice_->GetSelection()].c_str(), &serialPort_) == SP_OK )
    {
        sp_set_bits(serialPort_, 5 + dataWidthChoice_->GetSelection());
        sp_set_config(serialPort_, portConfig_);
        if (sp_open(serialPort_, SP_MODE_READ_WRITE) == SP_OK)
        {
            if(ctsFlowCheckBox_->GetValue())
                sp_set_rts(serialPort_, SP_RTS_FLOW_CONTROL );
            else
                sp_set_rts(serialPort_, SP_RTS_INVALID);

            currentPort_ = portChoice_->GetSelection();
            SetStatuslines();
            rxTimer_.Start(1);
            serverRxTimer_.Start(1);
            tcpserver_->start();
            wxString statusText(_("Connected to "));
            statusText += portChoice_->GetStringSelection();
            statusText += wxString::Format(_T(" (%dbaud, %d"), baudrate, 5 + dataWidthChoice_->GetSelection());
            statusText += statusTextPar;
            statusText += wxString::Format(_T("%d)"), stopBitsChoice_->GetSelection() + 1);

            SetStatusText(statusText);
        }
        else
        {
            Disconnect();
        }
    }
    else
    {
        serialPort_ = NULL;
        SetStatusText(_T("Connect failed"));
    }
}

void DebuggerTerminalFrame::Disconnect()
{
    if(serialPort_)
        sp_close(serialPort_);
    sp_free_port(serialPort_);
    serialPort_ = NULL;
    currentPort_ = -1;
    pauseCounter_ = 0;
    UpdateLineStates(false);
    if(rxTimer_.IsRunning())
        rxTimer_.Stop();
    if(txTimer_.IsRunning())
        txTimer_.Stop();
    if (serverRxTimer_.IsRunning())
        serverRxTimer_.Stop();
    if(fileToSend_.IsOpened())
        fileToSend_.Close();
    if(tcpserver_->conncted())
        tcpserver_->stop();
    SetStatusText(_T("Disconnected"));
}



void DebuggerTerminalFrame::OnConnectToggle(wxCommandEvent &WXUNUSED(event))
{
    if (connectToggleButton_->GetValue())
        Connect();
    else
        Disconnect();
}

void DebuggerTerminalFrame::OnUpdateConnectToggle(wxUpdateUIEvent &WXUNUSED(event))
{
    if(PortIsOpen())
    {
        connectToggleButton_->SetLabel(_T("Disconnect"));
        connectToggleButton_->SetValue(true);
    }
    else
    {
        connectToggleButton_->SetLabel(_T("Connect"));
        connectToggleButton_->SetValue(false);
    }
}

bool DebuggerTerminalFrame::PortIsOpen()
{
    return ((serialPort_ != NULL) && (currentPort_ != -1));
}

void DebuggerTerminalFrame::OnUpdateConnectControls(wxUpdateUIEvent &event)
{
    event.Enable(!PortIsOpen());
}

void DebuggerTerminalFrame::OnTxTimer(wxTimerEvent &WXUNUSED(event))
{
    SendNextChunkOfOpenedFile();
}

void DebuggerTerminalFrame::OnServerReadTimer(wxTimerEvent &event)
{
    io_service_.poll();

    if (tcpserver_->conncted())
    {
        uint8_t *data;
        size_t length = 0;
        tcpserver_->get_received_data(&data, &length); //caller takes ownership of data
        if(length)
        {
            size_t cnt = 0;
            do
            {
                size_t number_of_written_data = sp_nonblocking_write(serialPort_, data+cnt, length-cnt);
                cnt += number_of_written_data;
            }
            while(cnt < length);
            delete[] data;
        }
    }
}

void DebuggerTerminalFrame::OnRxTimer(wxTimerEvent &WXUNUSED(event))
{
    const int BufferLength = 8192;
    bool isOpen = PortIsOpen();
    UpdateLineStates(isOpen);
    if ( isOpen )
    {
        char buffer[BufferLength];
        char *buf = buffer;
        int length = sp_nonblocking_read(serialPort_, buffer, BufferLength);
        if (length < 0)
        {
            // what to do here?
            return;
        }
        if(tcpserver_->conncted())
        {
            if (length)
            {

                tcpserver_->set_transmit_data( reinterpret_cast<uint8_t*>(&buffer[0]), static_cast<size_t>(length)); // data will be copied by callee
            }
        }

        rxStreamCount_ += length;

        if(length)
        {
            int NewlineAfter = autoInsertNewlineSpinCtrl_->GetValue();
            if((NewlineAfter!=0) && (++NewlineAfterCharsCounter == NewlineAfter))
                txDataPanel_->AppendNewline();

            char err = 0;
            txDataPanel_->AppendChar((*buffer), err);
    //        if ( CheckNewline(length,rxLastChar_))
    //                rxDataPanel_->AppendNewline();
        }

        if (length == 0)
            pauseCounter_++;
        else
            pauseCounter_ = 0;
        int PauseNewlineValue = newlineByPauseSpinCtrl_->GetValue();
        if  ( PauseNewlineValue > 0 && PauseNewlineValue == pauseCounter_ )
            rxDataPanel_->AppendNewline();

        while(length--)
        {
            char ch = *buf++;
            if ( ch == (char)(userCharCounterSpin_->GetValue()&0x00ff))
                userStreamCount_++;
            if (clearAtCharCheckBox_->GetValue() && (ch == (char)(clearAtCharCheckSpinCtrl_->GetValue()&0x00ff)))
                rxDataPanel_->Clear();

            int NewlineAfter = autoInsertNewlineSpinCtrl_->GetValue();
            if((NewlineAfter!=0) && (++NewlineAfterCharsCounter == NewlineAfter))
                rxDataPanel_->AppendNewline();

            char err = 0;
            rxDataPanel_->AppendChar(ch, err);
            if ( CheckNewline(ch,rxLastChar_))
                rxDataPanel_->AppendNewline();
            rxLastChar_ = 0x00ff|ch;
        }
        UpdateRxStreamCounter();
        UpdateUserStreamCounter();
    }
}

bool DebuggerTerminalFrame::CheckNewline(char ch, char lastCh)
{
    if ( newLineControlChoice_->GetSelection() == 1 && ch == 0x0D ) // cr
        return true;
    if ( newLineControlChoice_->GetSelection() == 2 && ch == 0x0A ) // lf
        return true;
    if ( newLineControlChoice_->GetSelection() == 3 && ch == 0x0A && lastCh == 0x0D ) // cr + lf
        return true;
    if ( newLineControlChoice_->GetSelection() == 4 && ch == 0x00 ) // Null
        return true;
    if ( newLineControlChoice_->GetSelection() == 5 && ch == 0x03 ) // ETX
        return true;

    return false;
}

void DebuggerTerminalFrame::Transmit(char *buffer, int length)
{

    int idx = 0;
    do
    {
        int lengthTxed = sp_nonblocking_write(serialPort_, buffer + idx, length - idx);
        if (lengthTxed < 0)
        {
            //TODO what do we do here?
            return;
        }
        idx += lengthTxed;
    }
    while(idx < length);

    txStreamCount_ += length;
    while (length--)
    {
        char ch = *buffer++;
        txDataPanel_->AppendChar(ch);
        // TODO (danselmi#1#): detect newline sequence
        if ( false )
            txDataPanel_->AppendNewline();
    }
    UpdateTxStreamCounter();
}

void DebuggerTerminalFrame::UpdateLineStates(bool portIsOpen)
{
    static enum sp_signal signal;
    enum sp_signal new_signal;
    if (portIsOpen)
        sp_get_signals(serialPort_, &new_signal);

    if((signal ^ new_signal) & SP_SIG_CTS)
        (signal & SP_SIG_CTS) ? statuslineCTSLed_->Enable() : statuslineCTSLed_->Disable();

    if((signal ^ new_signal) & SP_SIG_DSR)
        (signal & SP_SIG_DSR) ? statuslineDSRLed_->Enable() : statuslineDSRLed_->Disable();

    if((signal ^ new_signal) & SP_SIG_RI)
        (signal & SP_SIG_RI ) ? statuslineRILed_->Enable()  : statuslineRILed_->Disable();

    if((signal ^ new_signal) & SP_SIG_DCD)
        (signal & SP_SIG_DCD) ? statuslineDCDLed_->Enable() : statuslineDCDLed_->Disable();

    signal = new_signal;
}

void DebuggerTerminalFrame::OnActivate(wxActivateEvent &event)
{
    if (!initDone_)
        return;

    if ( event.GetActive() )
    {
        if ( disconnectOnLostFocus_->IsChecked() && wasConnected_)
            Connect();
    }
    else
    {
        wasConnected_ = false;
        if(PortIsOpen() && disconnectOnLostFocus_->IsChecked())
        {
            wasConnected_ = true;
            Disconnect();
        }
    }
}

void DebuggerTerminalFrame::OnClearReceived(wxCommandEvent &WXUNUSED(event))
{
    rxDataPanel_->Clear();
}

void DebuggerTerminalFrame::OnClearTransmitted(wxCommandEvent &WXUNUSED(event))
{
    txDataPanel_->Clear();
}

void DebuggerTerminalFrame::OnResetTxStreamCounter(wxCommandEvent &event)
{
    txStreamCount_ = 0;
    UpdateTxStreamCounter();
}

void DebuggerTerminalFrame::UpdateTxStreamCounter()
{
    streamTxCounterTextCtrl_->SetValue(wxString::Format(_T("%ld"), txStreamCount_));
}

void DebuggerTerminalFrame::OnResetRxStreamCounter(wxCommandEvent &event)
{
    rxStreamCount_ = 0;
    UpdateRxStreamCounter();
}

void DebuggerTerminalFrame::UpdateRxStreamCounter()
{
    streamRxCounterTextCtrl_->SetValue(wxString::Format(_T("%ld"), rxStreamCount_));
}

void DebuggerTerminalFrame::OnResetUserStreamCounter(wxCommandEvent &event)
{
    userStreamCount_ = 0;
    UpdateUserStreamCounter();
}

void DebuggerTerminalFrame::UpdateUserStreamCounter()
{
    userCharCounterTextCltr_->SetValue(wxString::Format(_T("%ld"), userStreamCount_));
}

void DebuggerTerminalFrame::OnCheckBoxAutoscroll(wxCommandEvent &event)
{
    bool enableautoscroll = event.IsChecked();
    rxDataPanel_->DoAutoscroll(enableautoscroll);
    txDataPanel_->DoAutoscroll(enableautoscroll);

    wxConfigBase::Get()->Write(_T("AutoScroll"), enableautoscroll);
}

void DebuggerTerminalFrame::OnCheckBoxOutputFormat(wxCommandEvent &WXUNUSED(event))
{
    UpdateOutputFormats();
}

void DebuggerTerminalFrame::UpdateOutputFormats()
{
    int format = 0;
    format |= outputFormatASCIICheckBox_->GetValue()?DataPanelAsciiFormat:0;
    format |= outputFormatHEXCheckBox_->GetValue()?DataPanelHexFormat:0;
    format |= outputFormatDECCheckBox_->GetValue()?DataPanelDecFormat:0;
    format |= outputFormatBINCheckBox_->GetValue()?DataPanelBinFormat:0;

    wxConfigBase::Get()->Write(_T("OutputFormat"), format);

    rxDataPanel_->SetOutputFormat(format);
}

void DebuggerTerminalFrame::OnCheckBoxInputFormat(wxCommandEvent &WXUNUSED(event))
{
    UpdateInputFormats();
}

void DebuggerTerminalFrame::UpdateInputFormats()
{
    int format = 0;
    format |= inputFormatASCIICheckBox_->GetValue()?DataPanelAsciiFormat:0;
    format |= inputFormatHEXCheckBox_->GetValue()?DataPanelHexFormat:0;
    format |= inputFormatDECCheckBox_->GetValue()?DataPanelDecFormat:0;
    format |= inputFormatBINCheckBox_->GetValue()?DataPanelBinFormat:0;

    wxConfigBase::Get()->Write(_T("InputFormat"), format);

    txDataPanel_->SetOutputFormat(format);
}

void DebuggerTerminalFrame::OnSetRulerStart(wxCommandEvent& event)
{
    long val = wxGetNumberFromUser(_T("Enter new ruler start value:"), _T(""), _T("Ruler start"), rxDataPanel_->GetRulerStart(), 0, 100);
    if( val != -1)
    {
        rxDataPanel_->SetRulerStart(val&0xff);
        txDataPanel_->SetRulerStart(val&0xff);
    }
}

void DebuggerTerminalFrame::OnMenuShowRuler(wxCommandEvent& event)
{
    bool enable = event.IsChecked();
    rxDataPanel_->EnableRuler(enable);
    txDataPanel_->EnableRuler(enable);
}

void DebuggerTerminalFrame::OnUpdateShowRuler(wxUpdateUIEvent &event)
{
    event.Check(rxDataPanel_->RulerIsEnabled());
}

void DebuggerTerminalFrame::OnMenuClearAll(wxCommandEvent& event)
{
    rxDataPanel_->Clear();
    txDataPanel_->Clear();
}

void DebuggerTerminalFrame::OnMenuChangeFont(wxCommandEvent& event)
{
    wxString title;
    int size;
    if ( event.GetId() == ID_MENU_CHANGERX_FONT)
    {
        title = _T("Received data panel");
        size = rxDataPanel_->GetFontSize();
    }
    else
    {
        title = _T("Transmitted data panel");
        size = txDataPanel_->GetFontSize();
    }

    SelectFontSizeDialog dlg(this, wxID_ANY, title, size);
    if (dlg.ShowModal() == wxID_OK)
    {
        size = dlg.GetFontSize();
        if (event.GetId() == ID_MENU_CHANGERX_FONT)
        {
            rxDataPanel_->SetFontSize(size);
            rxDataPanel_->Refresh();
        }
        else
        {
            txDataPanel_->SetFontSize(size);
            txDataPanel_->Refresh();
        }
    }
}

void DebuggerTerminalFrame::OnToggleLinestate(wxCommandEvent &event)
{
    if (!PortIsOpen())
        return;
    if (event.GetId() == ID_SETSTATUSLINES_DTR_TOGGLEBUTTON )
        SetStatuslineDTR();
    else
        SetStatusLineRTS();
}

void DebuggerTerminalFrame::SetStatuslines()
{
    SetStatuslineDTR();
    SetStatusLineRTS();
}

void DebuggerTerminalFrame::SetStatuslineDTR()
{
    if ( setStatuslineDTRToggleButton_->GetValue())
        sp_set_dtr(serialPort_, SP_DTR_ON); //m_serialPort->SetLineState(ctb::LinestateDtr);
    else
        sp_set_dtr(serialPort_, SP_DTR_OFF); //m_serialPort->ClrLineState(ctb::LinestateDtr);
}

void DebuggerTerminalFrame::SetStatusLineRTS()
{
    if ( setStatuslineRTSToggleButton_->GetValue())
        sp_set_rts(serialPort_, SP_RTS_ON);
    else
        sp_set_rts(serialPort_, SP_RTS_OFF);
}

void DebuggerTerminalFrame::OnSendFile(wxCommandEvent &event)
{
    wxString filename;
    wxString defaultDir = wxConfigBase::Get()->Read(_T("OnSendFileDefaultDir"), _T(""));
    wxString defaultFile = wxConfigBase::Get()->Read(_T("OnSendFileDefaultFile"), _T(""));
    wxString wildcard = wxConfigBase::Get()->Read(_T("OnSendFileWildcard"),  _T("*.*"));

    if(fileToSend_.IsOpened() || (!PortIsOpen()))
        return;

    wxFileDialog dlg(this, _("Choose a file"), defaultDir, defaultFile, wildcard, wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if ( dlg.ShowModal() == wxID_OK)
    {
        filename = dlg.GetPath();
        if(fileToSend_.Open(filename, wxFile::read))
        {
            SendNextChunkOfOpenedFile();
        }
    }
}

void DebuggerTerminalFrame::SendNextChunkOfOpenedFile()
{
    if (!fileToSend_.IsOpened())
    {
        if(txTimer_.IsRunning())
            txTimer_.Stop();
        return;
    }

    int bits = 1 + (5 + dataWidthChoice_->GetSelection()) + ((parityChoice_->GetSelection() == 0) ? 0 : 1);

    bits += stopBitsChoice_->GetSelection() + 1;
    long baudrate = 115200;
    baudRateComboBox_->GetStringSelection().ToLong(&baudrate);
    int wordRate = baudrate/bits;
    size_t len = wordRate/20; // 50ms timer

    sendFileBuffer_ = new char[len];
    size_t read = fileToSend_.Read(sendFileBuffer_, len);

    if(!fileToSend_.Eof())
        txTimer_.Start(50, wxTIMER_ONE_SHOT);
    else
        fileToSend_.Close();

    Transmit(sendFileBuffer_, read);

    delete[] sendFileBuffer_;
}

void DebuggerTerminalFrame::OnUpdateSendFile(wxUpdateUIEvent &event)
{
    event.Enable(!fileToSend_.IsOpened() && PortIsOpen());
}

void DebuggerTerminalFrame::OnInputControlTextEnter(wxCommandEvent &event)
{
    if ( !PortIsOpen())
        return;

    int len = inputControlText_->GetLength();
    char buffer[len];
    inputControlText_->GetValues(buffer);
    inputControlText_->Clear();

    if (sendOnEnterChoice_->GetSelection()== 5 )// STX/ETX
    {
        char ch=0x02;
        Transmit(&ch, 1);
    }

    Transmit(buffer,len);

    len = 0;
    bool doNewline=true;
    switch (sendOnEnterChoice_->GetSelection())
    {
    default:
    case 0:
        doNewline = false;
        break; // none
    case 1:
        len = 1;
        buffer[0] = 0x0D;
        break; // CR
    case 2:
        len = 1;
        buffer[0] = 0x0A;
        break; // LF
    case 3:
        len = 2;
        buffer[0] = 0x0D;
        buffer[1] = 0x0A;
        break;//CR+LF
    case 4:
        len = 1;
        buffer[0] =  ' ';
        break;//SPACE
    case 5:
        len = 1;
        buffer[0] = 0x03;
        break;//STX/ETX
    case 6:
        len = 1;
        buffer[0] = 0x00;
        break;// null
    }
    if ( len != 0)
        Transmit(buffer, len);

    if(doNewline)
        txDataPanel_->AppendNewline();
}

void DebuggerTerminalFrame::OnDefaultLayout(wxCommandEvent& event)
{
    auiManager_->LoadPerspective(defaultPerspective_);

    auiManager_->Update();
}

void DebuggerTerminalFrame::OnShowAll(wxCommandEvent& event)
{
    for (unsigned int i = 0 ; i < windows_.size(); i++)
        auiManager_->GetPane(windows_[i]).Show();
    auiManager_->Update();
}

void DebuggerTerminalFrame::OnUpdateShowOrHidePanel(wxUpdateUIEvent &event)
{
    for ( unsigned int i = 0 ; i < windows_.size(); i++)
        if (event.GetId() == windows_[i]->GetId())
        {
            event.Check(auiManager_->GetPane(windows_[i]).IsShown());
            break;
        }
}

void DebuggerTerminalFrame::OnShowOrHidePanel(wxCommandEvent &event)
{
    for ( unsigned int i = 0 ; i < windows_.size(); i++)
    {
        if (event.GetId() == windows_[i]->GetId())
        {
            if (auiManager_->GetPane(windows_[i]).IsShown())
                auiManager_->GetPane(windows_[i]).Hide();
            else
                auiManager_->GetPane(windows_[i]).Show();
            break;
        }
    }
    auiManager_->Update();
}

void DebuggerTerminalFrame::OnChoiceInputctrlFormat(wxCommandEvent &event)
{
    int format = DataInputControlAsciiFormat;
    int choice = inputControlChoice_->GetSelection();
    if ( choice == 1 ) format = DataInputControlHexFormat;
    if ( choice == 2 ) format = DataInputControlBinFormat;
    //if ( choice == 3 ) format = DataInputControlDecFormat;
    inputControlText_->SetFormat(format);
}

void DebuggerTerminalFrame::OnReceiveBitmaskSelected(wxCommandEvent &event)
{
    char mask = 0xff;

    if (event.GetId() == ID_MENU_RECEIVE_BITMASK_8)
        mask = 0x7f;
    if (event.GetId() == ID_MENU_RECEIVE_BITMASK_8_7)
        mask = 0x3f;
    if (event.GetId() == ID_MENU_RECEIVE_BITMASK_8_6)
        mask = 0x1f;
    if (event.GetId() == ID_MENU_RECEIVE_BITMASK_8_5)
        mask = 0x0f;

    rxDataPanel_->SetBitMask(mask);

    wxConfigBase::Get()->Write(_T("ReceiverBitmask"), (int)(mask&0x000000ff));
}

void DebuggerTerminalFrame::OnUpdateReceiveBitmask(wxUpdateUIEvent &event)
{
    if (!initDone_)
        return;

    char bitmask = rxDataPanel_->GetBitMask();

    bool check = false;

    if ((bitmask == (char)0xff) && (event.GetId() == ID_MENU_RECEIVE_BITMASK_NONE))
        check = true;
    if ((bitmask == 0x7f) && (event.GetId() == ID_MENU_RECEIVE_BITMASK_8))
        check = true;
    if ((bitmask == 0x3f) && (event.GetId() == ID_MENU_RECEIVE_BITMASK_8_7))
        check = true;
    if ((bitmask == 0x1f) && (event.GetId() == ID_MENU_RECEIVE_BITMASK_8_6))
        check = true;
    if ((bitmask == 0x0f) && (event.GetId() == ID_MENU_RECEIVE_BITMASK_8_5))
        check = true;

    event.Check(check);
}

