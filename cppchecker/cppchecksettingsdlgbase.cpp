//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// wxCrafter project file: cppchecksettingsdlg.wxcp
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#include "cppchecksettingsdlgbase.h"


// Declare the bitmap loading function
extern void wxCrafterRo2g8MInitBitmapResources();

static bool bBitmapLoaded = false;


CppCheckSettingsDialogBase::CppCheckSettingsDialogBase(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
    : wxDialog(parent, id, title, pos, size, style)
{
    if ( !bBitmapLoaded ) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxCrafterRo2g8MInitBitmapResources();
        bBitmapLoaded = true;
    }
    
    wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(bSizer1);
    
    m_notebook1 = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxSize(-1, -1), 0);
    
    bSizer1->Add(m_notebook1, 1, wxALL|wxEXPAND, 5);
    
    m_ChecksPanel = new wxPanel(m_notebook1, wxID_ANY, wxDefaultPosition, wxSize(-1, -1), wxTAB_TRAVERSAL);
    m_notebook1->AddPage(m_ChecksPanel, _("Checks"), false);
    
    wxBoxSizer* bSizer3 = new wxBoxSizer(wxVERTICAL);
    m_ChecksPanel->SetSizer(bSizer3);
    
    m_staticText5 = new wxStaticText(m_ChecksPanel, wxID_ANY, _("Run the following extra checks:"), wxDefaultPosition, wxSize(-1, -1), 0);
    
    bSizer3->Add(m_staticText5, 0, wxALL, 5);
    
    wxBoxSizer* bSizer511 = new wxBoxSizer(wxHORIZONTAL);
    
    bSizer3->Add(bSizer511, 1, wxEXPAND, 5);
    
    wxArrayString m_checkListExtraWarningsArr;
    m_checkListExtraWarningsArr.Add(wxT("Coding style"));
    m_checkListExtraWarningsArr.Add(wxT("Performance"));
    m_checkListExtraWarningsArr.Add(wxT("Portability"));
    m_checkListExtraWarningsArr.Add(wxT("Unused functions"));
    m_checkListExtraWarningsArr.Add(wxT("Missing includes"));
    m_checkListExtraWarningsArr.Add(wxT("Output informative messages"));
    m_checkListExtraWarningsArr.Add(wxT("Posix standards"));
    m_checkListExtraWarningsArr.Add(wxT("C99 standards"));
    m_checkListExtraWarningsArr.Add(wxT("C++11 standards"));
    m_checkListExtraWarnings = new wxCheckListBox(m_ChecksPanel, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), m_checkListExtraWarningsArr, wxLB_SINGLE);
    
    bSizer511->Add(m_checkListExtraWarnings, 1, wxALL|wxEXPAND, 5);
    
    wxBoxSizer* bSizer611 = new wxBoxSizer(wxVERTICAL);
    
    bSizer511->Add(bSizer611, 0, wxEXPAND, 5);
    
    m_buttonAllChecks = new wxButton(m_ChecksPanel, wxID_ANY, _("Tick All"), wxDefaultPosition, wxSize(-1, -1), 0);
    m_buttonAllChecks->SetToolTip(_("Tick all the boxes"));
    
    bSizer611->Add(m_buttonAllChecks, 0, wxALL, 5);
    
    m_buttonClearChecks = new wxButton(m_ChecksPanel, wxID_ANY, _("Untick All"), wxDefaultPosition, wxSize(-1, -1), 0);
    m_buttonClearChecks->SetToolTip(_("Untick all the boxes"));
    
    bSizer611->Add(m_buttonClearChecks, 0, wxALL, 5);
    
    wxBoxSizer* boxSizer36 = new wxBoxSizer(wxVERTICAL);
    
    bSizer3->Add(boxSizer36, 0, wxALL|wxEXPAND, 10);
    
    m_cbOptionForce = new wxCheckBox(m_ChecksPanel, wxID_ANY, _("Force checking unlimited numbers of configurations"), wxDefaultPosition, wxSize(-1, -1), 0);
    m_cbOptionForce->SetValue(false);
    m_cbOptionForce->SetToolTip(_("By default the maximum number of configurations checked per file is 12. If that might not be enough, tick this box."));
    
    boxSizer36->Add(m_cbOptionForce, 0, wxALL|wxEXPAND, 5);
    
    wxBoxSizer* boxSizer38 = new wxBoxSizer(wxHORIZONTAL);
    
    boxSizer36->Add(boxSizer38, 0, 0, 5);
    
    m_cbJobs = new wxCheckBox(m_ChecksPanel, wxID_ANY, _("Multiple jobs (-j)"), wxDefaultPosition, wxSize(-1, -1), 0);
    m_cbJobs->SetValue(false);
    m_cbJobs->SetToolTip(_("Tell Cppcheck to use 'n' CPUs. NB this is incompatable with 'unusedFunction', and may give false-positive warnings for e.g. 'Unmatched suppression' ."));
    
    boxSizer38->Add(m_cbJobs, 0, wxALL|wxEXPAND, 5);
    
    m_spinCtrlJobs = new wxSpinCtrl(m_ChecksPanel, wxID_ANY, wxT("1"), wxDefaultPosition, wxSize(50,-1), wxSP_ARROW_KEYS);
    m_spinCtrlJobs->SetToolTip(_("Number of jobs to try to run in parallel"));
    m_spinCtrlJobs->SetRange(1, 100);
    m_spinCtrlJobs->SetValue(1);
    
    boxSizer38->Add(m_spinCtrlJobs, 0, wxALL, 5);
    
    m_cbCheckConfig = new wxCheckBox(m_ChecksPanel, wxID_ANY, _("Check configuration (turns off other checks)"), wxDefaultPosition, wxSize(-1, -1), 0);
    m_cbCheckConfig->SetValue(false);
    m_cbCheckConfig->SetToolTip(_("Pass --check-config to Cppchecker. This is useful if you get a 'Cppcheck cannot find all the include files' warning: it lets you see which #include aren't being located. However it turns off other checks."));
    
    boxSizer36->Add(m_cbCheckConfig, 0, wxALL|wxEXPAND, 5);
    
    m_ExcludePanel = new wxPanel(m_notebook1, wxID_ANY, wxDefaultPosition, wxSize(-1, -1), wxTAB_TRAVERSAL);
    m_notebook1->AddPage(m_ExcludePanel, _("Exclude"), false);
    
    wxBoxSizer* bSizer8 = new wxBoxSizer(wxVERTICAL);
    m_ExcludePanel->SetSizer(bSizer8);
    
    m_staticText1 = new wxStaticText(m_ExcludePanel, wxID_ANY, _("Files to exclude from CppCheck test:"), wxDefaultPosition, wxSize(-1, -1), 0);
    
    bSizer8->Add(m_staticText1, 0, wxALL, 5);
    
    wxBoxSizer* bSizer5 = new wxBoxSizer(wxHORIZONTAL);
    
    bSizer8->Add(bSizer5, 1, wxEXPAND, 5);
    
    wxArrayString m_listBoxExcludelistArr;
    m_listBoxExcludelist = new wxListBox(m_ExcludePanel, wxID_ANY, wxDefaultPosition, wxSize(-1, -1), m_listBoxExcludelistArr, 0);
    
    bSizer5->Add(m_listBoxExcludelist, 1, wxALL|wxEXPAND, 5);
    
    wxBoxSizer* bSizer6 = new wxBoxSizer(wxVERTICAL);
    
    bSizer5->Add(bSizer6, 0, wxEXPAND, 5);
    
    m_buttonAdd = new wxButton(m_ExcludePanel, wxID_ANY, _("Add"), wxDefaultPosition, wxSize(-1, -1), 0);
    m_buttonAdd->SetToolTip(_("Add file(s) to the excluded files list"));
    
    bSizer6->Add(m_buttonAdd, 0, wxALL, 5);
    
    m_buttonRemove = new wxButton(m_ExcludePanel, wxID_ANY, _("Remove"), wxDefaultPosition, wxSize(-1, -1), 0);
    m_buttonRemove->SetToolTip(_("Remove the selected file from the excluded file list"));
    
    bSizer6->Add(m_buttonRemove, 0, wxALL, 5);
    
    m_buttonClearList = new wxButton(m_ExcludePanel, wxID_ANY, _("Clear"), wxDefaultPosition, wxSize(-1, -1), 0);
    m_buttonClearList->SetToolTip(_("Clear the excluded files list"));
    
    bSizer6->Add(m_buttonClearList, 0, wxALL, 5);
    
    m_SuppressPanel = new wxPanel(m_notebook1, wxID_ANY, wxDefaultPosition, wxSize(-1, -1), wxTAB_TRAVERSAL);
    m_notebook1->AddPage(m_SuppressPanel, _("Suppress"), false);
    
    wxBoxSizer* bSizer81 = new wxBoxSizer(wxVERTICAL);
    m_SuppressPanel->SetSizer(bSizer81);
    
    m_staticText11 = new wxStaticText(m_SuppressPanel, wxID_ANY, _("Types of warnings NOT to display:"), wxDefaultPosition, wxSize(-1, -1), 0);
    
    bSizer81->Add(m_staticText11, 0, wxALL, 5);
    
    wxBoxSizer* bSizer51 = new wxBoxSizer(wxHORIZONTAL);
    
    bSizer81->Add(bSizer51, 1, wxEXPAND, 5);
    
    wxArrayString m_checkListSuppressArr;
    m_checkListSuppress = new wxCheckListBox(m_SuppressPanel, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), m_checkListSuppressArr, wxLB_SINGLE);
    
    bSizer51->Add(m_checkListSuppress, 1, wxALL|wxEXPAND, 5);
    
    wxBoxSizer* bSizer61 = new wxBoxSizer(wxVERTICAL);
    
    bSizer51->Add(bSizer61, 0, wxEXPAND, 5);
    
    m_buttonAddSuppression = new wxButton(m_SuppressPanel, wxID_ANY, _("Add"), wxDefaultPosition, wxSize(-1, -1), 0);
    m_buttonAddSuppression->SetToolTip(_("Add an extra check to suppress. You'll need to know its id..."));
    
    bSizer61->Add(m_buttonAddSuppression, 0, wxALL, 5);
    
    m_buttonRemoveSuppression = new wxButton(m_SuppressPanel, wxID_ANY, _("Remove"), wxDefaultPosition, wxSize(-1, -1), 0);
    m_buttonRemoveSuppression->SetToolTip(_("Remove the selected suppression from the list"));
    
    bSizer61->Add(m_buttonRemoveSuppression, 0, wxALL, 5);
    
    bSizer61->Add(0, 0, 0, wxTOP, 15);
    
    m_buttonSuppressAll = new wxButton(m_SuppressPanel, wxID_ANY, _("Tick All"), wxDefaultPosition, wxSize(-1, -1), 0);
    m_buttonSuppressAll->SetToolTip(_("Tick all the boxes"));
    
    bSizer61->Add(m_buttonSuppressAll, 0, wxALL, 5);
    
    m_buttonClearSuppressions = new wxButton(m_SuppressPanel, wxID_ANY, _("Untick All"), wxDefaultPosition, wxSize(-1, -1), 0);
    m_buttonClearSuppressions->SetToolTip(_("Untick all the boxes"));
    
    bSizer61->Add(m_buttonClearSuppressions, 0, wxALL, 5);
    
    m_checkBoxSerialise = new wxCheckBox(m_SuppressPanel, wxID_ANY, _("Remember these settings"), wxDefaultPosition, wxSize(-1, -1), 0);
    m_checkBoxSerialise->SetValue(false);
    m_checkBoxSerialise->SetToolTip(_("If ticked, these settings will be saved and be applied in the future. Otherwise the warnings will be back when you restart CodeLite, which may be what you should want."));
    
    bSizer81->Add(m_checkBoxSerialise, 0, wxALL, 10);
    
    m_IncludeDirs = new wxPanel(m_notebook1, wxID_ANY, wxDefaultPosition, wxSize(-1, -1), wxTAB_TRAVERSAL);
    m_notebook1->AddPage(m_IncludeDirs, _("Include Dirs"), false);
    
    wxBoxSizer* bSizer812 = new wxBoxSizer(wxVERTICAL);
    m_IncludeDirs->SetSizer(bSizer812);
    
    m_staticText113 = new wxStaticText(m_IncludeDirs, wxID_ANY, _("If the 'Missing Includes' check is enabled, add here any extra\ndirectories where Cppcheck should search for #includes"), wxDefaultPosition, wxSize(-1, -1), 0);
    
    bSizer812->Add(m_staticText113, 0, wxALL, 5);
    
    wxBoxSizer* bSizer514 = new wxBoxSizer(wxHORIZONTAL);
    
    bSizer812->Add(bSizer514, 1, wxEXPAND, 5);
    
    wxArrayString m_listBoxIncludeDirsArr;
    m_listBoxIncludeDirs = new wxListBox(m_IncludeDirs, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), m_listBoxIncludeDirsArr, wxLB_SINGLE);
    
    bSizer514->Add(m_listBoxIncludeDirs, 1, wxALL|wxEXPAND, 5);
    
    wxBoxSizer* bSizer616 = new wxBoxSizer(wxVERTICAL);
    
    bSizer514->Add(bSizer616, 0, wxEXPAND, 5);
    
    m_buttonAddIncludeDir = new wxButton(m_IncludeDirs, wxID_ANY, _("Add"), wxDefaultPosition, wxSize(-1, -1), 0);
    m_buttonAddIncludeDir->SetToolTip(_("Add the full path to a directory to search for #includes"));
    
    bSizer616->Add(m_buttonAddIncludeDir, 0, wxALL, 5);
    
    m_buttonRemoveIncludeDir = new wxButton(m_IncludeDirs, wxID_ANY, _("Remove"), wxDefaultPosition, wxSize(-1, -1), 0);
    
    bSizer616->Add(m_buttonRemoveIncludeDir, 0, wxALL, 5);
    
    bSizer616->Add(0, 0, 0, wxTOP, 15);
    
    m_checkBoxSuppressSystemIncludes = new wxCheckBox(m_IncludeDirs, wxID_ANY, _("Suppress warnings about 'system' includes"), wxDefaultPosition, wxSize(-1, -1), 0);
    m_checkBoxSuppressSystemIncludes->SetValue(true);
    m_checkBoxSuppressSystemIncludes->SetToolTip(_("If ticked, the 'missingIncludeSystem' suppression is passed to Cppcheck. This stops it complaining about a missing #include <foo>, while still detecting a missing #include \"bar\""));
    
    bSizer812->Add(m_checkBoxSuppressSystemIncludes, 0, wxALL, 10);
    
    m_checkBoxSerialiseIncludeDirs = new wxCheckBox(m_IncludeDirs, wxID_ANY, _("Remember these settings"), wxDefaultPosition, wxSize(-1, -1), 0);
    m_checkBoxSerialiseIncludeDirs->SetValue(false);
    m_checkBoxSerialiseIncludeDirs->SetToolTip(_("If ticked, these settings will be saved and be applied in the future. Otherwise the warnings will be back when you restart CodeLite, which may be what you want."));
    
    bSizer812->Add(m_checkBoxSerialiseIncludeDirs, 0, wxALL, 10);
    
    m_DefinesPanel = new wxPanel(m_notebook1, wxID_ANY, wxDefaultPosition, wxSize(-1, -1), wxTAB_TRAVERSAL);
    m_notebook1->AddPage(m_DefinesPanel, _("Command-line Definitions"), false);
    
    wxBoxSizer* bSizer813 = new wxBoxSizer(wxVERTICAL);
    m_DefinesPanel->SetSizer(bSizer813);
    
    m_staticText11428 = new wxStaticText(m_DefinesPanel, wxID_ANY, _("Here you can pass 'configurations' to cppcheck\ne.g. \"Only test code branches where FOO is defined\" or\n\"Don't test code branches where the value of FOO is 2\""), wxDefaultPosition, wxSize(-1, -1), 0);
    
    bSizer813->Add(m_staticText11428, 0, wxALL, 5);
    
    m_staticLine18 = new wxStaticLine(m_DefinesPanel, wxID_ANY, wxDefaultPosition, wxSize(-1,-1), wxLI_HORIZONTAL);
    
    bSizer813->Add(m_staticLine18, 0, wxALL|wxEXPAND, 5);
    
    m_staticText11429 = new wxStaticText(m_DefinesPanel, wxID_ANY, _("Defines to pass e.g. FOO  or FOO=1:"), wxDefaultPosition, wxSize(-1, -1), 0);
    
    bSizer813->Add(m_staticText11429, 0, wxLEFT|wxRIGHT|wxTOP, 5);
    
    wxBoxSizer* bSizer51521 = new wxBoxSizer(wxHORIZONTAL);
    
    bSizer813->Add(bSizer51521, 1, wxEXPAND, 5);
    
    wxArrayString m_listBoxDefinelistArr;
    m_listBoxDefinelist = new wxListBox(m_DefinesPanel, wxID_ANY, wxDefaultPosition, wxSize(-1, -1), m_listBoxDefinelistArr, 0);
    m_listBoxDefinelist->SetToolTip(_("Add here definitions of code branches you want to be checked e.g. 'FOO' or 'BAR=2'. Each will be passed to Cppcheck as '-DFOO' or -D'BAR=2' (so don't write the -D yourself)."));
    
    bSizer51521->Add(m_listBoxDefinelist, 1, wxALL|wxEXPAND, 5);
    
    wxBoxSizer* bSizer61723 = new wxBoxSizer(wxVERTICAL);
    
    bSizer51521->Add(bSizer61723, 0, wxEXPAND, 5);
    
    m_buttonAdd1824 = new wxButton(m_DefinesPanel, wxID_ANY, _("Add"), wxDefaultPosition, wxSize(-1, -1), 0);
    m_buttonAdd1824->SetToolTip(_("Add file(s) to the excluded files list"));
    
    bSizer61723->Add(m_buttonAdd1824, 0, wxALL, 5);
    
    m_buttonRemove1925 = new wxButton(m_DefinesPanel, wxID_ANY, _("Remove"), wxDefaultPosition, wxSize(-1, -1), 0);
    m_buttonRemove1925->SetToolTip(_("Remove the selected file from the excluded file list"));
    
    bSizer61723->Add(m_buttonRemove1925, 0, wxALL, 5);
    
    m_buttonClearList2026 = new wxButton(m_DefinesPanel, wxID_ANY, _("Clear"), wxDefaultPosition, wxSize(-1, -1), 0);
    m_buttonClearList2026->SetToolTip(_("Clear the excluded files list"));
    
    bSizer61723->Add(m_buttonClearList2026, 0, wxALL, 5);
    
    m_staticText114 = new wxStaticText(m_DefinesPanel, wxID_ANY, _("Undefines to pass:"), wxDefaultPosition, wxSize(-1, -1), 0);
    
    bSizer813->Add(m_staticText114, 0, wxLEFT|wxRIGHT|wxTOP, 5);
    
    wxBoxSizer* bSizer515 = new wxBoxSizer(wxHORIZONTAL);
    
    bSizer813->Add(bSizer515, 1, wxEXPAND, 5);
    
    wxArrayString m_listBoxUndefineListArr;
    m_listBoxUndefineList = new wxListBox(m_DefinesPanel, wxID_ANY, wxDefaultPosition, wxSize(-1, -1), m_listBoxUndefineListArr, 0);
    m_listBoxUndefineList->SetToolTip(_("Here you can add undefines (branches you don't want to be checked) e.g. 'FOO' or 'BAR=2'. Each will be passed to Cppcheck as '-UFOO' or -U'BAR=2' (so don't write the -U yourself)."));
    
    bSizer515->Add(m_listBoxUndefineList, 1, wxALL|wxEXPAND, 5);
    
    wxBoxSizer* bSizer617 = new wxBoxSizer(wxVERTICAL);
    
    bSizer515->Add(bSizer617, 0, wxEXPAND, 5);
    
    m_buttonAdd18 = new wxButton(m_DefinesPanel, wxID_ANY, _("Add"), wxDefaultPosition, wxSize(-1, -1), 0);
    m_buttonAdd18->SetToolTip(_("Add file(s) to the excluded files list"));
    
    bSizer617->Add(m_buttonAdd18, 0, wxALL, 5);
    
    m_buttonRemove19 = new wxButton(m_DefinesPanel, wxID_ANY, _("Remove"), wxDefaultPosition, wxSize(-1, -1), 0);
    m_buttonRemove19->SetToolTip(_("Remove the selected file from the excluded file list"));
    
    bSizer617->Add(m_buttonRemove19, 0, wxALL, 5);
    
    m_buttonClearList20 = new wxButton(m_DefinesPanel, wxID_ANY, _("Clear"), wxDefaultPosition, wxSize(-1, -1), 0);
    m_buttonClearList20->SetToolTip(_("Clear the excluded files list"));
    
    bSizer617->Add(m_buttonClearList20, 0, wxALL, 5);
    
    m_staticline1 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxSize(-1, -1), wxLI_HORIZONTAL);
    
    bSizer1->Add(m_staticline1, 0, wxALL|wxEXPAND, 5);
    
    wxBoxSizer* bSizer2 = new wxBoxSizer(wxHORIZONTAL);
    
    bSizer1->Add(bSizer2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5);
    
    m_BtmOK = new wxButton(this, wxID_OK, _("&OK"), wxDefaultPosition, wxSize(-1, -1), 0);
    m_BtmOK->SetDefault();
    
    bSizer2->Add(m_BtmOK, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5);
    
    m_BtnCancel = new wxButton(this, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxSize(-1, -1), 0);
    
    bSizer2->Add(m_BtnCancel, 0, wxALL, 5);
    
    SetSizeHints(-1,-1);
    if ( GetSizer() ) {
         GetSizer()->Fit(this);
    }
    Centre();
    // Connect events
    m_buttonAllChecks->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CppCheckSettingsDialogBase::OnChecksTickAll), NULL, this);
    m_buttonAllChecks->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(CppCheckSettingsDialogBase::OnChecksTickAllUI), NULL, this);
    m_buttonClearChecks->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CppCheckSettingsDialogBase::OnChecksUntickAll), NULL, this);
    m_buttonClearChecks->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(CppCheckSettingsDialogBase::OnChecksUntickAllUI), NULL, this);
    m_spinCtrlJobs->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(CppCheckSettingsDialogBase::OnJobsUpdateUI), NULL, this);
    m_buttonAdd->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CppCheckSettingsDialogBase::OnAddFile), NULL, this);
    m_buttonRemove->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CppCheckSettingsDialogBase::OnRemoveFile), NULL, this);
    m_buttonRemove->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(CppCheckSettingsDialogBase::OnRemoveFileUI), NULL, this);
    m_buttonClearList->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CppCheckSettingsDialogBase::OnClearList), NULL, this);
    m_buttonClearList->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(CppCheckSettingsDialogBase::OnClearListUI), NULL, this);
    m_buttonAddSuppression->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CppCheckSettingsDialogBase::OnAddSuppression), NULL, this);
    m_buttonRemoveSuppression->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CppCheckSettingsDialogBase::OnRemoveSuppression), NULL, this);
    m_buttonRemoveSuppression->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(CppCheckSettingsDialogBase::OnRemoveSuppressionUI), NULL, this);
    m_buttonSuppressAll->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CppCheckSettingsDialogBase::OnSuppressTickAll), NULL, this);
    m_buttonSuppressAll->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(CppCheckSettingsDialogBase::OnSuppressTickAllUI), NULL, this);
    m_buttonClearSuppressions->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CppCheckSettingsDialogBase::OnSuppressUntickAll), NULL, this);
    m_buttonClearSuppressions->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(CppCheckSettingsDialogBase::OnSuppressUntickAllUI), NULL, this);
    m_IncludeDirs->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(CppCheckSettingsDialogBase::OnIncludeDirsUpdateUI), NULL, this);
    m_buttonAddIncludeDir->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CppCheckSettingsDialogBase::OnAddIncludeDir), NULL, this);
    m_buttonRemoveIncludeDir->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CppCheckSettingsDialogBase::OnRemoveIncludeDir), NULL, this);
    m_buttonRemoveIncludeDir->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(CppCheckSettingsDialogBase::OnRemoveIncludeDirUI), NULL, this);
    m_buttonAdd1824->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CppCheckSettingsDialogBase::OnAddDefinition), NULL, this);
    m_buttonRemove1925->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CppCheckSettingsDialogBase::OnRemoveDefinition), NULL, this);
    m_buttonRemove1925->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(CppCheckSettingsDialogBase::OnRemoveDefinitionUI), NULL, this);
    m_buttonClearList2026->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CppCheckSettingsDialogBase::OnClearDefinitions), NULL, this);
    m_buttonClearList2026->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(CppCheckSettingsDialogBase::OnClearDefinitionsUI), NULL, this);
    m_buttonAdd18->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CppCheckSettingsDialogBase::OnAddUndefine), NULL, this);
    m_buttonRemove19->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CppCheckSettingsDialogBase::OnRemoveUndefine), NULL, this);
    m_buttonRemove19->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(CppCheckSettingsDialogBase::OnRemoveUndefineUI), NULL, this);
    m_buttonClearList20->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CppCheckSettingsDialogBase::OnClearUndefines), NULL, this);
    m_buttonClearList20->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(CppCheckSettingsDialogBase::OnClearUndefinesUI), NULL, this);
    m_BtmOK->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CppCheckSettingsDialogBase::OnBtnOK), NULL, this);
    
}

