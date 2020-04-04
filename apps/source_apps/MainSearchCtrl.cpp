// Name:        MainSearchCtrl.cpp
// Author:      Mateusz Kosmala <mateuszkosmala1@gmail.com>
// Created:     2012-03-03
// Copyright:   (c) 2020 by Mateusz Kosmala
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#include<MainSearchCtrl.h>
#include<AddUserButton.h>

wxIMPLEMENT_DYNAMIC_CLASS(MainSearchCtrl, wxSearchCtrl);

BEGIN_EVENT_TABLE(MainSearchCtrl, wxSearchCtrl)
END_EVENT_TABLE()

MainSearchCtrl::MainSearchCtrl(wxWindow* parent, wxWindowID id, const wxString& value, const wxPoint& pos,
    const wxSize& size, long style, const wxValidator& validator, const wxString& name)
   : wxSearchCtrl(parent,id,value,pos,size,style,validator,name)
{
	this->Bind(wxEVT_CHAR_HOOK, &MainSearchCtrl::Key, this);

}
void MainSearchCtrl::OnSend(wxCommandEvent& event)
{

	wxMessageBox(wxString("Working!"));
	event.Skip();

}
void MainSearchCtrl::Key(wxKeyEvent& event)
{

	if (event.GetKeyCode() == WXK_RETURN)

	{
		AddUserButtonEvent event1(wxEVT_ADDUSRBTN_ACTIVATED, 6015);
		event1.SetEventObject(this);
		ProcessWindowEvent(event1);
	}

	event.Skip();

}
