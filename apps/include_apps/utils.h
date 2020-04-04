/////////////////////////////////////////////////////////////////////////////
// Name:        utils.h
// Purpose:     tools file
// Author:      Mateusz Kosmala
// Created:     2020-03-03
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _UTILS_H_
#define _UTILS_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

//Return path of icon in more portable way
wxString wxGetAppFile(wxString file);

unsigned int Make_Random(void);

#endif