/////////////////////////////////////////////////////////////////////////////
// Name:        MainXmlDocument.h
// Author:      Mateusz Kosmala <mateuszkosmala1@gmail.com>
// Created:     2012-03-03
// Copyright:   (c) 2020 by Mateusz Kosmala
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _MAINXMLDOCUMENT_H_
#define _MAINXMLDOCUMENT_H_

#include <wx/string.h>
#include <wx/xml/xml.h>
#include <UserModelData.h>

class MainXmlDocument : public wxXmlDocument
{

public:

    MainXmlDocument() : wxXmlDocument() {}
    bool AddUser(UserModelData* usermodel);

private:

    wxString path;

};


#endif
