#ifndef SELECTFONTSIZEDIALOG_H
#define SELECTFONTSIZEDIALOG_H

//(*Headers(SelectFontSizeDialog)
#include <wx/choice.h>
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
//*)

class SelectFontSizeDialog: public wxDialog
{
	public:

		SelectFontSizeDialog(wxWindow* parent, wxWindowID id, const wxString &title, int sel);
		virtual ~SelectFontSizeDialog();

		//(*Declarations(SelectFontSizeDialog)
		wxChoice* Choice1;
		wxStaticText* StaticText1;
		//*)

		int GetFontSize();

	protected:

		//(*Identifiers(SelectFontSizeDialog)
		static const long ID_STATICTEXT1;
		static const long ID_CHOICE1;
		//*)

	private:

		//(*Handlers(SelectFontSizeDialog)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
