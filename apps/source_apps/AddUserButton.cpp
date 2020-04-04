/////////////////////////////////////////////////////////////////////////////
// Name:        AddUserButton.cpp
// Author:      Mateusz Kosmala <mateuszkosmala1@gmail.com>
// Created:     2012-03-03
// Copyright:   (c) 2020 by Mateusz Kosmala
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#include "AddUserButton.h"
#include <Utils.h>
///
wxDEFINE_EVENT(wxEVT_ADDUSRBTN_ACTIVATED, AddUserButtonEvent);
wxDEFINE_EVENT(wxEVT_ADDUSRBTN_CLICK, AddUserButtonEvent);

// RTTI
wxIMPLEMENT_DYNAMIC_CLASS(AddUserButtonEvent, wxCommandEvent);
wxIMPLEMENT_DYNAMIC_CLASS(AddUserButton, wxControl);

AddUserButton::AddUserButton(wxWindow* parent, wxWindowID id, wxPoint pos, wxBitmap normal, wxBitmap hover, wxBitmap activate, int color)
	:wxControl(parent, id, pos, wxSize(40, 50),wxBORDER_NONE)
{

	Bind(wxEVT_ENTER_WINDOW, &AddUserButton::OnHover, this, wxID_ANY);
	Bind(wxEVT_LEAVE_WINDOW, &AddUserButton::OnHoverEnd, this, wxID_ANY);
	Bind(wxEVT_LEFT_DOWN, &AddUserButton::OnClick, this, wxID_ANY);
	Bind(wxEVT_LEFT_UP, &AddUserButton::OnActivate, this, wxID_ANY);
	Bind(wxEVT_PAINT, &AddUserButton::OnPaint, this, wxID_ANY);
	Bind(wxEVT_SIZE, &AddUserButton::OnSize, this, wxID_ANY);
	Bind(wxEVT_SIZING, &AddUserButton::OnSize, this, wxID_ANY);

	if (color != 0)
	{
		this->color = wxColor(255, 255, 255);
	}
	else
	this->color = wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE);

	
	this->n = normal;
	this->h = hover;
	this->a = activate;

}





AddUserButton::~AddUserButton()
{
	Unbind(wxEVT_ENTER_WINDOW, &AddUserButton::OnHover, this, wxID_ANY);
	Unbind(wxEVT_LEAVE_WINDOW, &AddUserButton::OnHoverEnd, this, wxID_ANY);
	Unbind(wxEVT_LEFT_DOWN, &AddUserButton::OnClick, this, wxID_ANY);
	Unbind(wxEVT_LEFT_UP, &AddUserButton::OnActivate, this, wxID_ANY);
	Unbind(wxEVT_PAINT, &AddUserButton::OnPaint, this, wxID_ANY);
	Unbind(wxEVT_SIZE, &AddUserButton::OnSize, this, wxID_ANY);
	Unbind(wxEVT_SIZING, &AddUserButton::OnSize, this, wxID_ANY);
}


void AddUserButton::OnSize(wxSizeEvent& event)
{
	wxClientDC dc(this);
	dc.Clear();
	dc.SetBrush(color);
	wxSize SizeWindow = this->GetSize();
	int height = (SizeWindow.x / 2) - 16;
	int length = (SizeWindow.y / 2) - 16;
	dc.DrawRectangle(300, 100, 300, 300);
	dc.DrawBitmap(n, height, length, false);

}



void AddUserButton::OnHover(wxMouseEvent& WXUNUSED(event))
{
	//for future use
}


void AddUserButton::OnHoverEnd(wxMouseEvent& WXUNUSED(event))
{
	//for future use
}

void AddUserButton::OnClick(wxMouseEvent& WXUNUSED(event))
{

	wxClientDC dc(this);
	dc.Clear();
	dc.SetBrush(color);
	dc.DrawRectangle(300, 100, 300, 300);

	dc.SetBrush(color);      //Complete ! 
	dc.SetPen(wxPen(color, 9));
	dc.DrawCircle(wxPoint(23, 25), 18);
	wxSize SizeWindow = this->GetSize();
	int height = (SizeWindow.x / 2) - 17;
	int length = (SizeWindow.y / 2) - 19;
	dc.DrawRectangle(300, 100, 300, 300);
	dc.DrawBitmap(h, height, length, false);



	AddUserButtonEvent event(wxEVT_ADDUSRBTN_CLICK, this->GetId());
	event.SetEventObject(this);
	ProcessWindowEvent(event);

}


void AddUserButton::OnActivate(wxMouseEvent& WXUNUSED(event))
{

	wxClientDC dc(this);
	dc.Clear();
	dc.SetBrush(color);
	wxSize SizeWindow = this->GetSize();
	int height = (SizeWindow.x / 2) - 16;
	int length = (SizeWindow.y / 2) - 16;
	dc.DrawRectangle(300, 100, 300, 300);
	dc.DrawBitmap(n, height, length, false);

	//Skip Event
	AddUserButtonEvent evt(wxEVT_ADDUSRBTN_ACTIVATED, this->GetId());
	evt.SetEventObject(this);
	ProcessEvent(evt);

}


void AddUserButton::OnPaint(wxPaintEvent& WXUNUSED(event))
{

	//User Image
	wxClientDC dc(this);
	dc.Clear();
	dc.SetBrush(color);
	wxSize SizeWindow = this->GetSize();
	int height = (SizeWindow.x / 2) - 16;
	int length = (SizeWindow.y / 2) - 16;
	dc.DrawRectangle(300, 100, 300, 300);
	dc.DrawBitmap(n, height, length, false);

}


