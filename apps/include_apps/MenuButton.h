/////////////////////////////////////////////////////////////////////////////
// Name:        MenuButton.h
// Author:      Mateusz Kosmala <mateuszkosmala1@gmail.com>
// Created:     2012-03-03
// Copyright:   (c) 2020 by Mateusz Kosmala
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _MENUBTN_H__
#define _MENUBTN_H__

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class MenuButtonEvent : public wxCommandEvent
{

public:

	MenuButtonEvent(wxEventType EventType = wxEVT_NULL, int id = wxID_ANY)
		: wxCommandEvent(EventType, id) {}
	wxEvent* Clone() const { return new MenuButtonEvent(*this); }

private:

	wxDECLARE_DYNAMIC_CLASS(MenuButtonEvent);
};

wxDECLARE_EVENT(wxEVT_MENUBTN_ACTIVATED, MenuButtonEvent);
wxDECLARE_EVENT(wxEVT_MENUBTN_CLICK, MenuButtonEvent);

typedef void (wxEvtHandler::* MenuButtonEventFunction)(MenuButtonEvent&);
#define MenuButtonEventHandler(func) wxEVENT_HANDLER_CAST(MenuButtonEventFunction, func)                    

#define EVT_MENUBTN_ACTIVATED(id, func) \
	wx__DECLARE_EVT1(wxEVT_MENUBTN_ACTIVATED, id, MenuButtonEventHandler(func))
#define EVT_MENUBTN_CLICK(id, func) \
	wx__DECLARE_EVT1(wxEVT_MENUBTN_CLICK, id, MenuButtonEventHandler(func))

//unused ranged event handlers
#define EVT_MENUBTNRANGE_ACTIVATED(id1, id2, func) \
	wx__DECLARE_EVT2(wxEVT_MENUBTN_ACTIVATED, id1, id2, MenuButtonEventHandler(func))
#define EVT_MENUBTNRANGE_CLICK(id1, id2, func) \
	wx__DECLARE_EVT2(wxEVT_MENUBTN_CLICK, id1, id2, MenuButtonEventHandler(func))

class MenuButton : public wxControl
{

public:

	MenuButton() { }
	MenuButton(wxWindow* parent, wxWindowID id, wxPoint pos, wxBitmap normal, wxBitmap hover = wxNullBitmap, wxBitmap activate = wxNullBitmap);
	virtual ~MenuButton();
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
	wxBitmap h;
	wxBitmap a;

	wxDECLARE_DYNAMIC_CLASS(MenuButton);

};

#endif