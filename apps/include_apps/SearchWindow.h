/////////////////////////////////////////////////////////////////////////////
// Name:        SearchWindow.h
// Author:      Mateusz Kosmala <mateuszkosmala1@gmail.com>
// Created:     2012-03-03
// Copyright:   (c) 2020 by Mateusz Kosmala
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _SEARCHWIND_H__
#define _SEARCHWIND_H__

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/srchctrl.h>


class SearchWindow : public wxSearchCtrl
{

public:

    SearchWindow(wxWindow* parent,
        wxWindowID 	id,
        const wxString& value = wxEmptyString,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long 	style = 0,
        const wxValidator& validator = wxDefaultValidator,
        const wxString& name = wxTextCtrlNameStr);
   
    ~SearchWindow();
    void OnText(wxCommandEvent& event);
    void OnLeave(wxMouseEvent& event);
    void OnDown(wxMouseEvent& event);
    void OnClick(wxMouseEvent& event);
    void OnDClick(wxMouseEvent& event);
    void OnChar(wxKeyEvent& event);
    SearchWindow() {}

private:
   
    wxDECLARE_DYNAMIC_CLASS(SearchWindow);
    wxDECLARE_EVENT_TABLE();

};




#endif