CppCheckSettingsDialogBase::~CppCheckSettingsDialogBase()
{
    m_buttonAllChecks->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CppCheckSettingsDialogBase::OnChecksTickAll), NULL, this);
    m_buttonAllChecks->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(CppCheckSettingsDialogBase::OnChecksTickAllUI), NULL, this);
    m_buttonClearChecks->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CppCheckSettingsDialogBase::OnChecksUntickAll), NULL, this);
    m_buttonClearChecks->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(CppCheckSettingsDialogBase::OnChecksUntickAllUI), NULL, this);
    m_spinCtrlJobs->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(CppCheckSettingsDialogBase::OnJobsUpdateUI), NULL, this);
    m_buttonAdd->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CppCheckSettingsDialogBase::OnAddFile), NULL, this);
    m_buttonRemove->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CppCheckSettingsDialogBase::OnRemoveFile), NULL, this);
    m_buttonRemove->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(CppCheckSettingsDialogBase::OnRemoveFileUI), NULL, this);
    m_buttonClearList->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CppCheckSettingsDialogBase::OnClearList), NULL, this);
    m_buttonClearList->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(CppCheckSettingsDialogBase::OnClearListUI), NULL, this);
    m_buttonAddSuppression->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CppCheckSettingsDialogBase::OnAddSuppression), NULL, this);
    m_buttonRemoveSuppression->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CppCheckSettingsDialogBase::OnRemoveSuppression), NULL, this);
    m_buttonRemoveSuppression->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(CppCheckSettingsDialogBase::OnRemoveSuppressionUI), NULL, this);
    m_buttonSuppressAll->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CppCheckSettingsDialogBase::OnSuppressTickAll), NULL, this);
    m_buttonSuppressAll->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(CppCheckSettingsDialogBase::OnSuppressTickAllUI), NULL, this);
    m_buttonClearSuppressions->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CppCheckSettingsDialogBase::OnSuppressUntickAll), NULL, this);
    m_buttonClearSuppressions->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(CppCheckSettingsDialogBase::OnSuppressUntickAllUI), NULL, this);
    m_IncludeDirs->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(CppCheckSettingsDialogBase::OnIncludeDirsUpdateUI), NULL, this);
    m_buttonAddIncludeDir->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CppCheckSettingsDialogBase::OnAddIncludeDir), NULL, this);
    m_buttonRemoveIncludeDir->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CppCheckSettingsDialogBase::OnRemoveIncludeDir), NULL, this);
    m_buttonRemoveIncludeDir->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(CppCheckSettingsDialogBase::OnRemoveIncludeDirUI), NULL, this);
    m_buttonAdd1824->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CppCheckSettingsDialogBase::OnAddDefinition), NULL, this);
    m_buttonRemove1925->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CppCheckSettingsDialogBase::OnRemoveDefinition), NULL, this);
    m_buttonRemove1925->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(CppCheckSettingsDialogBase::OnRemoveDefinitionUI), NULL, this);
    m_buttonClearList2026->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CppCheckSettingsDialogBase::OnClearDefinitions), NULL, this);
    m_buttonClearList2026->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(CppCheckSettingsDialogBase::OnClearDefinitionsUI), NULL, this);
    m_buttonAdd18->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CppCheckSettingsDialogBase::OnAddUndefine), NULL, this);
    m_buttonRemove19->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CppCheckSettingsDialogBase::OnRemoveUndefine), NULL, this);
    m_buttonRemove19->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(CppCheckSettingsDialogBase::OnRemoveUndefineUI), NULL, this);
    m_buttonClearList20->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CppCheckSettingsDialogBase::OnClearUndefines), NULL, this);
    m_buttonClearList20->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(CppCheckSettingsDialogBase::OnClearUndefinesUI), NULL, this);
    m_BtmOK->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CppCheckSettingsDialogBase::OnBtnOK), NULL, this);
    
}

