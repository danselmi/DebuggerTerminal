#ifndef DEBUGGERTERMINALMAIN_H
#define DEBUGGERTERMINALMAIN_H

#include <wx/aui/aui.h>
#include <wx/tglbtn.h>
#include <wx/choice.h>
#include <wx/combobox.h>
#include <wx/checkbox.h>
#include <wx/button.h>
#include <wx/spinctrl.h>
#include <wx/file.h>

#include <wx/frame.h>
#include "led.h"
#include "DataPanel.h"
#include "DataInputControl.h"

class DebuggerTerminalFrame: public wxFrame
{
    public:

        DebuggerTerminalFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~DebuggerTerminalFrame();

    private:
        bool initDone;
        wxString defaultPerspective;

    private:
        void CreateConnectionToolBar();
        void CreateStreamCounterToolBar();
        void CreateUserCharCounterToolBar();
        void CreateNewLineControlToolBar();
        void CreateClearInputOutputToolBar();
        void CreateOutputFormatToolBar();
        void CreateInputFormatToolBar();
        void CreateSaveOutputToolBar();
        void CreateClearAtCharToolBar();
        void CreateAutoInserNewlineToolBar();
        void CreateOutputOptionsToolBar();
        void CreateNewlineByPauseToolBar();
        void CreateStatuslinesToolBar();
        void CreateSetStatuslinesToolBar();
        void CreateSendFileToolBar();
        void CreateSendOnEnterToolBar();
        void CreateInputControlToolBar();
        void InitMenuBar();

        void  UpdateLineStates(bool portOpen=false);

        void Transmit(char *buffer, int length);

    private:
        void OnRxTimer(wxTimerEvent &event);
        void OnTxTimer(wxTimerEvent &event);
        void OnServerreadTimer(wxTimerEvent &event);
        void OnPortRescan(wxCommandEvent &event);
        void OnConnectToggle(wxCommandEvent &event);
        void OnToggleLinestate(wxCommandEvent &event);
        void OnUpdateConnectToggle(wxUpdateUIEvent &event);
        void OnUpdateConnectControls(wxUpdateUIEvent &event);
        void OnUpdateSendFile(wxUpdateUIEvent &event);
        void OnUpdateShowRuler(wxUpdateUIEvent &event);
        //void OnSetFocus(wxFocusEvent &event);
        //void OnKillFocus(wxFocusEvent &event);
        void OnActivate(wxActivateEvent &event);
        void OnClearReceived(wxCommandEvent &event);
        void OnClearTransmitted(wxCommandEvent &event);
        void OnChoiceInputctrlFormat(wxCommandEvent &event);

    private:
        int pauseCounter_;
        unsigned long txStreamCount_;
        unsigned long rxStreamCount_;
        void OnResetTxStreamCounter(wxCommandEvent &event);
        void OnResetRxStreamCounter(wxCommandEvent &event);
        void UpdateTxStreamCounter();
        void UpdateRxStreamCounter();

        unsigned long userStreamCount_;
        void UpdateUserStreamCounter();
        void OnResetUserStreamCounter(wxCommandEvent &event);

        void OnCheckBoxAutoscroll(wxCommandEvent &event);
        void OnCheckBoxOutputFormat(wxCommandEvent &event);
        void OnCheckBoxInputFormat(wxCommandEvent &event);
        void UpdateOutputFormats();
        void UpdateInputFormats();

        void OnSendFile(wxCommandEvent &event);
        void OnInputControlTextEnter(wxCommandEvent& event);
        void OnUpdateShowOrHidePanel(wxUpdateUIEvent &event);
        void OnUpdateReceiveBitmask(wxUpdateUIEvent &event);
        void OnReceiveBitmaskSelected(wxCommandEvent &event);
        void OnShowOrHidePanel(wxCommandEvent &event);

    private:
        wxTimer rxTimer_;
        wxTimer txTimer_;
        wxTimer serverRxTimer_;
        struct sp_port *serialPort_;
        struct sp_port_config *portConfig_;
        bool wasConnected_;
        void UpdatePortList();
        void initPortsList();
        wxArrayString ports_;
        int currentPort_;
        void Connect();
        void Disconnect();
        bool PortIsOpen();
        int NewlineAfterCharsCounter;
        void SetStatuslines();
        void SetStatuslineDTR();
        void SetStatusLineRTS();
        void SendNextChunkOfOpenedFile();
        bool CheckNewline(char ch, char lastCh);
        short rxLastChar_, txLastChar_;

