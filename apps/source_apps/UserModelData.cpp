/////////////////////////////////////////////////////////////////////////////
// Name:        AppList.cpp
// Author:      Mateusz Kosmala <mateuszkosmala1@gmail.com>
// Created:     2012-03-03
// Copyright:   (c) 2020 by Mateusz Kosmala
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#include <UserModelData.h>

UserModelData::UserModelData(bool Favourite1, unsigned long long ID_USER1, wxString Name1,
	wxString Surname1, wxString IP_ADRESS1, bool BOLD1, wxString Photo_Path1, wxString City1, int STATUS1) : Favourite(Favourite1), ID_USER(ID_USER1), Name(Name1), Surname(Surname1),
	IP_ADRESS(IP_ADRESS1), BOLD(BOLD1) , Photo_Path(Photo_Path1), City(City1) , STATUS(STATUS1)
{
	
}


bool UserModelData::GetFavourite(void)
{

	return Favourite;

}

unsigned long long UserModelData::GetID(void)
{

	return ID_USER;

}

wxString UserModelData::GetName(void)
{

	return Name;

}

wxString UserModelData::GetSurname(void)
{

	return Surname;

}

wxString UserModelData::GetIP(void)
{

	return IP_ADRESS;

}

bool UserModelData::GetBold(void)
{

	return BOLD;

}

wxString UserModelData::GetPath(void)
{

	return Photo_Path;

}

wxString UserModelData::GetCity(void)
{

	return City;

}

int UserModelData::GetStatus(void)
{
	
	return STATUS;
	
}

bool UserModelData::SetFavourite(bool Favourite1)
{

	if (true)
	{

		Favourite = Favourite1;
		return true;

	}

	else
		return false;

}

bool UserModelData::SetID(unsigned long long ID_USER1)
{

	if (true)
	{

		ID_USER = ID_USER1;
		return true;

	}

	else
		return false;

}

bool UserModelData::SetName(wxString Name1)
{

	if (true)
	{

		Name = Name1;
		return true;

	}

	else
		return false;

} 


bool UserModelData::SetSurname(wxString Surname1)
{

	if (true)
	{

		Surname = Surname1;
		return true;

	}

	else
		return false;

}

bool UserModelData::SetIP(wxString IP_ADRESS1)
{

	if (true)
	{

		IP_ADRESS = IP_ADRESS1;
		return true;

	}

	else
		return false;

}

bool UserModelData::SetBold(bool BOLD1)
{

	if (true)
	{

		BOLD = BOLD1;
		return true;

	}

	else
		return false;

}

bool UserModelData::SetPath(wxString Photo_Path1)
{

	if (true)
	{

		Photo_Path = Photo_Path1;
		return true;

	}

	else
		return false;

}

bool UserModelData::SetCity(wxString City1)
{

	if (true)
	{

		City = City1;
		return true;

	}

	else
		return false;

}

bool UserModelData::SetStatus(int STATUS1)
{

	if (true)
	{

		STATUS = STATUS1;
		return true;

	}

	else
		return false;

}













UserModelData::~UserModelData()
{

}

