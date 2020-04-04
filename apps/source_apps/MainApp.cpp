/////////////////////////////////////////////////////////////////////////////
// Name:        MainApp.cpp
// Author:      Mateusz Kosmala <mateuszkosmala1@gmail.com>
// Created:     2012-03-03
// Copyright:   (c) 2020 by Mateusz Kosmala
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include<MainApp.h>
#include <wx/config.h>
#include <wx/stdpaths.h>


const wxString AppName = wxT("SEth");

//---------------------------------------------------------------------------
// Implementacja aplikacji.
//---------------------------------------------------------------------------

IMPLEMENT_APP(MainApp)

//---------------------------------------------------------------------------
// Identyfikatory
//---------------------------------------------------------------------------
enum
{
	ID_APPON_START = wxID_HIGHEST + 1,
	
};

bool MainApp::OnInit()
{

	wxInitAllImageHandlers();
	frame = new MainWindow(NULL, wxID_ANY, AppName, wxDefaultPosition, wxSize(980, 670), wxDEFAULT_FRAME_STYLE);
	frame->Show(true);
	frame->resize = 0;
	frame->Bind(wxEVT_SIZE, &MainWindow::OnSize, frame);
	

	//Setting config
	IP_ADRESS = wxString("192.168.0.105");
	PORT = wxString("3306");
	wxFileConfig* config = new wxFileConfig(AppName, "", wxString("C:\\Users\\metju\\Desktop\\Programming\\ConsoleApplications\\SEth\\SEth\\docs\\settings.conf.txt"));
	config->DeleteAll();
	config->Write(wxT("AppConfig/App"),0);
	config->Write(wxT("Servers/Default"), IP_ADRESS);
	config->Write(wxT("Protocols/Default"), PORT);
	config->Flush();



	return true;

}
