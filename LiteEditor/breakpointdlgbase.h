//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// wxCrafter project file: breakpointdlg.wxcp
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#ifndef BREAKPOINTDLG_BASE_CLASSES_H
#define BREAKPOINTDLG_BASE_CLASSES_H

#include <wx/settings.h>
#include <wx/xrc/xmlres.h>
#include <wx/xrc/xh_bmp.h>
#include <wx/panel.h>
#include <wx/artprov.h>
#include <wx/sizer.h>
#include <wx/listctrl.h>
#include "breakpointslistctrl.h"
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/iconbndl.h>
#include <wx/stattext.h>
#include <wx/choicebk.h>
#include <wx/imaglist.h>
#include <wx/checkbox.h>
#include <wx/textctrl.h>
#include <wx/statline.h>
#include <wx/radiobox.h>
#include <wx/spinctrl.h>

class BreakpointTabBase : public wxPanel
{
protected:
    BreakpointsListctrl* m_listCtrlBreakpoints;
    wxButton* m_buttonAdd;
    wxButton* m_buttonEdit;
    wxButton* m_buttonDelete;
    wxButton* m_buttonDeleteAll;
    wxButton* m_buttonApplyPending;

protected:
    virtual void OnItemActivated(wxListEvent& event) { event.Skip(); }
    virtual void OnItemDeselected(wxListEvent& event) { event.Skip(); }
    virtual void OnItemRightClick(wxListEvent& event) { event.Skip(); }
    virtual void OnItemSelected(wxListEvent& event) { event.Skip(); }
    virtual void OnAdd(wxCommandEvent& event) { event.Skip(); }
    virtual void OnEdit(wxCommandEvent& event) { event.Skip(); }
    virtual void OnDelete(wxCommandEvent& event) { event.Skip(); }
    virtual void OnDeleteAll(wxCommandEvent& event) { event.Skip(); }
    virtual void OnApplyPending(wxCommandEvent& event) { event.Skip(); }

public:
    BreakpointTabBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1,-1), long style = wxTAB_TRAVERSAL);
    virtual ~BreakpointTabBase();
};


class BreakpointPropertiesDlgBase : public wxDialog
{
protected:
    wxStaticText* m_staticText9;
    wxChoicebook* m_choicebook;
    wxPanel* m_panel1;
    wxStaticText* m_staticText51;
    wxCheckBox* m_checkLineno;
    wxTextCtrl* m_textLineno;
    wxCheckBox* m_checkBreakFunction;
    wxTextCtrl* m_textFunctionname;
    wxCheckBox* m_checkRegex;
    wxCheckBox* m_checkBreakMemory;
    wxTextCtrl* m_textBreakMemory;
    wxStaticText* m_staticText6;
    wxTextCtrl* m_textFilename;
    wxButton* m_buttonBrowse;
    wxStaticLine* m_staticline5;
    wxPanel* m_panel2;
    wxRadioBox* m_radioWatchtype;
    wxStaticText* m_staticText5;
    wxTextCtrl* m_textWatchExpression;
    wxStaticText* m_staticText1;
    wxTextCtrl* m_textCond;
    wxStaticText* m_staticText11;
    wxTextCtrl* m_textCommands;
    wxCheckBox* m_checkDisable;
    wxCheckBox* m_checkTemp;
    wxStaticText* m_staticText7;
    wxSpinCtrl* m_spinIgnore;
    wxStaticLine* m_staticline4;
    wxButton* m_button6;
    wxButton* m_button7;

protected:
    virtual void OnPageChanged(wxChoicebookEvent& event) { event.Skip(); }
    virtual void OnPageChanging(wxChoicebookEvent& event) { event.Skip(); }
    virtual void OnCheckBreakLineno(wxCommandEvent& event) { event.Skip(); }
    virtual void OnCheckBreakLinenoUI(wxUpdateUIEvent& event) { event.Skip(); }
    virtual void OnCheckBreakFunction(wxCommandEvent& event) { event.Skip(); }
    virtual void OnCheckBreakFunctionUI(wxUpdateUIEvent& event) { event.Skip(); }
    virtual void OnCheckBreakMemory(wxCommandEvent& event) { event.Skip(); }
    virtual void OnCheckBreakMemoryUI(wxUpdateUIEvent& event) { event.Skip(); }
    virtual void OnBrowse(wxCommandEvent& event) { event.Skip(); }

public:
    BreakpointPropertiesDlgBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Breakpoint and Watchpoint Properties"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1,-1), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER);
    virtual ~BreakpointPropertiesDlgBase();
};

#endif
