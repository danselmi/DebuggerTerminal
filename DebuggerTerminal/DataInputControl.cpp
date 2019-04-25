#include "DataInputControl.h"

//#include <wx/clipbrd.h>
//#include <wx/dataobj.h>
#include <wx/dcclient.h>
#include <wx/msgdlg.h>
#include <wx/caret.h>
#include <wx/textctrl.h>

//{
BEGIN_EVENT_TABLE(DataInputControlPanel,wxControl)
    EVT_CHAR      (DataInputControlPanel::OnChar)
    EVT_PAINT     (DataInputControlPanel::OnPaint)
    EVT_SET_FOCUS (DataInputControlPanel::OnSetFocus)
    EVT_KILL_FOCUS(DataInputControlPanel::OnKillFocus)
    EVT_LEFT_DOWN (DataInputControlPanel::OnLeftDown)
END_EVENT_TABLE()
//}


DataInputControlPanel::DataInputControlPanel(wxWindow *parent, wxWindowID id):
wxControl(parent, id, wxDefaultPosition, wxDefaultSize, wxBORDER_SUNKEN),
dataCapacity_(512),
data_(new char[dataCapacity_])
{
    //ctor
    //dataCapacity_ = 512;
    //data_ = new char[dataCapacity_];
    dataLength_ = 0;
    dataSubLength_ = 0;
    SetCaret(new wxCaret(this, 1, 1));
    caretPos_ = 0;
    caretSubPos_ = 0;

    wxWindow::SetBackgroundColour(*wxWHITE);//wxSystemSettings::GetColour());
    SetFont(wxFont(10, wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL));
    SetFormat(DataInputControlAsciiFormat, true);
    UpdateStepSize();

    AdjustCaretPos();
    bool hasFocus = FindFocus() == this;
    if (hasFocus && !GetCaret()->IsVisible())
        GetCaret()->Show();
    else if (!hasFocus && GetCaret()->IsVisible() )
        GetCaret()->Hide();
}

