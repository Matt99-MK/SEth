/////////////////////////////////////////////////////////////////////////////
// Name:        AddUserButton.h
// Author:      Mateusz Kosmala <mateuszkosmala1@gmail.com>
// Created:     2012-03-03
// Copyright:   (c) 2020 by Mateusz Kosmala
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _ADDUSRBTN_H__
#define _ADDUSRBTN_H__

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class AddUserButtonEvent : public wxCommandEvent
{

public:

	AddUserButtonEvent(wxEventType EventType = wxEVT_NULL, int id = wxID_ANY)
		: wxCommandEvent(EventType, id) {}
	wxEvent* Clone() const { return new AddUserButtonEvent(*this); }

private:

	wxDECLARE_DYNAMIC_CLASS(AddUserButtonEvent);
};

wxDECLARE_EVENT(wxEVT_ADDUSRBTN_ACTIVATED, AddUserButtonEvent);
wxDECLARE_EVENT(wxEVT_ADDUSRBTN_CLICK, AddUserButtonEvent);

typedef void (wxEvtHandler::* AddUserButtonEventFunction)(AddUserButtonEvent&);
#define AddUserButtonEventHandler(func) wxEVENT_HANDLER_CAST(AddUserButtonEventFunction, func)                    

#define EVT_ADDUSRBTN_ACTIVATED(id, func) \
	wx__DECLARE_EVT1(wxEVT_ADDUSRBTN_ACTIVATED, id, AddUserButtonEventHandler(func))
#define EVT_ADDUSRBTN_CLICK(id, func) \
	wx__DECLARE_EVT1(wxEVT_ADDUSRBTN_CLICK, id, AddUserButtonEventHandler(func))

//unused ranged event handlers
#define EVT_ADDUSRBTNRANGE_ACTIVATED(id1, id2, func) \
	wx__DECLARE_EVT2(wxEVT_ADDUSRBTN_ACTIVATED, id1, id2, AddUserButtonEventHandler(func))
#define EVT_ADDUSRBTNRANGE_CLICK(id1, id2, func) \
	wx__DECLARE_EVT2(wxEVT_ADDUSRBTN_CLICK, id1, id2, AddUserButtonEventHandler(func))

class AddUserButton : public wxControl
{

public:

	AddUserButton() { }
	AddUserButton(wxWindow* parent, wxWindowID id, wxPoint pos, wxBitmap normal, wxBitmap hover = wxNullBitmap, wxBitmap activate = wxNullBitmap,int color=0);
	virtual ~AddUserButton();
	bool Create(wxWindow* parent, wxWindowID id, wxPoint pos, wxBitmap normal, wxBitmap hover = wxNullBitmap, wxBitmap activate = wxNullBitmap);

protected:

	virtual wxSize DoGetBestSize() const { //Use as default size of control
		if (n.IsOk()) return n.GetSize();
		else return wxSize(64, 64);
	}

	void OnHover(wxMouseEvent& event);
	void OnHoverEnd(wxMouseEvent& event);
	void OnClick(wxMouseEvent& event);
	void OnActivate(wxMouseEvent& event);
	void OnPaint(wxPaintEvent& evt);
	void OnSize(wxSizeEvent& event);

private:

	wxBitmap n;
	wxColor color;
	wxBitmap h;
	wxBitmap a;

	wxDECLARE_DYNAMIC_CLASS(AddUserButton);

};

#endif