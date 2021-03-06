//
// This file was automatically generated by wxrc, do not edit by hand.
//

#include <wx/wxprec.h>

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#include <wx/filesys.h>
#include <wx/fs_mem.h>
#include <wx/xrc/xmlres.h>
#include <wx/xrc/xh_all.h>

#if wxCHECK_VERSION(2,8,5) && wxABI_VERSION >= 20805
    #define XRC_ADD_FILE(name, data, size, mime) \
        wxMemoryFSHandler::AddFileWithMimeType(name, data, size, mime)
#else
    #define XRC_ADD_FILE(name, data, size, mime) \
        wxMemoryFSHandler::AddFile(name, data, size)
#endif

static size_t xml_res_size_0 = 434;
static unsigned char xml_res_file_0[] = {
137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,16,0,0,0,16,8,6,0,0,
0,31,243,255,97,0,0,0,9,112,72,89,115,0,0,11,18,0,0,11,18,1,210,221,126,
252,0,0,0,4,103,65,77,65,0,0,177,142,124,251,81,147,0,0,0,32,99,72,82,77,
0,0,122,37,0,0,128,131,0,0,249,255,0,0,128,233,0,0,117,48,0,0,234,96,0,
0,58,152,0,0,23,111,146,95,197,70,0,0,1,40,73,68,65,84,120,218,98,248,255,
255,63,3,24,51,48,128,49,3,152,7,99,35,0,76,221,205,27,55,254,195,245,0,
49,64,0,49,49,144,8,222,190,127,143,194,7,8,32,184,1,140,96,12,50,147,145,
17,68,51,226,50,224,205,27,20,62,64,0,193,13,248,79,164,11,222,188,121,
139,194,7,8,32,36,23,128,189,14,167,97,97,129,14,94,191,126,133,194,7,8,
32,22,148,128,2,58,31,221,64,76,3,94,163,240,1,2,8,111,32,50,18,97,0,64,
0,33,185,128,17,106,253,127,88,144,98,13,199,55,175,81,3,17,32,128,88,144,
2,241,63,186,189,140,88,28,241,230,45,170,1,0,1,196,130,234,100,68,236,
1,195,3,107,24,188,67,75,7,0,1,196,8,11,107,100,7,131,52,67,12,67,8,74,
72,136,163,70,11,80,234,197,243,23,140,0,1,132,17,136,8,205,168,192,193,
193,145,225,243,231,207,12,159,191,124,6,211,142,64,62,8,0,4,16,60,77,131,
180,254,135,7,5,102,110,128,90,15,151,132,233,3,8,32,38,84,155,17,225,6,
9,3,84,67,34,34,34,80,104,16,0,8,32,120,24,0,3,225,63,102,58,64,132,3,34,
172,64,90,16,94,4,8,32,70,236,9,150,120,0,16,96,0,124,129,148,122,47,1,
57,27,0,0,0,0,73,69,78,68,174,66,96,130};

static size_t xml_res_size_1 = 253;
static unsigned char xml_res_file_1[] = {
60,63,120,109,108,32,118,101,114,115,105,111,110,61,34,49,46,48,34,32,101,
110,99,111,100,105,110,103,61,34,85,84,70,45,56,34,63,62,10,60,114,101,
115,111,117,114,99,101,32,120,109,108,110,115,61,34,104,116,116,112,58,
47,47,119,119,119,46,119,120,119,105,110,100,111,119,115,46,111,114,103,
47,119,120,120,114,99,34,32,118,101,114,115,105,111,110,61,34,50,46,51,
46,48,46,49,34,62,10,32,32,60,111,98,106,101,99,116,32,99,108,97,115,115,
61,34,119,120,66,105,116,109,97,112,34,32,110,97,109,101,61,34,115,111,
114,116,34,62,79,112,101,110,87,105,110,100,111,119,115,80,97,110,101,108,
66,97,115,101,95,108,105,116,101,101,100,105,116,111,114,95,98,105,116,
109,97,112,115,46,99,112,112,36,46,46,95,46,46,95,46,46,95,46,46,95,104,
111,109,101,95,100,97,118,105,100,95,68,111,119,110,108,111,97,100,115,
95,115,111,114,116,46,112,110,103,60,47,111,98,106,101,99,116,62,10,60,
47,114,101,115,111,117,114,99,101,62,10};

void wxCrafterKq0OgDInitBitmapResources()
{

    // Check for memory FS. If not present, load the handler:
    {
        wxMemoryFSHandler::AddFile(wxT("XRC_resource/dummy_file"), wxT("dummy one"));
        wxFileSystem fsys;
        wxFSFile *f = fsys.OpenFile(wxT("memory:XRC_resource/dummy_file"));
        wxMemoryFSHandler::RemoveFile(wxT("XRC_resource/dummy_file"));
        if (f) delete f;
        else wxFileSystem::AddHandler(new wxMemoryFSHandler);
    }

    XRC_ADD_FILE(wxT("XRC_resource/OpenWindowsPanelBase_liteeditor_bitmaps.cpp$.._.._.._.._home_david_Downloads_sort.png"), xml_res_file_0, xml_res_size_0, wxT("image/png"));
    XRC_ADD_FILE(wxT("XRC_resource/OpenWindowsPanelBase_liteeditor_bitmaps.cpp$OpenWindowsPanelBase_liteeditor_bitmaps.xrc"), xml_res_file_1, xml_res_size_1, wxT("text/xml"));
    wxXmlResource::Get()->Load(wxT("memory:XRC_resource/OpenWindowsPanelBase_liteeditor_bitmaps.cpp$OpenWindowsPanelBase_liteeditor_bitmaps.xrc"));
}
