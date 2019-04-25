#include "SelectFontSizeDialog.h"

//(*InternalHeaders(SelectFontSizeDialog)
#include <wx/button.h>
#include <wx/string.h>
#include <wx/intl.h>
//*)

//(*IdInit(SelectFontSizeDialog)
const long SelectFontSizeDialog::ID_STATICTEXT1 = wxNewId();
const long SelectFontSizeDialog::ID_CHOICE1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(SelectFontSizeDialog,wxDialog)
	//(*EventTable(SelectFontSizeDialog)
	//*)
END_EVENT_TABLE()

SelectFontSizeDialog::SelectFontSizeDialog(wxWindow* parent, wxWindowID id, const wxString &title, int sel)
{
	//(*Initialize(SelectFontSizeDialog)
	wxBoxSizer* BoxSizer1;
	wxStdDialogButtonSizer* StdDialogButtonSizer1;

	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Select font size:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	BoxSizer1->Add(StaticText1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	Choice1 = new wxChoice(this, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
	BoxSizer1->Add(Choice1, 1, wxLEFT|wxRIGHT|wxSHAPED|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StdDialogButtonSizer1 = new wxStdDialogButtonSizer();
	StdDialogButtonSizer1->AddButton(new wxButton(this, wxID_OK, wxEmptyString));
	StdDialogButtonSizer1->AddButton(new wxButton(this, wxID_CANCEL, wxEmptyString));
	StdDialogButtonSizer1->Realize();
	BoxSizer1->Add(StdDialogButtonSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);
	//*)
	SetTitle(title);

	if (sel < 6)sel = 6;
	if (sel > 24)sel=24;
	for (int i=6; i < 25 ; i++)
    {
        Choice1->Append(wxString::Format(_T("%d"), i));
    }
    Choice1->SetSelection(sel-6);
}
SelectFontSizeDialog::~SelectFontSizeDialog()
{
	//(*Destroy(SelectFontSizeDialog)
	//*)
}

int SelectFontSizeDialog::GetFontSize()
{
    return Choice1->GetSelection() +6;
}
