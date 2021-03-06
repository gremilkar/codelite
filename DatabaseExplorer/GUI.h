//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#ifndef GUI_BASE_CLASSES_H
#define GUI_BASE_CLASSES_H

#include <wx/settings.h>
#include <wx/xrc/xmlres.h>
#include <wx/xrc/xh_bmp.h>
#include <wx/dialog.h>
#include <wx/iconbndl.h>
#include <wx/artprov.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/statbox.h>
#include <wx/radiobut.h>
#include <wx/checkbox.h>
#include <wx/panel.h>
#include <wx/pen.h>
#include <wx/aui/auibar.h>
#include <wx/toolbar.h>
#include <wx/splitter.h>
#include <wx/stc/stc.h>
#include <wx/grid.h>
#include <wx/treectrl.h>
#include <wx/notebook.h>
#include <wx/imaglist.h>
#include <wx/filepicker.h>
#include <wx/listctrl.h>
#include <wx/listbox.h>
#include <wx/choice.h>
#include <wx/arrstr.h>
#include <wx/gbsizer.h>
#include <wx/radiobox.h>
#include <wx/infobar.h>
#include <wx/dataview.h>
#include <wx/statline.h>

class _ImageExportDialog : public wxDialog
{
protected:
    wxBoxSizer* mainSizer;
    wxStaticText* m_staticText34;
    wxBoxSizer* fpSizer;
    wxTextCtrl* m_textCtrlPath;
    wxButton* m_button29;
    wxStaticBoxSizer* scaleSizer;
    wxRadioButton* m_radioBtnDefaultScale;
    wxBoxSizer* customScaleSizer;
    wxRadioButton* m_radioBtnScaleCustom;
    wxTextCtrl* m_textCtrlScale;
    wxCheckBox* m_checkBoxBackground;
    wxStdDialogButtonSizer* m_sdbSizer2;
    wxButton* m_button126;
    wxButton* m_button127;

protected:
    virtual void OnInit(wxInitDialogEvent& event) { event.Skip(); }
    virtual void OnBowseClick(wxCommandEvent& event) { event.Skip(); }
    virtual void OnUpdateCustomScale(wxUpdateUIEvent& event) { event.Skip(); }

public:
    _ImageExportDialog(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Export image"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1, -1), long style = wxDEFAULT_DIALOG_STYLE);
    virtual ~_ImageExportDialog();
};


class _ThumbPane : public wxPanel
{
protected:
    wxBoxSizer* mainSizer;

protected:

public:
    _ThumbPane(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(500,300), long style = wxTAB_TRAVERSAL);
    virtual ~_ThumbPane();
};


class _SqlCommandPanel : public wxPanel
{
protected:
    enum {
        ID_INSERT_TEMPLATE = 1001,
        ID_SQL_HISTORY = 1002,
    };
protected:
    wxFlexGridSizer* fgSizer3;
    wxAuiToolBar* m_auibar167;
    wxSplitterWindow* m_splitter1;
    wxPanel* m_panel13;
    wxBoxSizer* bSizer23;
    wxBoxSizer* bSizer25;
    wxStyledTextCtrl* m_scintillaSQL;
    wxPanel* m_panel14;
    wxBoxSizer* bSizer24;
    wxGrid* m_gridTable;
    wxStaticText* m_labelStatus;

protected:
    virtual void OnLoadClick(wxCommandEvent& event) { event.Skip(); }
    virtual void OnSaveClick(wxCommandEvent& event) { event.Skip(); }
    virtual void OnExecuteClick(wxCommandEvent& event) { event.Skip(); }
    virtual void OnTemplatesBtnClick(wxAuiToolBarEvent& event) { event.Skip(); }
    virtual void OnHistoryToolClicked(wxAuiToolBarEvent& event) { event.Skip(); }
    virtual void OnGridCellRightClick(wxGridEvent& event) { event.Skip(); }

public:
    _SqlCommandPanel(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1,-1), long style = wxTAB_TRAVERSAL);
    virtual ~_SqlCommandPanel();
};


