#ifndef DATAINPUTCONTROL_H
#define DATAINPUTCONTROL_H

#include <wx/textctrl.h>
//#include <wx/panel.h>
//#include <wx/control.h>

#include <vector>

#define DataInputControlAsciiFormat 0x0001
#define DataInputControlHexFormat   0x0002
#define DataInputControlDecFormat   0x0004
#define DataInputControlBinFormat   0x0008

class DataInputControl : public wxTextCtrl
{
public:
    DataInputControl(wxWindow *parent, wxWindowID id);
    virtual ~DataInputControl();

    void SetFormat(int format, bool force = false);
protected:
private:
    void OnChar(wxKeyEvent &event);
    virtual void Copy();
    virtual void Cut();
    virtual void Clear();

    int m_format;
    std::vector<char> m_data;


private:
    DECLARE_EVENT_TABLE()
};

#endif // DATAINPUTCONTROL_H
