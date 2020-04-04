/////////////////////////////////////////////////////////////////////////////
// Name:        AppList.h
// Author:      Mateusz Kosmala <mateuszkosmala1@gmail.com>
// Created:     2012-03-03
// Copyright:   (c) 2020 by Mateusz Kosmala
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _APPLIST_H_
#define _APPLIST_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/dataview.h>
#include <UserModelData.h>
#include<DatabaseConnection.h>
class AppList : public wxDataViewListCtrl
{

public:
	
	AppList() {}
	AppList(wxWindow* parent, wxWindowID id,
		const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDV_ROW_LINES, const wxValidator& validator = wxDefaultValidator);
	~AppList();
	bool Initialization(void);
	bool RecreateList(void);
	bool Saving(void);
	wxBitmap PaintProfil(const wxDataViewItem& profil,const int& background);
	bool CreateAccount(UserModelData* usermodel);
	void CreateUser(void);
	void SelectionChanged(wxDataViewEvent& event);
	void OnMove(wxMouseEvent& event);
	wxDataViewItem actual_item;
	int Row_counts;
	DatabaseConnection *connection;
	int Last_focused;
	
private:

	wxVector<wxVariant> data;
	UserModelData* model;
	wxImage image;
	wxBitmap FrameOnActiveBack;
	wxBitmap FrameOnDisActiveBack;
	wxBitmap CircleOnActive;
	wxBitmap Last_Picture;

	DECLARE_EVENT_TABLE()
	wxDECLARE_DYNAMIC_CLASS(AppList);

};

#endif