class _AdapterSelectDlg : public wxDialog
{
protected:
    wxBoxSizer* bSizer9;
    wxButton* m_btnMySql;
    wxButton* m_btnSqlite;
    wxButton* m_button24;

protected:
    virtual void OnMysqlClick(wxCommandEvent& event) { event.Skip(); }
    virtual void OnSqliteClick(wxCommandEvent& event) { event.Skip(); }
    virtual void OnPostgresClick(wxCommandEvent& event) { event.Skip(); }

public:
    _AdapterSelectDlg(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Select dbAdapter"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1,-1), long style = wxDEFAULT_DIALOG_STYLE);
    virtual ~_AdapterSelectDlg();
};


class _DbViewerPanel : public wxPanel
{
protected:
    wxBoxSizer* bSizer28;
    wxToolBar* m_toolBar1;
    wxTreeCtrl* m_treeDatabases;

protected:
    virtual void OnDnDStart(wxTreeEvent& event) { event.Skip(); }
    virtual void OnItemActivate(wxTreeEvent& event) { event.Skip(); }
    virtual void OnItemRightClick(wxTreeEvent& event) { event.Skip(); }
    virtual void OnItemSelectionChange(wxTreeEvent& event) { event.Skip(); }

public:
    _DbViewerPanel(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1,-1), long style = wxTAB_TRAVERSAL);
    virtual ~_DbViewerPanel();
};


