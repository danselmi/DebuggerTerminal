#ifndef DATAINPUTCONTROL_H
#define DATAINPUTCONTROL_H

#include <wx/panel.h>
#include <wx/control.h>

#include <vector>

#define DataInputControlAsciiFormat 0x0001
#define DataInputControlHexFormat   0x0002
#define DataInputControlBinFormat   0x0004
//#define DataInputControlDecFormat   0x0008

class DataInputControlPanel : public wxControl/*, public wxPanel*/
{
public:
    DataInputControlPanel(wxWindow *parent, wxWindowID id);
    virtual ~DataInputControlPanel();

    void SetFormat(int format, bool force = false);
    unsigned int GetLength();
    void GetValues(char *buffer);
    void Clear();

protected:
private:
    void OnChar(wxKeyEvent &event);
    void OnPaint(wxPaintEvent &event);
    void OnSetFocus(wxFocusEvent &event);
    void OnKillFocus(wxFocusEvent &event);
    void OnLeftDown(wxMouseEvent &event);
    void Paint(wxDC&  dc);
    void UpdateStepSize();
    void AdjustCaretPos();
    void MoveCaretLeft(int keycode);
    void MoveCaretRight(int keycode);
    void DoDelete(int keycode);
    void DeleteHexDigit();
    void DeleteBit();
    void DeleteAsciiDigit();

    int format_;
    //std::vector<char> data_;
    unsigned int dataCapacity_;
    char *data_;
    unsigned int dataLength_;
    unsigned int dataSubLength_;
    void Resize();

    wxCoord stepSize_;
    wxSize charSize_;
    unsigned int caretPos_;
    unsigned int caretSubPos_;

private:
    void AddAsciiDigit(char val);
    void AddBit(char val);
    //void AddDecDigit(char val);
    void AddHexDigit(char val);
    const unsigned int LeftOffset()const{return 3;}
    const unsigned int TopOffset()const{return 3;}


private:
    DECLARE_EVENT_TABLE()
};


class DataInputControl : public DataInputControlPanel
{
public:
    DataInputControl(wxWindow *parent, wxWindowID id):
    DataInputControlPanel(parent, id){}
    virtual ~DataInputControl(){}
};
//class DataInputControl : public wxControl
//{
//public:
//    DataInputControl(wxWindow *parent, wxWindowID id):
//    wxControl(parent, wxID_ANY/*, wxDefaultPosition, wxDefaultSize, wxBORDER_SUNKEN*/)
//    {
//        panel = new DataInputControlPanel(this, id);
//    }
//    virtual ~DataInputControl(){}
//public:
//    void SetFormat(int format, bool force = false){panel->SetFormat(format, force);}
//    unsigned int GetLength(){return panel->GetLength();}
//    void GetValues(char *buffer){panel->GetValues(buffer);}
//    void Clear(){panel->Clear();}
//private:
//    DataInputControlPanel *panel;
//};

#endif // DATAINPUTCONTROL_H
