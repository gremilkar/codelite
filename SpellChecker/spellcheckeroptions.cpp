/////////////////////////////////////////////////////////////////////////////
// Purpose:
// Author:      Frank Lichtner
// Modified by:
// Created:     02/02/14
// SVN-ID:      $Id: spellcheckeroptions.cpp 35 2014-02-22 18:18:49Z Frank $
// Copyright:   2014 Frank Lichtner
// License:
/////////////////////////////////////////////////////////////////////////////
#include "spellcheckeroptions.h"
#include <cl_standard_paths.h>
// ------------------------------------------------------------
SpellCheckerOptions::SpellCheckerOptions()
{
    m_dictionary.Empty();
    m_dictionaryPath.Empty();
    m_scanStr = true;
    m_scanCPP = false;
    m_scanC   = false;
    m_scanD1  = false;
    m_scanD2  = false;
    
    wxString defaultDicsDir;
    defaultDicsDir << clStandardPaths::Get().GetDataDir() << wxFILE_SEP_PATH << "dics";
    m_dictionaryPath = defaultDicsDir;
}

// ------------------------------------------------------------
SpellCheckerOptions::~SpellCheckerOptions()
{
}

// ------------------------------------------------------------
void SpellCheckerOptions::DeSerialize( Archive& arch )
{
    arch.Read( wxT( "m_dictionary" ), m_dictionary );
    arch.Read( wxT( "m_dictionaryPath" ), m_dictionaryPath );
    arch.Read( wxT( "m_scanStr" ), m_scanStr );
    arch.Read( wxT( "m_scanCPP" ), m_scanCPP );
    arch.Read( wxT( "m_scanC" ), m_scanC );
    arch.Read( wxT( "m_scanD1" ), m_scanD1 );
    arch.Read( wxT( "m_scanD2" ), m_scanD2 );
}

// ------------------------------------------------------------
void SpellCheckerOptions::Serialize( Archive& arch )
{
    arch.Write( wxT( "m_dictionary" ), m_dictionary );
    arch.Write( wxT( "m_dictionaryPath" ), m_dictionaryPath );
    arch.Write( wxT( "m_scanStr" ), m_scanStr );
    arch.Write( wxT( "m_scanCPP" ), m_scanCPP );
    arch.Write( wxT( "m_scanC" ), m_scanC );
    arch.Write( wxT( "m_scanD1" ), m_scanD1 );
    arch.Write( wxT( "m_scanD2" ), m_scanD2 );
}
// ------------------------------------------------------------
