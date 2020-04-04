/////////////////////////////////////////////////////////////////////////////
// Name:        MenuButton.cpp
// Author:      Mateusz Kosmala <mateuszkosmala1@gmail.com>
// Created:     2012-03-03
// Copyright:   (c) 2020 by Mateusz Kosmala
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////


#include "MenuButton.h"
#include <Utils.h>

wxDEFINE_EVENT(wxEVT_MENUBTN_ACTIVATED, MenuButtonEvent);
wxDEFINE_EVENT(wxEVT_MENUBTN_CLICK, MenuButtonEvent);

// RTTI
wxIMPLEMENT_DYNAMIC_CLASS(MenuButtonEvent, wxCommandEvent);
wxIMPLEMENT_DYNAMIC_CLASS(MenuButton, wxControl);

MenuButton::MenuButton(wxWindow* parent, wxWindowID id, wxPoint pos, wxBitmap normal, wxBitmap hover, wxBitmap activate)
	:wxControl(parent, id, pos, wxSize(40,50), wxBORDER_NONE)
{

	Bind(wxEVT_ENTER_WINDOW, &MenuButton::OnHover, this, wxID_ANY);
	Bind(wxEVT_LEAVE_WINDOW, &MenuButton::OnHoverEnd, this, wxID_ANY);
	Bind(wxEVT_LEFT_DOWN, &MenuButton::OnClick, this, wxID_ANY);
	Bind(wxEVT_LEFT_UP, &MenuButton::OnActivate, this, wxID_ANY);
	Bind(wxEVT_PAINT, &MenuButton::OnPaint, this, wxID_ANY);
	Bind(wxEVT_SIZE, &MenuButton::OnSize, this, wxID_ANY);
	Bind(wxEVT_SIZING, &MenuButton::OnSize, this, wxID_ANY);

	this->n = normal;
	this->h = hover;
	this->a = activate;

}





MenuButton::~MenuButton()
{
	Unbind(wxEVT_ENTER_WINDOW, &MenuButton::OnHover, this, wxID_ANY);
	Unbind(wxEVT_LEAVE_WINDOW, &MenuButton::OnHoverEnd, this, wxID_ANY);
	Unbind(wxEVT_LEFT_DOWN, &MenuButton::OnClick, this, wxID_ANY);
	Unbind(wxEVT_LEFT_UP, &MenuButton::OnActivate, this, wxID_ANY);
	Unbind(wxEVT_PAINT, &MenuButton::OnPaint, this, wxID_ANY);
	Unbind(wxEVT_SIZE, &MenuButton::OnSize, this, wxID_ANY);
	Unbind(wxEVT_SIZING, &MenuButton::OnSize, this, wxID_ANY);
}


void MenuButton::OnSize(wxSizeEvent& event)
{
	wxClientDC dc(this);
	dc.Clear();
	dc.SetBrush(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
	wxSize SizeWindow = this->GetSize();
	int height = (SizeWindow.x / 2) - 15;
	int length = (SizeWindow.y / 2) - 15;
	dc.DrawRectangle(300, 100, 300, 300);
	dc.DrawBitmap(n, height, length, false);

}



void MenuButton::OnHover(wxMouseEvent& WXUNUSED(event))
{

	
	wxClientDC dc(this);
	dc.Clear();
	dc.SetBrush(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));

	wxSize SizeWindow = this->GetSize();
	int height = (SizeWindow.x /2) - 15;
	int length = (SizeWindow.y / 2) - 15;
	dc.DrawRectangle(300, 100, 300, 300);
	dc.DrawBitmap(n, height, length, false); 


}


void MenuButton::OnHoverEnd(wxMouseEvent& WXUNUSED(event))
{
	wxClientDC dc(this);
	dc.Clear();
	dc.SetBrush(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
	wxSize SizeWindow = this->GetSize();
	int height = (SizeWindow.x / 2) - 15;
	int length = (SizeWindow.y / 2) - 15;
	dc.DrawRectangle(300, 100, 300, 300);
	dc.DrawBitmap(n, height, length, false); 

}

void MenuButton::OnClick(wxMouseEvent& WXUNUSED(event))
{

	wxClientDC dc(this);
	dc.Clear();
	dc.SetBrush(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
	dc.DrawRectangle(300, 100, 300, 300);

	dc.SetBrush(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));      //Complete ! 
	dc.SetPen(wxPen(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE), 9));
	dc.DrawCircle(wxPoint(23, 25), 18);
	wxSize SizeWindow = this->GetSize();
	int height = (SizeWindow.x / 2) - 16;
	int length = (SizeWindow.y / 2) - 16;
	dc.DrawRectangle(300, 100, 300, 300);
	dc.DrawBitmap(h, height, length, false); 


	
	MenuButtonEvent event(wxEVT_MENUBTN_CLICK, this->GetId());
	event.SetEventObject(this);
	ProcessWindowEvent(event);

}


void MenuButton::OnActivate(wxMouseEvent& WXUNUSED(event))
{

	wxClientDC dc(this);
	dc.Clear();
	dc.SetBrush(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
	wxSize SizeWindow = this->GetSize();
	int height = (SizeWindow.x / 2) - 15;
	int length = (SizeWindow.y / 2) - 15;
	dc.DrawRectangle(300, 100, 300, 300);
	dc.DrawBitmap(n, height, length, false); 

	//Skip Event
	MenuButtonEvent evt(wxEVT_MENUBTN_ACTIVATED, this->GetId());
	evt.SetEventObject(this);
	ProcessEvent(evt);

}


void MenuButton::OnPaint(wxPaintEvent& WXUNUSED(event))
{

	//User Image
	wxClientDC dc(this);
	dc.Clear();
	dc.SetBrush(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
	wxSize SizeWindow = this->GetSize();
	int height = (SizeWindow.x / 2) - 15;
	int length = (SizeWindow.y / 2) - 15;
	dc.DrawRectangle(300, 100, 300, 300);
	dc.DrawBitmap(n, height, length, false);
	
}


