#ifndef DATAPANEL_H
#define DATAPANEL_H

#include <wx/panel.h>
#include <wx/timer.h>
#include <vector>

#define DataPanelAsciiFormat 0x0001
#define DataPanelHexFormat   0x0002
#define DataPanelDecFormat   0x0004
#define DataPanelBinFormat   0x0008
#include <wx/scrolwin.h>


class DataPanel : public wxScrolledWindow
{
    public:
        DataPanel(wxWindow *parent, wxWindowID id, int fontsize);
        virtual ~DataPanel();
    private:
        DataPanel(){}

        bool ruler_;
        unsigned char rulerStart_;
        int fontSize_;

        wxFont font_;
        int format_;
        bool enableAutoscroll_;

        const unsigned int TopOffset()const{return 3;}
        const unsigned int LeftOffset()const{return 3;}
        wxString GetASCIIAsString(char ch)const;
    public:

        void OnPaintEvent(wxPaintEvent &event);
        //void paintNow();
        void OnSize(wxSizeEvent &event);
        void OnScroll(wxScrollWinEvent& event);

        void Paint(wxDC& dc);

        // some useful events
        /*void mouseMoved(wxMouseEvent& event);
        oid mouseDown(wxMouseEvent& event);
        void mouseWheelMoved(wxMouseEvent& event);
        void mouseReleased(wxMouseEvent& event);
        void rightClick(wxMouseEvent& event);
        void mouseLeftWindow(wxMouseEvent& event);
        void keyPressed(wxKeyEvent& event);
        void keyReleased(wxKeyEvent& event);
        */
    private:
        wxSize charSize_;
        wxCoord stepSize_;
        unsigned int steps_;
        void UpdateGrid();
        void UpdateLinesView();
        typedef std::vector< short > line;

        std::vector< line > lines_;
        std::vector< line > linesView_;

        //int visibleLineNumber_;
        bool modified_, modifiedscrollpos_;

        wxTimer timer_;
        static const long ID_DATA_PANEL_TIMER;
        void OnTimer(wxTimerEvent &event);

        void AdjustScrollbars();

        char bitmask_;

    public:

        void Clear();
        void EnableRuler(bool enable = true);
        bool RulerIsEnabled(){return ruler_;}
        void SetRulerStart(unsigned char start=1);
        unsigned char GetRulerStart(){return rulerStart_;}
        void DoAutoscroll(bool enable=true);
        void AppendNewline();
        //void AppendData(char *buf, unsigned int len);
        //void ShowNewlineCharacter(bool enable);
        void AppendChar(char ch, char err = 0x00);

        void SetOutputFormat(int OutputFormat);
        int GetFontSize(){return fontSize_;}
        void SetFontSize(int fontSize);

        char GetBitMask();
        void SetBitMask(char mask);

    protected:
    private:
        /*bool m_Ruler;
        unsigned char m_RulerStart;
        int m_fontSize;*/

    DECLARE_DYNAMIC_CLASS(DataPanel)
    DECLARE_EVENT_TABLE()
};

#endif // DATAPANEL_H
