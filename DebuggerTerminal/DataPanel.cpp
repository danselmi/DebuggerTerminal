#include "DataPanel.h"

#include <wx/dcclient.h>
#include <wx/settings.h>

const long DataPanel::ID_DATA_PANEL_TIMER = wxNewId();
namespace{
    const char ParErr   = 0x01;
    const char FrameErr = 0x02;
    const char NewLine  = 0x04;
};

IMPLEMENT_DYNAMIC_CLASS(DataPanel, wxPanel)

BEGIN_EVENT_TABLE(DataPanel,wxPanel)
    // some useful events
    /*
    EVT_MOTION(BasicDrawPane::mouseMoved)
    EVT_LEFT_DOWN(BasicDrawPane::mouseDown)
    EVT_LEFT_UP(BasicDrawPane::mouseReleased)
    EVT_RIGHT_DOWN(BasicDrawPane::rightClick)
    EVT_LEAVE_WINDOW(BasicDrawPane::mouseLeftWindow)
    EVT_KEY_DOWN(BasicDrawPane::keyPressed)
    EVT_KEY_UP(BasicDrawPane::keyReleased)
    EVT_MOUSEWHEEL(BasicDrawPane::mouseWheelMoved)
    */
    // catch paint events
    EVT_PAINT      (                     DataPanel::OnPaintEvent)
    EVT_SIZE       (                     DataPanel::OnSize)
    EVT_TIMER      (ID_DATA_PANEL_TIMER, DataPanel::OnTimer)
    EVT_SCROLLWIN  (                     DataPanel::OnScroll)
END_EVENT_TABLE()

