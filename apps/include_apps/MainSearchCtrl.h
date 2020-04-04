// Name:        MainSearchCtrl.h
// Author:      Mateusz Kosmala <mateuszkosmala1@gmail.com>
// Created:     2012-03-03
// Copyright:   (c) 2020 by Mateusz Kosmala
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////


#ifndef _MAINSEARCHCTRL_H__
#define _MAINSEARCHCTRL_H__
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/srchctrl.h>

class MainSearchCtrl : public wxSearchCtrl
{
public:
    MainSearchCtrl(wxWindow* parent, wxWindowID id, const wxString& value = wxEmptyString, const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxSearchCtrlNameStr);
    MainSearchCtrl(){}
    void OnSend(wxCommandEvent& event);
    void Key(wxKeyEvent& event);

    

private:
 
    wxDECLARE_EVENT_TABLE();
    wxDECLARE_DYNAMIC_CLASS(MainSearchCtrl);

};


#endif