    private:
        wxAuiManager *auiManager_;
        wxAuiNotebook *auiNotebook_;
        std::vector< wxWindow* > windows_;

        wxToggleButton *connectToggleButton_;
        wxChoice *portChoice_;
        wxComboBox *baudRateComboBox_;
        wxChoice *dataWidthChoice_;
        wxChoice *stopBitsChoice_;
        wxChoice *parityChoice_;
        wxCheckBox *ctsFlowCheckBox_;
        wxMenuItem *disconnectOnLostFocus_;

        wxTextCtrl *streamRxCounterTextCtrl_;
        wxTextCtrl *streamTxCounterTextCtrl_;

        wxSpinCtrl *userCharCounterSpin_;
        wxTextCtrl *userCharCounterTextCltr_;

        wxChoice *newLineControlChoice_;

        wxCheckBox *outputFormatASCIICheckBox_;
        wxCheckBox *outputFormatHEXCheckBox_;
        wxCheckBox *outputFormatDECCheckBox_;
        wxCheckBox *outputFormatBINCheckBox_;

        wxCheckBox *inputFormatASCIICheckBox_;
        wxCheckBox *inputFormatHEXCheckBox_;
        wxCheckBox *inputFormatDECCheckBox_;
        wxCheckBox *inputFormatBINCheckBox_;

        wxCheckBox *clearAtCharCheckBox_;
        wxSpinCtrl *clearAtCharCheckSpinCtrl_;

        wxSpinCtrl *autoInsertNewlineSpinCtrl_;
        wxSpinCtrl *newlineByPauseSpinCtrl_;

        wxLed *statuslineCTSLed_;
        wxLed *statuslineDSRLed_;
        wxLed *statuslineRILed_;
        wxLed *statuslineDCDLed_;

        wxToggleButton *setStatuslineDTRToggleButton_;
        wxToggleButton *setStatuslineRTSToggleButton_;

        wxChoice *sendOnEnterChoice_;

        wxChoice *inputControlChoice_;
        DataInputControl *inputControlText_;

        wxFile fileToSend_;
        char *sendFileBuffer_;

        DataPanel *rxDataPanel_;
        DataPanel *txDataPanel_;

        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnSetRulerStart(wxCommandEvent& event);
        void OnMenuShowRuler(wxCommandEvent& event);
        void OnMenuClearAll(wxCommandEvent& event);
        void OnMenuChangeFont(wxCommandEvent& event);
        void OnDefaultLayout(wxCommandEvent& event);
        void OnShowAll(wxCommandEvent& event);

        static const long ID_MENU_QUIT;
        static const long ID_MENU_ABOUT;
        static const long ID_MENU_SHOW_RULER;
        static const long ID_MENU_SET_RULER_START;
        static const long ID_MENU_CONNECTONFOCUS;
        static const long ID_MENU_CLEAR_ALL;
        static const long ID_MENU_CHANGERX_FONT;
        static const long ID_MENU_CHANGETX_FONT;
        static const long ID_MENU_MODIFY_NEWLINE_AT;
        static const long ID_MENU_MODIFY_SEND_ON_ENTER;
        //static const long ID_MENU_RECEIVE_BITMASK;
        static const long ID_MENU_RECEIVE_BITMASK_NONE;
        static const long ID_MENU_RECEIVE_BITMASK_8;
        static const long ID_MENU_RECEIVE_BITMASK_8_7;
        static const long ID_MENU_RECEIVE_BITMASK_8_6;
        static const long ID_MENU_RECEIVE_BITMASK_8_5;
        static const long ID_MENU_SHOW_ALL_PANES;
        static const long ID_MENU_DEFAULT_LAYOUT;
        static const long ID_MENU_SAVE_LAYOUT;
        static const long ID_MENU_LOAD_LAYOUT;

        static const long ID_RXDATA_PANEL;
        static const long ID_TXDATA_PANEL;
        static const long ID_INPUTCTRL_PANEL;