DataInputControlPanel::~DataInputControlPanel()
{
    //dtor
    delete[] data_;
    data_ = NULL;
    dataCapacity_ = 0;
}
void DataInputControlPanel::OnSetFocus(wxFocusEvent &event)
{
    if (!GetCaret()->IsVisible())
        GetCaret()->Show();
}
void DataInputControlPanel::OnKillFocus(wxFocusEvent &event)
{
    if (GetCaret()->IsVisible())
        GetCaret()->Hide();
}
void DataInputControlPanel::OnPaint(wxPaintEvent & event)
{
    wxPaintDC dc(this);
    Paint(dc);
}
void DataInputControlPanel::Paint(wxDC&  dc)
{
    dc.SetFont(GetFont());
    //dc.SetPen(*wxBLACK_PEN);
    wxPoint offset(0,0);

    wxPoint pos(stepSize_, TopOffset());

#if defined(__WXMSW__)
    pos.y += 1.5*charSize_.y;
#endif
    unsigned int length = dataLength_;
    if (dataSubLength_)
        length++;
    for (unsigned int i = 0; i < length ;i++)
    {
        wxString str;
        unsigned short val = 0x00ff&data_[i];
        if (format_ == DataInputControlAsciiFormat)
        {
            str = wxString::Format(_T("%c"), (char)(val));
            dc.SetBrush(wxBrush(GetBackgroundColour()));
            dc.SetPen(wxPen(GetBackgroundColour()));
            dc.DrawRectangle(pos.x-stepSize_+1, pos.y, stepSize_-1,charSize_.y+1);
            dc.DrawText(str, pos.x-charSize_.x*str.length(), pos.y);
        }
        if (format_ == DataInputControlBinFormat)
        {
            unsigned short tmp = val;
            str = wxEmptyString;
            unsigned int range = 7;
            for (unsigned short k = 0; k <= range ; k++)
            {
                str = ((tmp & 0x0001)?_T("1"):_T("0")) + str;
                tmp >>= 1;
            }
            dc.SetBrush(wxBrush(wxColor(0xc0,0xff,0xc0)));
            dc.SetPen(wxPen(wxColor(0xc0,0xff,0xc0)));
            dc.DrawRectangle(pos.x-stepSize_+1, pos.y, stepSize_-1,charSize_.y+1);
            dc.DrawText(str, pos.x-charSize_.x*str.length(), pos.y);
        }
//        if (format_ == DataInputControlDecFormat)
//        {
//            str = wxString::Format(_T("%d"), val);
//            dc.SetBrush(wxBrush(wxColor(0xff,0xc0,0xc0)));
//            dc.SetPen(wxPen(wxColor(0xff,0xc0,0xc0)));
//            dc.DrawRectangle(pos.x-stepSize_+1, pos.y, stepSize_-1,charSize_.y+1);
//            dc.DrawText(str, pos.x-charSize_.x*str.length(), pos.y);
//        }
        if (format_ == DataInputControlHexFormat)
        {
            str = wxString::Format(_T("%02x"), val);
            dc.SetBrush(wxBrush(wxColor(0xc0,0xc0,0xff)));
            dc.SetPen(wxPen(wxColor(0xc0,0xc0,0xff)));
            dc.DrawRectangle(pos.x-stepSize_+1, pos.y, stepSize_-1,charSize_.y+1);
            dc.DrawText(str, pos.x-charSize_.x*str.length(), pos.y);
        }
        pos.x += stepSize_;
    }
    wxString str(wxString::Format(_T("caret: %d,%d   data: %d,%d"), caretPos_, caretSubPos_, dataLength_, dataSubLength_));
    wxCoord x, y;
    dc.GetTextExtent(str, &x, &y);
    dc.DrawText(str, GetSize().x-x-20, pos.y);//*/
}
void DataInputControlPanel::OnChar(wxKeyEvent &event)
{
    int keycode = event.GetKeyCode();
    if ( keycode ==  WXK_RETURN)
    {
        wxCommandEvent evt;
        evt.SetId(GetId());
        evt.SetEventType(wxEVT_COMMAND_TEXT_ENTER);
        ProcessEvent(evt);
        return;
    }

    if ( keycode == WXK_LEFT )
    {
        MoveCaretLeft(keycode);
        return;
    }
    if ( keycode == WXK_RIGHT )
    {
        MoveCaretRight(keycode);
        return;
    }

    if ( keycode == WXK_BACK || keycode == WXK_DELETE)
    {
        DoDelete(keycode);
        return;
    }


    if (event.HasModifiers() ||  keycode > 127 /*ascii only*/ || keycode == WXK_RETURN || keycode == WXK_ESCAPE )
        return;


    switch (format_)
    {
    default:
    case DataInputControlAsciiFormat:
        AddAsciiDigit((char)keycode);
        break;
    case DataInputControlBinFormat:
        if (keycode == '0' || keycode == '1' )
            AddBit(keycode - '0');
        break;
//    case DataInputControlDecFormat:
//        if (keycode >= '0' && keycode <= '9' )
//            AddDecDigit(keycode - '0');
//        break;
    case DataInputControlHexFormat:
        if (keycode >= '0' && keycode <= '9' )
            AddHexDigit(keycode - '0');
        else if (keycode >= 'a' && keycode <= 'f' )
            AddHexDigit(10 + keycode - 'a');
        else if (keycode >= 'A' && keycode <= 'F' )
            AddHexDigit(10 + keycode - 'A');
        break;
    }
}
void DataInputControlPanel::MoveCaretLeft(int keycode)
{
    if (caretSubPos_ > 0 && format_ != DataInputControlAsciiFormat )
        caretSubPos_ --;
    else
    {
        if (caretPos_ > 0)
        {
            caretPos_ --;
            if (format_ == DataInputControlAsciiFormat) caretSubPos_ = 0; else
            if (format_ == DataInputControlBinFormat) caretSubPos_ = 7;   else
            //if (format_ == DataInputControlDecFormat) caretSubPos_ = 2;   else
            if (format_ == DataInputControlHexFormat) caretSubPos_ = 1;
        }
    }
    AdjustCaretPos();
    Refresh(); /// /////////////////////////////////////////////////////
}
void DataInputControlPanel::MoveCaretRight(int keycode)
{
    if (caretSubPos_ == dataSubLength_ && caretPos_ == dataLength_)
        return;
    if ( format_ == DataInputControlAsciiFormat )
    {
        caretPos_++;
        caretSubPos_ = 0;
        if (caretPos_ > dataLength_)
            caretPos_ = dataLength_;
    }
    else
    {
        unsigned int maxSubPos = 0;
        if (format_ == DataInputControlBinFormat ) maxSubPos = 7;else
        //if (format_ == DataInputControlDecFormat ) maxSubPos = 2;else
        if (format_ == DataInputControlHexFormat ) maxSubPos = 1;

        if (caretSubPos_ < maxSubPos )
        {
            caretSubPos_++;
        }
        else
        {
            caretSubPos_ = 0;
            caretPos_++;
            if (caretPos_ > dataLength_)
                caretPos_ = dataLength_;
        }
    }
    AdjustCaretPos();
    Refresh(); /// /////////////////////////////////////////////////////
}
void DataInputControlPanel::DoDelete(int keycode)
{
    if (dataLength_ == 0 && dataSubLength_ == 0 )
        return;
    if ((keycode == WXK_BACK && caretPos_ == 0 && caretSubPos_ == 0))
        return;
    if ((keycode == WXK_DELETE && caretPos_ == dataLength_))
    {
        if (format_ == DataInputControlAsciiFormat )
            return;
        if (caretSubPos_ == dataSubLength_ )
            return;
    }
    switch (format_)
    {
    default:
    case DataInputControlAsciiFormat:
        if (keycode == WXK_BACK)
            caretPos_--;
        DeleteAsciiDigit();
        return;
    case DataInputControlBinFormat:
        if (keycode == WXK_BACK)
        {
            if(caretSubPos_)
                caretSubPos_--;
            else
            {
                caretPos_--;
                caretSubPos_ = 7;
            }
        }
        DeleteBit();
        return;
//        case DataInputControlDecFormat:
//            break;
    case DataInputControlHexFormat:
        if (keycode == WXK_BACK)
        {
            if(caretSubPos_)
                caretSubPos_--;
            else
            {
                caretPos_--;
                caretSubPos_ = 1;
            }
        }
        DeleteHexDigit();
        return;
    }
}
void DataInputControlPanel::DeleteHexDigit()
{

    if (caretSubPos_)
        data_[caretPos_] &= 0xF0;
    else
        data_[caretPos_] <<= 4;
    if (caretPos_ != dataLength_)
        data_[caretPos_] |= (((data_[caretPos_+1])>>4)&0x0F);


    unsigned int p = caretPos_+1;
    unsigned int length = dataLength_;
    if (dataSubLength_)
        length++;
    for ( ; p < length ; p++)
        data_[p] = (data_[p]<<4) | (((data_[p+1])>>4)&0x0F);


    if (dataSubLength_ == 0)
    {
        dataSubLength_ = 1;
        dataLength_--;
    }
    else
        dataSubLength_ --;

    AdjustCaretPos();
    Refresh();
}
void DataInputControlPanel::DeleteBit()
{
    char mask= 0x00;
    for (unsigned int i = caretSubPos_; i ; i--)
        mask = (mask >> 1) | 0x80;

    data_[caretPos_] = (data_[caretPos_]&mask) | ((data_[caretPos_]<<1)&~mask);
    if (caretPos_ != dataLength_)
        data_[caretPos_] |= (data_[caretPos_+1]&0x80)?0x01:0x00;


    unsigned int p = caretPos_+1;
    unsigned int length = dataLength_;
    if (dataSubLength_)
        length++;
    for ( ; p < length ; p++)
        data_[p] = (data_[p]<<1) | ((data_[p+1]&0x80)?0x01:0x00);

    if (dataSubLength_ == 0)
    {
        dataSubLength_ = 7;
        dataLength_--;
    }
    else
        dataSubLength_ --;

    AdjustCaretPos();
    Refresh();
}
void DataInputControlPanel::DeleteAsciiDigit()
{
    dataLength_--;
    for(unsigned int p = caretPos_ ; p < dataLength_ ; p++)
        data_[p] = data_[p+1];

    AdjustCaretPos();
    Refresh();
    return;
}
void DataInputControlPanel::AddAsciiDigit(char val)
{
    Resize();
    caretSubPos_ = 0; // not needed in ASCII mode
    dataSubLength_ = 0;

    if (caretPos_ > dataLength_) caretPos_ = dataLength_;

    for ( unsigned int p = dataLength_ ; p > caretPos_; p-- )
        data_[p] = data_[p-1];
    data_[caretPos_++] = val;
    dataLength_++;

    AdjustCaretPos();
    Refresh();
}
void DataInputControlPanel::AddBit(char val)
{
    if (dataSubLength_ == 0)
        Resize();

    if (caretPos_ > dataLength_)
    {
        caretPos_ = dataLength_;
        caretSubPos_ = dataSubLength_;
    }

    if (dataSubLength_ == 0) //// make the next byte occupie with the new/shifted bit
        data_[dataLength_] = 0x00;
    for(unsigned int p=dataLength_ ; p > caretPos_ ; p-- )
        data_[p] = ((data_[p-1]&0x01)?0x80:0x00) | ((data_[p]>>1)&0x7F);

    unsigned char nBit = val?0x80:0x00;
    unsigned char lMask= 0x00;
    for (unsigned int i = caretSubPos_; i ; i--)
    {
        nBit >>= 1;
        lMask = (lMask >> 1) | 0x80;
    }
    data_[caretPos_] = (data_[caretPos_]& lMask) | (nBit) | ((unsigned char)(data_[caretPos_]& (~lMask))>>1);

    caretSubPos_++;
    if (caretSubPos_ == 8)
    {
        caretSubPos_ = 0;
        caretPos_++;
    }

    dataSubLength_++;
    if(dataSubLength_ == 8)
    {
        dataSubLength_ = 0;
        dataLength_++; // point to the first unused place
    }

    AdjustCaretPos();
    Refresh();
}
void DataInputControlPanel::AddHexDigit(char val)
{
    if (dataSubLength_ == 0)
        Resize();

    if (caretPos_ > dataLength_)
    {
        caretPos_ = dataLength_;
        caretSubPos_ = dataSubLength_;
    }

    if (dataSubLength_ == 0) // make the next byte occupie with the new/shifted nibble
        data_[dataLength_] = 0x00;
    for(unsigned int p = dataLength_; p > caretPos_ ; p-- )
        data_[p] = ((data_[p-1]<<4)&0xF0) | ((data_[p]>>4)&0x0F);

    if (caretSubPos_== 0)
        data_[caretPos_] = ((data_[caretPos_] >> 4)&0x0F) | (val << 4);
    else
        data_[caretPos_] = (data_[caretPos_]&0xF0) | val;

    caretSubPos_++;
    if (caretSubPos_ == 2)
    {
        caretSubPos_ = 0;
        caretPos_++;
    }
    dataSubLength_++;
    if(dataSubLength_ == 2)
    {
        dataSubLength_ = 0;
        dataLength_++; // point to the first unused place
    }

    AdjustCaretPos();
    Refresh();
}
//void DataInputControlPanel::AddDecDigit(char val)
//{
//
//    AdjustCaretPos();
//    Refresh();
//}
void DataInputControlPanel::Resize()
{
    if (dataLength_ < dataCapacity_)
        return;

    char *ndata = new char[dataCapacity_*2];
    for ( unsigned int i = 0; i < dataLength_ ; i++)
        ndata[i] = data_[i];

    delete[] data_;

    data_ = ndata;
}
void DataInputControlPanel::AdjustCaretPos()
{

    wxCoord posy = TopOffset()
#if defined(__WXMSW__)
    + 1.5*charSize_.y
#endif
    ;
    GetCaret()->Move(LeftOffset()+caretPos_*stepSize_ + caretSubPos_*charSize_.x, posy);
}
void DataInputControlPanel::SetFormat(int format, bool force )
{
    if ( !force && format_ == format) return;

    format_ = format;
    UpdateStepSize();
    caretSubPos_ = 0;
    dataSubLength_ = 0;
    AdjustCaretPos();
    Refresh();
}
void DataInputControlPanel::UpdateStepSize()
{
    GetTextExtent(_T("H"), &charSize_.x, &charSize_.y);
    GetCaret()->SetSize(1, charSize_.y);

    if (format_ == DataInputControlAsciiFormat) stepSize_ = charSize_.x;
    if (format_ == DataInputControlBinFormat)   stepSize_ = charSize_.x*8;
    //if (format_ == DataInputControlDecFormat)   stepSize_ = charSize_.x*3;
    if (format_ == DataInputControlHexFormat)   stepSize_ = charSize_.x*2;

    stepSize_ += LeftOffset();
}

