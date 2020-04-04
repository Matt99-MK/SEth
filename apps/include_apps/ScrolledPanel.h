/////////////////////////////////////////////////////////////////////////////
// Name:        ScrolledPanel.h
// Author:      Mateusz Kosmala <mateuszkosmala1@gmail.com>
// Created:     2012-03-03
// Copyright:   (c) 2020 by Mateusz Kosmala
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#include<AppList.h>
#include<vector>
#include <wx/activityindicator.h>
#include <MainXmlDocument.h>
#ifndef _SCROLLPANEL_H__
#define _SCROLLPANEL_H__
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

// ScrolledPanel
class ScrolledPanel : public wxScrolled<wxPanel>
{
public:
    enum
    {
        NEW_SELECT =0,
        USER_TEXT,
        RECEIVE_MESSAGE,
        RECEIVE_MESSAGE_START,
    };

public:
    ScrolledPanel(wxWindow* parent);
    wxBitmap AddTextAndBitmap(wxString text,int mode = NEW_SELECT);
    wxXmlDocument doc;
    double HEIGHT_POINT;
    double HEIGHT_POINTSCROLL;
    bool AddAllToControl(wxString text, int SCROLL = 0);
    bool Clear(void);
    bool AddTextToModel(wxString text , long long item);
    std::vector<wxStaticBitmap*> bitmaps;
    void ChangePanelSize(wxBitmap bitmap);
    void OnResize(wxSizeEvent& event);
    unsigned long long ID;
    void OnMouse(wxMouseEvent& event);
    void OnScroll(wxScrollWinEvent& event);

private:
    void OnPaint(wxPaintEvent& event);
    int Number_Controls;
    wxActivityIndicator* activity;
    wxButton* m_button;
    long long LAST;

    wxDECLARE_EVENT_TABLE();
};


#endif