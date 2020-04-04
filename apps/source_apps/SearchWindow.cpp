/////////////////////////////////////////////////////////////////////////////
// Name:        SearchWindow.cpp
// Author:      Mateusz Kosmala <mateuszkosmala1@gmail.com>
// Created:     2012-03-03
// Copyright:   (c) 2020 by Mateusz Kosmala
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "SearchWindow.h"
#include<MainApp.h>
#include<AppList.h>




wxBEGIN_EVENT_TABLE(SearchWindow, wxSearchCtrl)
EVT_TEXT(wxID_ANY, SearchWindow::OnText)
wxEND_EVENT_TABLE()
wxIMPLEMENT_DYNAMIC_CLASS(SearchWindow, wxSearchCtrl);

SearchWindow::~SearchWindow()
{
    
    Unbind(wxEVT_LEFT_DOWN, &SearchWindow::OnDown, this, wxID_ANY);
    Unbind(wxEVT_LEFT_DCLICK, &SearchWindow::OnDClick, this, wxID_ANY);
    Unbind(wxEVT_LEFT_DCLICK, &SearchWindow::OnDClick, this, wxID_ANY);
    Unbind(wxEVT_CHAR, &SearchWindow::OnChar, this, wxID_ANY);

}

void SearchWindow::OnChar(wxKeyEvent& event)
{

    wxString text = this->GetValue();

    if (text.IsSameAs(wxString(""), true) )
    {
        

       this->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
           wxFONTWEIGHT_SEMIBOLD, false));
        this->SetForegroundColour(*wxBLACK);
        
        wxString char1(event.GetUnicodeKey());
        
        if (char1.IsSameAs("\b"))
        {
            this->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_ITALIC,
                wxFONTWEIGHT_LIGHT, false));
            this->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DDKSHADOW));
            this->SetDescriptiveText(wxString("Searching"));
            return;
        }
        char1.MakeUpper();

        this->AppendText(char1);

        return;
    }
    else
    {
        
        wxString Compare = text.Last();
        wxString char1(event.GetUnicodeKey());

        if (Compare.IsSameAs("\u0020") && !(char1.IsSameAs("\b")))
        {
            char1.MakeUpper();
            this->AppendText(char1);
            return;

        }

        wxString text1 = this->GetValue();

        if (char1.IsSameAs("\b") && (text1.Length() == 1))
        {
            
            this->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_ITALIC,
                wxFONTWEIGHT_LIGHT, false));
            this->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DDKSHADOW));
           
        }

    }


    if (text.IsSameAs(wxString("Searching"), true))
    {
        this->Clear();
        return;
    }
      
   //BE CONTINUED...-------------------------------------------------------------------------------------------------------
   

    event.Skip();
}


void SearchWindow::OnDClick(wxMouseEvent& event)
{

    this->SelectAll();

}

void SearchWindow::OnLeave(wxMouseEvent& event)
{
 
    wxString text = this->GetValue();
    if (text.IsSameAs(wxString(""), true))
    {

    this->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_ITALIC,
        wxFONTWEIGHT_LIGHT, false));
    this->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DDKSHADOW));
    this->SetDescriptiveText(wxString("Searching"));
      
    }
   


}


SearchWindow::SearchWindow(wxWindow* parent,
    wxWindowID 	id,
    const wxString& value ,
    const wxPoint& pos ,
    const wxSize& size,
    long 	style,
    const wxValidator& validator ,
    const wxString& name )
    : wxSearchCtrl(parent, id, value, pos, size, style, validator, name)
{

    Bind(wxEVT_CHAR, &SearchWindow::OnChar, this, wxID_ANY);
    Bind(wxEVT_LEFT_DOWN, &SearchWindow::OnDown, this, wxID_ANY);
    Bind(wxEVT_LEAVE_WINDOW, &SearchWindow::OnLeave, this, wxID_ANY);
    Bind(wxEVT_LEFT_DCLICK, &SearchWindow::OnDClick, this, wxID_ANY);

}


void SearchWindow::OnText(wxCommandEvent& event)
{
    
}

void SearchWindow::OnDown(wxMouseEvent& event)
{
    
    wxString text = this->GetValue();
    if(text.IsSameAs(wxString("Searching"), true))
    {

        this->Clear();

    }
    else 
    {
       
    }
    this->SetFocus();
    this->SetForegroundColour(*wxBLACK);
    

    /*
   wxBitmap FrameOnActiveBack;
   FrameOnActiveBack.LoadFile(wxString("C:\\Users\\metju\\Desktop\\Programming\\ConsoleApplications\\SEth\\SEth\\extern_files\\Icons\\color.png"), wxBITMAP_TYPE_PNG);
   wxImage Circle = FrameOnActiveBack.ConvertToImage();
   Circle.Rescale(58, 58, wxIMAGE_QUALITY_HIGH);
   FrameOnActiveBack = Circle;
   wxMessageBox("DZIA£A");

    MainApp &reference = wxGetApp();
    AppList *help =  reference.frame->contactlist;

    reference.frame->contactlist->SetValue(wxVariant(FrameOnActiveBack), help->Last_focused,0);
    */
    
}