CppCheckAddSuppressionDialogBase::CppCheckAddSuppressionDialogBase(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
    : wxDialog(parent, id, title, pos, size, style)
{
    if ( !bBitmapLoaded ) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxCrafterRo2g8MInitBitmapResources();
        bBitmapLoaded = true;
    }
    
    wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(bSizer1);
    
    m_staticText12 = new wxStaticText(this, wxID_ANY, _("Description to show in the dialog"), wxDefaultPosition, wxSize(-1, -1), 0);
    
    bSizer1->Add(m_staticText12, 0, wxALL, 5);
    
    m_txtDescription = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(-1, -1), 0);
    m_txtDescription->SetToolTip(_("This is what you'll see in the settings dialog. Put whatever you like here; it's not used internally"));
    
    bSizer1->Add(m_txtDescription, 0, wxALL|wxEXPAND, 5);
    
    m_staticText13 = new wxStaticText(this, wxID_ANY, _("The ID string that cppchecker will recognise"), wxDefaultPosition, wxSize(-1, -1), 0);
    
    bSizer1->Add(m_staticText13, 0, wxALL, 5);
    
    m_txtKey = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(-1, -1), 0);
    m_txtKey->SetToolTip(_("Enter here the unique ID string that cppchecker can recognise. Examples are \"operatorEqVarError\" and \"uninitMemberVar\". You can find these by grepping the cppchecker source, or by running cppchecker on your app in a terminal and passing the additional parameter '--xml'."));
    
    bSizer1->Add(m_txtKey, 0, wxALL|wxEXPAND, 5);
    
    m_staticline1 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxSize(-1, -1), wxLI_HORIZONTAL);
    
    bSizer1->Add(m_staticline1, 0, wxALL|wxEXPAND, 5);
    
    wxBoxSizer* bSizer2 = new wxBoxSizer(wxHORIZONTAL);
    
    bSizer1->Add(bSizer2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5);
    
    m_buttonOK = new wxButton(this, wxID_OK, _("&OK"), wxDefaultPosition, wxSize(-1, -1), 0);
    m_buttonOK->SetDefault();
    
    bSizer2->Add(m_buttonOK, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5);
    
    m_buttonCancel = new wxButton(this, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxSize(-1, -1), 0);
    
    bSizer2->Add(m_buttonCancel, 0, wxALL, 5);
    
    SetSizeHints(-1,-1);
    if ( GetSizer() ) {
         GetSizer()->Fit(this);
    }
    Centre(wxBOTH);
    // Connect events
    m_buttonOK->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(CppCheckAddSuppressionDialogBase::OnOKButtonUpdateUI), NULL, this);
    
}

CppCheckAddSuppressionDialogBase::~CppCheckAddSuppressionDialogBase()
{
    m_buttonOK->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(CppCheckAddSuppressionDialogBase::OnOKButtonUpdateUI), NULL, this);
    
}