class _DBSettingsDialog : public wxDialog
{
protected:
    wxBoxSizer* bSizer4;
    wxNotebook* m_notebook2;
    wxPanel* m_Sqlite;
    wxBoxSizer* bSizer27;
    wxFlexGridSizer* fgSizer41;
    wxStaticText* m_staticText11;
    wxFilePickerCtrl* m_filePickerSqlite;
    wxListCtrl* m_listCtrlRecentFiles;
    wxPanel* m_MySqlPanel;
    wxFlexGridSizer* fgSizer3;
    wxFlexGridSizer* fgSizer4;
    wxStaticText* m_staticText10;
    wxTextCtrl* m_txName;
    wxStaticText* m_staticText1;
    wxTextCtrl* m_txServer;
    wxStaticText* m_staticText2;
    wxTextCtrl* m_txUserName;
    wxStaticText* m_staticText3;
    wxTextCtrl* m_txPassword;
    wxBoxSizer* bSizer8;
    wxListBox* m_listBox2;
    wxPanel* m_PostgrePanel;
    wxBoxSizer* bSizer_1;
    wxFlexGridSizer* fgSizer42;
    wxStaticText* m_staticText101;
    wxTextCtrl* m_txPgName;
    wxStaticText* m_staticText12;
    wxTextCtrl* m_txPgServer;
    wxStaticText* m_staticText35;
    wxTextCtrl* m_txPgPort;
    wxStaticText* m_staticText21;
    wxTextCtrl* m_txPgUserName;
    wxStaticText* m_staticText31;
    wxTextCtrl* m_txPgPassword;
    wxStaticText* m_staticText24;
    wxTextCtrl* m_txPgDatabase;
    wxListBox* m_listBoxPg;
    wxBoxSizer* bSizer28;
    wxButton* m_button36;
    wxButton* m_button35;

protected:
    virtual void OnItemActivated(wxListEvent& event) { event.Skip(); }
    virtual void OnItemSelected(wxListEvent& event) { event.Skip(); }
    virtual void OnItemKeyDown(wxListEvent& event) { event.Skip(); }
    virtual void OnMySqlPassKeyDown(wxKeyEvent& event) { event.Skip(); }
    virtual void OnHistoryClick(wxCommandEvent& event) { event.Skip(); }
    virtual void OnHistoryDClick(wxCommandEvent& event) { event.Skip(); }
    virtual void OnHistoruUI(wxUpdateUIEvent& event) { event.Skip(); }
    virtual void OnPgSqlKeyDown(wxKeyEvent& event) { event.Skip(); }
    virtual void OnPgHistoryClick(wxCommandEvent& event) { event.Skip(); }
    virtual void OnPgHistoryDClick(wxCommandEvent& event) { event.Skip(); }
    virtual void OnDlgOK(wxCommandEvent& event) { event.Skip(); }

public:
    _DBSettingsDialog(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Connection settings"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1, -1), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER);
    virtual ~_DBSettingsDialog();
};


class _ErdPanel : public wxPanel
{
protected:
    wxFlexGridSizer* fgSizer7;
    wxAuiToolBar* m_toolBarErd;
    wxPanel* m_wxsfPanel;
    wxBoxSizer* m_wxsfSizer;

protected:
    virtual void OnMouseWheel(wxMouseEvent& event) { event.Skip(); }

public:
    _ErdPanel(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(640,480), long style = wxTAB_TRAVERSAL);
    virtual ~_ErdPanel();
};


class _CreateForeignKey : public wxDialog
{
protected:
    wxFlexGridSizer* fgSizer12;
    wxStaticBoxSizer* sbSizer7;
    wxStaticText* m_staticText15;
    wxTextCtrl* m_txSrcTable;
    wxStaticText* m_staticText17;
    wxChoice* m_cmbSrcCol;
    wxGridBagSizer* gbSizer1;
    wxRadioBox* m_radioRelation;
    wxRadioBox* m_radioOnDelete;
    wxRadioBox* m_radioOnUpdate;
    wxStaticBoxSizer* sbSizer8;
    wxStaticText* m_staticText16;
    wxTextCtrl* m_txDstTable;
    wxStaticText* m_staticText18;
    wxChoice* m_cmbDstCol;
    wxBoxSizer* bSizer12;
    wxButton* m_btnCancel;
    wxButton* m_btnOK;

protected:
    virtual void OnCancelClick(wxCommandEvent& event) { event.Skip(); }
    virtual void OnOKClick(wxCommandEvent& event) { event.Skip(); }
    virtual void OnOKUI(wxUpdateUIEvent& event) { event.Skip(); }

public:
    _CreateForeignKey(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Create foreign key"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1, -1), long style = wxDEFAULT_DIALOG_STYLE);
    virtual ~_CreateForeignKey();
};


class _LogDialog : public wxDialog
{
protected:
    wxFlexGridSizer* fgSizer13;
    wxStaticBoxSizer* sbSizer9;
    wxTextCtrl* m_textCtrl11;
    wxBoxSizer* bSizer13;
    wxButton* m_button18;

protected:
    virtual void OnCloseClick(wxCommandEvent& event) { event.Skip(); }
    virtual void OnCloseUI(wxUpdateUIEvent& event) { event.Skip(); }

public:
    _LogDialog(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Database log"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(640,460), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxMAXIMIZE_BOX);
    virtual ~_LogDialog();
};


class _ViewSettings : public wxDialog
{
protected:
    wxBoxSizer* bSizer15;
    wxFlexGridSizer* fgSizer14;
    wxBoxSizer* bSizer14;
    wxStaticText* m_staticText19;
    wxTextCtrl* m_txName;
    wxStyledTextCtrl* m_scintilla2;
    wxButton* m_btnOK;

protected:
    virtual void OnOKClick(wxCommandEvent& event) { event.Skip(); }

public:
    _ViewSettings(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("View settings"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(650,450), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxMAXIMIZE_BOX|wxMINIMIZE_BOX);
    virtual ~_ViewSettings();
};


class _ClassGenerateDialog : public wxDialog
{
protected:
    wxBoxSizer* bSizer22;
    wxFlexGridSizer* fgSizer19;
    wxStaticText* m_staticText30;
    wxTextCtrl* m_txPrefix;
    wxStaticText* m_staticText31;
    wxTextCtrl* m_txPostfix;
    wxStaticText* m_staticText28;
    wxDirPickerCtrl* m_dirPicker;
    wxStaticText* m_staticText34;
    wxFlexGridSizer* fgSizer26;
    wxTextCtrl* m_txVirtualDir;
    wxButton* m_btnBrowseVirtualDir;
    wxStaticText* m_staticText36;
    wxChoice* m_choiceTemplates;
    wxStaticText* m_staticText29;
    wxTextCtrl* m_textLog;
    wxBoxSizer* bSizer20;
    wxButton* m_button26;
    wxButton* m_button25;

protected:
    virtual void OnBtnBrowseClick(wxCommandEvent& event) { event.Skip(); }
    virtual void OnCancelClick(wxCommandEvent& event) { event.Skip(); }
    virtual void OnGenerateClick(wxCommandEvent& event) { event.Skip(); }

public:
    _ClassGenerateDialog(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Class generator dialog"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1, -1), long style = wxDEFAULT_DIALOG_STYLE);
    virtual ~_ClassGenerateDialog();
};


class _CodePreviewDialog : public wxDialog
{
protected:
    wxBoxSizer* boxSizer10;
    wxStyledTextCtrl* m_scintilla3;
    wxButton* m_button14;

protected:
    virtual void OnOKClick(wxCommandEvent& event) { event.Skip(); }

public:
    _CodePreviewDialog(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("SQL Preview"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(500,470), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER);
    virtual ~_CodePreviewDialog();
};


class _TableSettings : public wxDialog
{
protected:
    wxBoxSizer* boxSizer19;
    wxInfoBar* m_infobar;
    wxBoxSizer* boxSizer21;
    wxStaticText* m_staticText23;
    wxTextCtrl* m_textName;
    wxSplitterWindow* m_splitter27;
    wxPanel* m_splitterPage31;
    wxBoxSizer* boxSizer37;
    wxStaticText* m_staticText55;
    wxAuiToolBar* m_auibar39;
    wxDataViewListCtrl* m_dvColumns;
    wxPanel* m_splitterPage35;
    wxBoxSizer* boxSizer43;
    wxStaticText* m_staticText57;
    wxAuiToolBar* m_auibar45;
    wxFlexGridSizer* flexGridSizer143;
    wxDataViewListCtrl* m_dvKeys;
    wxBoxSizer* boxSizer163;
    wxFlexGridSizer* flexGridSizer147;
    wxStaticText* m_staticText125;
    wxChoice* m_choiceLocalCol;
    wxStaticText* m_staticText131;
    wxChoice* m_choiceRefTable;
    wxStaticText* m_staticText135;
    wxChoice* m_choiceRefCol;
    wxRadioBox* m_radioOnUpdate;
    wxRadioBox* m_radioOnDelete;
    wxStaticLine* m_staticLine149;
    wxBoxSizer* boxSizer49;
    wxButton* m_button51;
    wxButton* m_button53;

protected:
    virtual void OnInit(wxInitDialogEvent& event) { event.Skip(); }
    virtual void OnAddColumnClick(wxCommandEvent& event) { event.Skip(); }
    virtual void OnRemoveColumnClick(wxCommandEvent& event) { event.Skip(); }
    virtual void OnUpdateColumns(wxUpdateUIEvent& event) { event.Skip(); }
    virtual void OnMoveUpClick(wxCommandEvent& event) { event.Skip(); }
    virtual void OnUpdateMoveUp(wxUpdateUIEvent& event) { event.Skip(); }
    virtual void OnMoveDownClick(wxCommandEvent& event) { event.Skip(); }
    virtual void OnUpdateMoveDown(wxUpdateUIEvent& event) { event.Skip(); }
    virtual void OnColumnChanged(wxDataViewEvent& event) { event.Skip(); }
    virtual void OnAddKeyClick(wxCommandEvent& event) { event.Skip(); }
    virtual void OnRemoveKeyClick(wxCommandEvent& event) { event.Skip(); }
    virtual void OnUpdateKeys(wxUpdateUIEvent& event) { event.Skip(); }
    virtual void OnKeySelected(wxDataViewEvent& event) { event.Skip(); }
    virtual void OnKeyChanged(wxDataViewEvent& event) { event.Skip(); }
    virtual void OnLocalColSelected(wxCommandEvent& event) { event.Skip(); }
    virtual void OnRefTableSelected(wxCommandEvent& event) { event.Skip(); }
    virtual void OnRefColSelected(wxCommandEvent& event) { event.Skip(); }
    virtual void OnRadioUpdateSelected(wxCommandEvent& event) { event.Skip(); }
    virtual void OnRadioDeleteSelected(wxCommandEvent& event) { event.Skip(); }
    virtual void OnCancelClick(wxCommandEvent& event) { event.Skip(); }
    virtual void OnOKClick(wxCommandEvent& event) { event.Skip(); }

public:
    _TableSettings(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Table settings"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(600,700), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER);
    virtual ~_TableSettings();
};

#endif
