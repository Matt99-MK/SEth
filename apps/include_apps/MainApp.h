/////////////////////////////////////////////////////////////////////////////
// Name:        MainApp.h
// Author:      Mateusz Kosmala <mateuszkosmala1@gmail.com>
// Created:     2012-03-03
// Copyright:   (c) 2020 by Mateusz Kosmala
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _MAINAPP_H_
#define _MAINAPP_H_
#include <wx/fileconf.h>
#include<MainWindow.h>


//---------------------------------------------------------------------------
// Klasa MainApp
//---------------------------------------------------------------------------

class MainApp : public wxApp
{

    public:
    MainWindow* frame;
    wxString IP_ADRESS;
    wxString PORT;
    virtual bool OnInit();

};

DECLARE_APP(MainApp)


#endif
