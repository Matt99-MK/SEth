/////////////////////////////////////////////////////////////////////////////
// Name:        UserModelData.h
// Author:      Mateusz Kosmala <mateuszkosmala1@gmail.com>
// Created:     2012-03-03
// Copyright:   (c) 2020 by Mateusz Kosmala
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _UMODELD_H_
#define _UMODELD_H_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class UserModelData 
{

public:

	enum
	{
		STATUS_ACTIV = 0,
		STATUS_DISACTIVE,
		
	};

	UserModelData() {}
	UserModelData(bool Favourite = 0 ,unsigned long long ID_USER = 0, wxString Name = wxEmptyString, wxString Surname = wxEmptyString, wxString IP_ADRESS = wxEmptyString,
		bool BOLD = 0, wxString Photo_Path = wxEmptyString, wxString City = wxEmptyString, int STATUS = UserModelData::STATUS_DISACTIVE);
	~UserModelData();
	bool GetFavourite(void);
	unsigned long long GetID(void);
	wxString GetName(void);
	wxString GetSurname(void);
	wxString GetIP(void);
	bool GetBold(void);
	wxString GetPath(void);
	wxString GetCity(void);
	int GetStatus(void);
	bool SetFavourite(bool Favourite);
	bool SetID(unsigned long long ID_USER);
	bool SetName(wxString Name);
	bool SetSurname(wxString Surname);
	bool SetIP(wxString IP_ADRESS);
	bool SetBold(bool BOLD);
	bool SetPath(wxString Photo_Path);
	bool SetCity(wxString City);
	bool SetStatus(int STATUS);

public:	

	bool Favourite;
	unsigned long long ID_USER;
	wxString Name;
	wxString Surname;
	wxString IP_ADRESS;
	bool BOLD;
	wxString Photo_Path;
	wxString City;
	int STATUS;

};



#endif