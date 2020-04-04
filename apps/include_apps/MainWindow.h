/////////////////////////////////////////////////////////////////////////////
// Name:        MainWindow.cpp
// Author:      Mateusz Kosmala <mateuszkosmala1@gmail.com>
// Created:     2012-03-03
// Copyright:   (c) 2020 by Mateusz Kosmala
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#include <UserImage.h>
#include <MainXmlDocument.h>
#include<wx/toolbar.h>
#include<MenuButton.h>
#include<ScrolledPanel.h>
#include<AddUserButton.h>
#include <AppList.h>
#include<MainSearchCtrl.h>
#include <wx/srchctrl.h>
#include<Poco/Net/TCPServer.h>
#include "Session.h"
#include "DenyFilter.h"
#include <wx/log.h>
#include <opencv2/opencv.hpp>



#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

class MainWindow: public wxFrame
{

    public:

        MainWindow(wxWindow *parent, wxWindowID id, const wxString &title,
            const wxPoint &position, const wxSize &size, long style);
        ~MainWindow();    
        UserModelData* GetRestInfoDateBase(UserModelData* usermodel);
        void MainWindow::OnUpdate(wxCommandEvent& evt);
        UserModelData* GetRestInfoSettings(UserModelData* usermodel);
        bool Initialization(void);
        wxStaticText *statictext;
        AppList* contactlist;
        UserImage *MainImage;
        wxBoxSizer* MainSizer;
        void autoremove(wxXmlNode* root);
        MainXmlDocument* messagestructure;
        wxBoxSizer* MainHorizontalSizer;
        void OnResize(wxSizeEvent& event);
        MainXmlDocument* usersstructure;
        MainSearchCtrl* searchmain;
        MainXmlDocument* ReturnUS(void);
        void OnMenuClick(MenuButtonEvent& event);
        wxToolBar* toolbar;
        wxStaticBitmap* userphotos;
        bool toolbar_status;
        void OnAttachClick(AddUserButtonEvent& event);
        void OnSettingsClick(AddUserButtonEvent& event);
        void OnSendClick(AddUserButtonEvent& event);
        void OnSend(wxCommandEvent& event);
        bool  MainWindow::OnReceive(std::string a,std::string ip);
        void SelectionChanged(wxDataViewEvent& event);
        void OnVideoClick(AddUserButtonEvent& event);
        void Testing(wxIdleEvent& event);
        void OnSize(wxSizeEvent& event);
        ScrolledPanel* myscrolledpanel;
        wxStaticText* usertext;
        TCPServer* srv;
        StreamSocket* ss;
        void OnTimer(wxTimerEvent& event);
        wxLog* logger;
        int resize;
        void OnMove(wxMouseEvent& event);
        void OnClick(wxMouseEvent& event);
        bool AddAccount(UserModelData* usermodel);
       
    private:      
        wxTimer m_timer;

        DECLARE_EVENT_TABLE()

};

#endif