DataPanel::DataPanel(wxWindow *parent, wxWindowID id, int fontsize):
wxPanel(parent, id),
ruler_(true),
rulerStart_(1),
fontSize_(fontsize),
font_(fontSize_, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL),
format_(DataPanelAsciiFormat),
enableAutoscroll_(true),
//charSize_(),
//stepSize_(),
//steps_(),
//lines_(),
//linesView_(),
modified_(false),
modifiedscrollpos_(false),
//timer_,
bitmask_(0xFF)
{
    //ctor


    if (fontsize>24)
        fontsize=24;
    if (fontsize<6)
        fontsize=6;

    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DLIGHT));
    timer_.SetOwner(this, ID_DATA_PANEL_TIMER);


    Clear();
    UpdateGrid();

    timer_.Start(50);
}
DataPanel::~DataPanel()
{
    //dtor
}
void DataPanel::OnPaintEvent(wxPaintEvent &event)
{
    wxPaintDC dc(this);
    Paint(dc);
}
void DataPanel::Paint(wxDC&  dc)
{
    dc.SetFont(font_);

    wxPoint pos;
    pos.y = TopOffset();

    if ( ruler_ )
    {
        pos.x = stepSize_;
        for ( unsigned int i = 0; i < steps_ ; i++)
        {
            wxString str = wxString::Format(_("%d"), i+rulerStart_);
            dc.SetPen(*wxWHITE_PEN);
            dc.SetBrush(*wxWHITE_BRUSH);
            dc.DrawRectangle(pos.x-stepSize_+1, pos.y, stepSize_-1,charSize_.y+1);
            if( (format_ != DataPanelAsciiFormat && format_ != 0) || ((i+rulerStart_)==1 || (i+rulerStart_)%5==0))
                dc.DrawText(str, pos.x-charSize_.x*str.length(), pos.y);
            pos.x += stepSize_;
        }
        pos.y += charSize_.y+4;
    }

    unsigned int visiblelines = GetScrollThumb(wxVERTICAL);
    unsigned int firstline = GetScrollPos(wxVERTICAL);
    if ( firstline + visiblelines > linesView_.size())
        visiblelines = linesView_.size();
    for ( unsigned int idx = 0 ;  idx <  visiblelines ; idx++)
    {
        pos.x = stepSize_;
        wxCoord posy=pos.y;
        line currline = linesView_[firstline+idx];
        for ( unsigned int i = 0; i < currline.size() ; i++)
        {
            wxString str;
            unsigned short val = 0x00ff&(currline[i]&bitmask_);
            unsigned short err = 0x00ff&(currline[i]>>8);
            bool isErr = err&(ParErr|FrameErr);
//            bool isNewLine =  (err & NewLine);
//            if (isNewLine)
//                str = _T("\\n");

            posy = pos.y;
            if (format_ & DataPanelAsciiFormat)
            {
                char ch = (char)val;
                str = GetASCIIAsString(ch);
                if (isErr)
                {
                    dc.SetBrush(*wxRED_BRUSH);
                    dc.SetPen(*wxRED_PEN);
                }
                else
                {
                    dc.SetBrush(wxBrush(GetBackgroundColour()));
                    dc.SetPen(wxPen(GetBackgroundColour()));
                }
                dc.DrawRectangle(pos.x-stepSize_+1, posy, stepSize_-1,charSize_.y+1);
                dc.DrawText(str, pos.x-charSize_.x*str.length(), posy);
                posy += charSize_.y+TopOffset();
            }
            if (format_ & DataPanelHexFormat)
            {
                str = wxString::Format(_T("%02x"), val);
                if (isErr)
                {
                    dc.SetBrush(*wxRED_BRUSH);
                    dc.SetPen(*wxRED_PEN);
                }
                else
                {
                    dc.SetBrush(wxBrush(wxColor(0xc0,0xc0,0xff)));
                    dc.SetPen(wxPen(wxColor(0xc0,0xc0,0xff)));
                }
                dc.DrawRectangle(pos.x-stepSize_+1, posy, stepSize_-1,charSize_.y+1);
                dc.DrawText(str, pos.x-charSize_.x*str.length(), posy);
                posy += charSize_.y+TopOffset();
            }
            if (format_ & DataPanelDecFormat)
            {
                str = wxString::Format(_T("%d"), val);
                if (isErr)
                {
                    dc.SetBrush(*wxRED_BRUSH);
                    dc.SetPen(*wxRED_PEN);
                }
                else
                {
                    dc.SetBrush(wxBrush(wxColor(0xff,0xc0,0xc0)));
                    dc.SetPen(wxPen(wxColor(0xff,0xc0,0xc0)));
                }
                dc.DrawRectangle(pos.x-stepSize_+1, posy, stepSize_-1,charSize_.y+1);
                dc.DrawText(str, pos.x-charSize_.x*str.length(), posy);
                posy += charSize_.y+TopOffset();
            }
            if (format_ & DataPanelBinFormat)
            {
                unsigned short tmp = val;
                str = wxEmptyString;
                for (unsigned short k = 0; k < 8 ; k++)
                {
                    str = ((tmp & 0x0001)?_T("1"):_T("0")) + str;
                    tmp >>= 1;
                }
                if (isErr)
                {
                    dc.SetBrush(*wxRED_BRUSH);
                    dc.SetPen(*wxRED_PEN);
                }
                else
                {
                    dc.SetBrush(wxBrush(wxColor(0xc0,0xff,0xc0)));
                    dc.SetPen(wxPen(wxColor(0xc0,0xff,0xc0)));
                }
                dc.DrawRectangle(pos.x-stepSize_+1, posy, stepSize_-1,charSize_.y+1);
                dc.DrawText(str, pos.x-charSize_.x*str.length(), posy);
                posy += charSize_.y+TopOffset();
            }
            pos.x += stepSize_;
        }
        pos.y = posy+TopOffset();
    }
}
wxString DataPanel::GetASCIIAsString(char ch)const
{
    if (ch > 32 && ch < 127)
        return wxString::Format(_("%c"), ch);
    if (ch == 0x00) return _T("NUL");
    if (ch == 0x01) return _T("SOH");
    if (ch == 0x02) return _T("STX");
    if (ch == 0x03) return _T("ETX");
    if (ch == 0x04) return _T("EOT");
    if (ch == 0x05) return _T("ENQ");
    if (ch == 0x06) return _T("ACK");
    if (ch == 0x07) return _T("BEL");
    if (ch == 0x08) return _T("BS");
    if (ch == '\t') return _T("\\t");
    //if (ch == 0x09) return _T("\\t");
    if (ch == '\n') return _T("\\n");
    //if (ch == 0x0a) return _T("\\n");
    if (ch == 0x0b) return _T("VT");
    if (ch == 0x0c) return _T("FF");
    if (ch == '\r') return _T("\\r");
    //if (ch == 0x0d) return _T("\\r");
    if (ch == 0x0e) return _T("SO");
    if (ch == 0x0f) return _T("SI");

    if (ch == 0x10) return _T("DLE");
    if (ch == 0x11) return _T("DC1");
    if (ch == 0x12) return _T("DC2");
    if (ch == 0x13) return _T("DC3");
    if (ch == 0x14) return _T("DC4");
    if (ch == 0x15) return _T("NAK");
    if (ch == 0x16) return _T("SYN");
    if (ch == 0x17) return _T("ETB");
    if (ch == 0x18) return _T("CAN");
    if (ch == 0x19) return _T("EM");
    if (ch == 0x1a) return _T("SUB");
    if (ch == 0x1b) return _T("Esc");
    if (ch == 0x1c) return _T("FS");
    if (ch == 0x1d) return _T("GS");
    if (ch == 0x1e) return _T("RS");
    if (ch == 0x1f) return _T("US");
    if (ch == 0x20) return _T("SP");
    if (ch == 0x7f) return _T("DEL");

    return wxEmptyString;

}
void DataPanel::OnSize(wxSizeEvent &WXUNUSED(event))
{
    SetFont(font_);
    UpdateGrid();
}
void DataPanel::UpdateGrid()
{
    GetTextExtent(_T("H"), &charSize_.x, &charSize_.y);
    stepSize_ = charSize_.x;

    int formats = 0;
    if ( format_ & DataPanelAsciiFormat )
        formats++;
    if ( format_ & DataPanelHexFormat )
    {
        formats++;
        stepSize_ = 2*charSize_.x;
    }
    if ( format_ & DataPanelDecFormat )
    {
        formats++;
        stepSize_ = 3*charSize_.x;
    }
    if ( format_ & DataPanelBinFormat )
    {
        formats++;
        stepSize_ = 8*charSize_.x;
    }
    stepSize_ += LeftOffset();

    steps_ = GetSize().x/stepSize_;

    UpdateLinesView();

    Refresh();
}
void DataPanel::UpdateLinesView()
{
    linesView_.clear();

    std::vector< line >::iterator it;
    for (it = lines_.begin(); it != lines_.end(); it++)
    {
        line currLine = *it;

        std::vector< short >::iterator it;
        line thenewline;
        //thenewline.resize(steps_);
        for(it = currLine.begin();it != currLine.end();it++)
        {
            thenewline.push_back(*it);
            if (thenewline.size() == steps_)
            {
                linesView_.push_back(thenewline);
                thenewline.clear();
                //newline.resize(steps_);
            }
        }
        if (thenewline.size()!=0)
            linesView_.push_back(thenewline);
    }
    AdjustScrollbars();
}
void DataPanel::AdjustScrollbars()
{
    int formats = 0;
    if ( format_ & DataPanelAsciiFormat )
        formats++;
    if ( format_ & DataPanelHexFormat )
        formats++;
    if ( format_ & DataPanelDecFormat )
        formats++;
    if ( format_ & DataPanelBinFormat )
        formats++;

    int lines = linesView_.size();
    int visibleLines =  (GetSize().y - (ruler_?charSize_.y+TopOffset():0))/((charSize_.y+TopOffset())*formats +TopOffset());

    int pos = GetScrollPos(wxVERTICAL);
    if (enableAutoscroll_)
        pos = lines - visibleLines;
    SetScrollbar(wxVERTICAL, pos, visibleLines, lines, false );

}
void DataPanel::OnTimer(wxTimerEvent &WXUNUSED(event))
{
    if (modified_)
    {
        UpdateLinesView();
        Refresh();
        modified_ = false;
        modifiedscrollpos_ = false;
    }
    else if (modifiedscrollpos_)
    {
        Refresh();
        modifiedscrollpos_ = false;
    }
}
void DataPanel::Clear()
{
    lines_.clear();
    line newline;
    lines_.push_back(newline);
    modified_ = true;
}
void DataPanel::AppendNewline()
{
    short next = NewLine << 8;;
    lines_.back().push_back(next);

    line thenewline;
    thenewline.clear();
    lines_.push_back(thenewline);
    modified_ = true;
}
void DataPanel::AppendChar(char ch, char err)
{
    short next = (ch&0x00ff) | (err << 8);
    lines_.back().push_back(next);
    modified_ = true;
}
void DataPanel::DoAutoscroll(bool enable)
{
    enableAutoscroll_ = enable;
    if (enable)
    {
        AdjustScrollbars();
        Refresh();
    }
}
void DataPanel::SetOutputFormat(int OutputFormat)
{
    format_ = OutputFormat;
    UpdateGrid();
}
void DataPanel::SetFontSize(int fontSize)
{
    if (fontSize_ != fontSize)
    {
        fontSize_ = fontSize;
        font_ = wxFont(fontSize_, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
        SetFont(font_);
        UpdateGrid();
    }
}
void DataPanel::EnableRuler(bool enable)
{
    if ( ruler_ != enable)
    {
        ruler_ = enable;
        UpdateGrid();
        Refresh();
    }
}
void DataPanel::SetRulerStart(unsigned char start)
{
    if (rulerStart_ != start)
    {
        rulerStart_ = start;
        Refresh();
    }
}
void DataPanel::OnScroll(wxScrollWinEvent& event)
{
    if (event.GetOrientation() == wxHORIZONTAL )
        return;
    modifiedscrollpos_ = true;
}
char DataPanel::GetBitMask()
{
    return bitmask_;
}
void DataPanel::SetBitMask(char mask)
{
    if (mask != bitmask_)
    {
        bitmask_ = mask;
        Refresh();
    }
}
