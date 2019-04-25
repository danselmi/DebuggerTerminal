#include "DataInputControl.h"

#include <wx/clipbrd.h>
#include <wx/dataobj.h>

//{
BEGIN_EVENT_TABLE(DataInputControl,wxTextCtrl)
    EVT_CHAR(DataInputControl::OnChar)
END_EVENT_TABLE()
//}


DataInputControl::DataInputControl(wxWindow *parent, wxWindowID id):
wxTextCtrl(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER /*| wxTE_MULTILINE | wxTE_RICH*/ )
{
    //ctor
    SetFormat(DataInputControlAsciiFormat, true);
    //SetBackgroundColour(*wxWHITE);//wxSystemSettings::GetColour());
}

DataInputControl::~DataInputControl()
{
    //dtor
}

void DataInputControl::OnChar(wxKeyEvent &event)
{
    int keycode = event.GetKeyCode();

    if (event.HasModifiers() || keycode > 300 ||
        keycode == WXK_BACK || keycode == WXK_RETURN ||
        keycode == WXK_ESCAPE || keycode == WXK_DELETE)
    {
        event.Skip();
        return;
    }
    if ( keycode == WXK_TAB || keycode == WXK_SPACE )
        return;

    switch (m_format)
    {
    default:
    case DataInputControlAsciiFormat:
        event.Skip();
        return;
    case DataInputControlBinFormat:
        if (keycode == '0' || keycode == '1' )
        {
            event.Skip();
            return;
        }
        break;
    case DataInputControlDecFormat:
        if (keycode >= '0' && keycode <= '9' )
        {
            event.Skip();
            return;
        }
        break;
    case DataInputControlHexFormat:
        if ((keycode >= '0' && keycode <= '9' ) || (keycode >= 'a' && keycode <= 'f' ) || (keycode >= 'A' && keycode <= 'F' ))
        {
            event.Skip();
            return;
        }
        break;
    }
}
void DataInputControl::SetFormat(int format, bool force )
{
    if ( !force && m_format == format) return;
    wxString str = GetValue();

    char *buffer;
    unsigned int len=0;


    if (m_format == DataInputControlAsciiFormat)
    {
        len = str.length();
        buffer = new char[len];
        strncpy(buffer, (const char*)str.ToUTF8(),len);
    }
    if (m_format == DataInputControlBinFormat)
    {
        while (str.length() % 8) str += ('0');
        len = str.length()/8;
        buffer = new char[len];
        for (unsigned int i = 0 ; i < len; i++)
        {
            char val = 0;
            for (unsigned int k = 0 ; k < 8 ; k++)
            {
                wxChar ch = str[i*8+k];
                if ( ch != _T('0') ) val |= 0x01;

                if (k==7)buffer[i]=val;
                val <<= 1;
            }
        }
    }
    if (m_format == DataInputControlDecFormat)
    {
        while (str.length() % 3) str += ('0');
        len = str.length()/3;
        buffer = new char[len];
        for (unsigned int i = 0 ; i < len; i++)
        {
            char val = 0;
            for (unsigned int k = 0 ; k < 3 ; k++)
            {
                wxChar ch = str[i*3+k];
                val += (ch - _T('0'));

                if (k==2)buffer[i]=val;
                val *= 10;
            }
        }
    }
    if (m_format == DataInputControlHexFormat)
    {
        while (str.length() % 2) str += _T('0');
        len = str.length()/2;
        buffer = new char[len];
        str = str.MakeUpper();
        for (unsigned int i = 0 ; i < len; i++)
        {
            char val = 0;
            for (unsigned int k = 0 ; k < 2 ; k++)
            {
                wxChar ch = str[i*2+k];
                if ( ch >= _T('0') && ch <= _T('9'))
                    val |= (ch - _T('0'));
                if ( ch >= _T('A') && ch <= _T('F'))
                    val |= (ch - _T('A'));

                if (k==1)buffer[i]=val;
                val <<= 4;
            }
        }
    }

    m_format = format;
    str.Empty();

    if (m_format == DataInputControlAsciiFormat)
    {
        for (unsigned int i = 0; i < len; i++)
        {
            wxChar ch = buffer[i];
            str += ch;
        }
        SetBackgroundColour(wxNullColour);
    }
    if (m_format == DataInputControlBinFormat)
    {
        for (unsigned int i = 0; i < len; i++)
        {
            char ch = buffer[i];
            for (unsigned int k = 0 ; k <8 ; k++)
            {
                if (ch & 0x80)
                    str += _T('1');
                else
                    str += _T('0');
                ch <<= 1;
            }
        }
        SetBackgroundColour(wxColor(0xc0,0xff,0xc0));
    }
    if (m_format == DataInputControlDecFormat)
    {
        for (unsigned int i = 0; i < len; i++)
        {
            unsigned char ch = buffer[i];
            unsigned char thr = 100;
            for (unsigned int k = 0 ; k <3 ; k++)
            {
                wxChar s = _T('0');
                while(ch>=thr)
                {
                    s++;
                    ch -= thr;
                }
                str += s;
                thr /= 10;
            }
        }
        SetBackgroundColour(wxColor(0xff,0xc0,0xc0));
    }
    if (m_format == DataInputControlHexFormat)
    {
        for (unsigned int i = 0; i < len; i++)
        {
            char ch = buffer[i];
            for (unsigned int k = 0 ; k <2 ; k++)
            {
                wxChar s = _T('0');
                if ( (ch & 0xf0) >= 0xA0)
                    s = _T('A');
                s += (ch & 0xf0)/16;
                str += s;
                ch <<= 4;
            }
        }
        SetBackgroundColour(wxColor(0xc0,0xc0,0xff));
    }
    SetValue(str);

}

void DataInputControl::Copy()
{
    if (wxTheClipboard->Open())
    {
        wxTheClipboard->SetData( new wxTextDataObject(_T("Some text")) );
        wxTheClipboard->Close();
    }
}
void DataInputControl::Cut()
{
    DataInputControl::Copy();
    DataInputControl::Clear();

}
void DataInputControl::Clear()
{
    m_data.clear();
    wxTextCtrl::Clear();
}