unsigned int DataInputControlPanel::GetLength()
{
    return dataLength_;
}
void DataInputControlPanel::GetValues(char *buffer)
{
    for (unsigned int i = 0 ; i < dataLength_; i++)
        *buffer++ = data_[i];
}
void DataInputControlPanel::Clear()
{
    dataLength_ = 0;
    dataSubLength_ = 0;
    caretPos_ = 0;
    caretSubPos_ = 0;
    AdjustCaretPos();
    Refresh();
}
void DataInputControlPanel::OnLeftDown(wxMouseEvent &event)
{
    wxCoord x= event.GetX()-LeftOffset();
    unsigned int maxSubPos = 0;
    if ( format_ == DataInputControlBinFormat ) maxSubPos = 7;
    //if ( format_ == DataInputControlDecFormat ) maxSubPos = 2;
    if ( format_ == DataInputControlHexFormat ) maxSubPos = 1;


    caretPos_ = x / stepSize_;
    x -= caretPos_*stepSize_;

    caretSubPos_ = x / charSize_.x;
    if ( caretSubPos_ > maxSubPos )
    {
        ++caretPos_;
        caretSubPos_ = 0;
    }

    if ( caretPos_ > dataLength_ )
    {
        caretPos_ = dataLength_;
        caretSubPos_ = dataSubLength_;
    }
    else if ( caretPos_ == dataLength_ )
    {
        if ( caretSubPos_ > dataSubLength_ )
            caretSubPos_ = dataSubLength_;
    }

    event.Skip();
    AdjustCaretPos();
    Refresh();
}