        static const long ID_CONNECTION_TOOLBAR;
        static const long ID_CONNECT_TOGGLEBUTTON;
        static const long ID_PORT_CHOICE;
        static const long ID_PORT_RESCAN_BUTTON;
        static const long ID_BAUDRATE_COMBOBOX;
        static const long ID_DATA_WIDTH_CHOICE;
        static const long ID_STOPBITS_CHOICE;
        static const long ID_PARITY_CHOICE;
        static const long ID_CTSFLOW_CHECKBOX;

        static const long ID_STREAMCOUNTER_TOOLBAR;
        static const long ID_STREAMCOUNTER_RX_TEXT;
        static const long ID_STREAMCOUNTER_TX_TEXT;
        static const long ID_STREAMCOUNTER_RX_BUTTON;
        static const long ID_STREAMCOUNTER_TX_BUTTON;

        static const long ID_USERCHARCOUNTER_TOOLBAR;
        static const long ID_USERCHARCOUNTER_SPINCTRL;
        static const long ID_USERCHARCOUNTER_TEXT;
        static const long ID_USERCHARCOUNTER_BUTTON;

        static const long ID_NEWLINECONTROL_TOOLBAR;
        static const long ID_NEWLINECONTROL_CHOICE;
        static const long ID_NEWLINECONTROL_CHECKBOX;

        static const long ID_CLEAR_TOOLBAR;
        static const long ID_CLEARRECEIVED_BUTTON;
        static const long ID_CLEARTRANSMITTED_BUTTON;

        static const long ID_OUTPUTFORMAT_TOOLBAR;
        static const long ID_OUTPUTFORMAT_ASCII_CHECKBOX;
        static const long ID_OUTPUTFORMAT_HEX_CHECKBOX;
        static const long ID_OUTPUTFORMAT_DEC_CHECKBOX;
        static const long ID_OUTPUTFORMAT_BIN_CHECKBOX;
        static const long ID_INPUTFORMAT_TOOLBAR;
        static const long ID_INPUTFORMAT_ASCII_CHECKBOX;
        static const long ID_INPUTFORMAT_HEX_CHECKBOX;
        static const long ID_INPUTFORMAT_DEC_CHECKBOX;
        static const long ID_INPUTFORMAT_BIN_CHECKBOX;

        static const long ID_SAVEOUTPUT_TOOLBAR;
        static const long ID_SAVEOUTPUT_BUTTON;
        static const long ID_SAVEOUTPUT_SETTINGS_BUTTON;

        static const long ID_CLEARATCHAR_TOOLBAR;
        static const long ID_CLEARATCHAR_CHECKBOX;
        static const long ID_CLEARATCHAR_SPINCTRL;

        static const long ID_AUTOINSERTNEWLIN_TOOLBAR;
        static const long ID_AUTOINSERTNEWLIN_SPINCTRL;

        static const long ID_OUTPUTOPTIONS_TOOLBAR;
        static const long ID_OUTPUTOPTIONS_AUTOSCROLL_CHECKBOX;
        static const long ID_OUTPUTOPTIONS_SHOWERR_CHECKBOX;

        static const long ID_NEWLINEBYPAUSE_TOOLBAR;
        static const long ID_NEWLINEBYPAUSE_SPINCTRL;

        static const long ID_STATUSLINES_TOOLBAR;
        static const long ID_STATUSLINES_CTSLED;
        static const long ID_STATUSLINES_DSRLED;
        static const long ID_STATUSLINES_RILED;
        static const long ID_STATUSLINES_DCDLED;

        static const long ID_SETSTATUSLINES_TOOLBAR;
        static const long ID_SETSTATUSLINES_DTR_TOGGLEBUTTON;
        static const long ID_SETSTATUSLINES_RTS_TOGGLEBUTTON;

        static const long ID_SENDONENTER_TOOLBAR;
        static const long ID_SENDONENTER_CHOICE;

        static const long ID_SENDFILE_TOOLBAR;
        static const long ID_SENDFILE_BUTTON;

        static const long ID_INPUTCONTROL_TOOLBAR;
        static const long ID_INPUTCONTROL_CHOICE;
        static const long ID_INPUTCONTROL_TEXT;
        static const long ID_INPUTCONTROL_BUTTON;

        static const long ID_RX_TIMER;
        static const long ID_TX_TIMER;

        DECLARE_EVENT_TABLE()
};

#endif
