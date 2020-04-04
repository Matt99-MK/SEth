/////////////////////////////////////////////////////////////////////////////
// Name:        UserImage.cpp
// Author:      Mateusz Kosmala <mateuszkosmala1@gmail.com>
// Created:     2012-03-03
// Copyright:   (c) 2020 by Mateusz Kosmala
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#include "UserImage.h"
#include <Utils.h>
#include <wx/filedlg.h>

// RTTI
wxIMPLEMENT_DYNAMIC_CLASS(UserImage, wxControl);

UserImage::UserImage(wxWindow* parent, wxWindowID id, wxPoint pos, wxSize size,int status)
	:wxControl(parent, id, pos, wxSize(50,50),wxBORDER_NONE)
{
	
	Bind(wxEVT_PAINT, &UserImage::OnPaint, this, wxID_ANY);
	Bind(wxEVT_SIZE, &UserImage::OnSize, this, wxID_ANY);
	Bind(wxEVT_SIZING, &UserImage::OnSize, this, wxID_ANY);
	Bind(wxEVT_LEFT_UP, &UserImage::OnClick, this, wxID_ANY);
	this->status = status;
	this->PathToPhoto = new wxString("C:\\Users\\metju\\Desktop\\Programming\\ConsoleApplications\\SEth\\SEth\\extern_files\\Icons\\123.jpg");
	
	//Active
	wxBitmap WorkedBitmap(wxString("C:\\Users\\metju\\Desktop\\Programming\\ConsoleApplications\\SEth\\SEth\\extern_files\\Icons\\stop1.png"), wxBITMAP_TYPE_PNG);
	wxImage WorkedImage = WorkedBitmap.ConvertToImage();
	WorkedImage.Rescale(40, 40);
	this->FrameOnActive = new wxBitmap(WorkedImage);
	
	//Disactive
	wxBitmap WorkedBitmap1(wxString("C:\\Users\\metju\\Desktop\\Programming\\ConsoleApplications\\SEth\\SEth\\extern_files\\Icons\\stop2.png"), wxBITMAP_TYPE_PNG);
	WorkedImage = WorkedBitmap1.ConvertToImage();
	WorkedImage.Rescale(40, 40);
	this->FrameOnDisActive =  new wxBitmap(WorkedImage);

	//Photo
	wxBitmap WorkedBitmap11(*PathToPhoto, wxBITMAP_TYPE_JPEG);
	WorkedImage = WorkedBitmap11.ConvertToImage();
	WorkedImage.Rescale(40, 40);
	this->UserPhoto = new wxBitmap(WorkedImage);

	
}

void UserImage::OnClick(wxMouseEvent& event)
{

	wxFileDialog openFileDialog(this, _("Change Image"), "", "", "JPEG files (*.jpg)|*.jpg", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;
	else
	{

		this->ChangePhoto(openFileDialog.GetPath());

	}

}


bool UserImage::ChangeStatus(int status)
{

	if (this->status = status)
		return true;
	else
		return false;

}

bool UserImage::ChangePhoto(wxString path)
{

	wxBitmap WorkedBitmap11(path, wxBITMAP_TYPE_JPEG);
	wxImage WorkedImage = WorkedBitmap11.ConvertToImage();
	WorkedImage.Rescale(40, 40);
	this->UserPhoto = new wxBitmap(WorkedImage);
	wxClientDC dc(this);
	dc.Clear();
	dc.SetBrush(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
	dc.DrawRectangle(300, 100, 300, 300);

	wxSize SizeWindow = this->GetSize();
	int height = (SizeWindow.x / 2) - 22;
	int length = (SizeWindow.y / 2) - 22;

	dc.DrawBitmap(*this->UserPhoto, height, length, false);

	if (this->status == UserImage::ID_ON_ACTIVE)
	{

		dc.DrawBitmap(*this->FrameOnActive, height, length, false);

	}
	else
	{
		dc.DrawBitmap(*this->FrameOnDisActive, height, length, false);

	};

	return true;

}


UserImage::~UserImage()
{

	Unbind(wxEVT_PAINT, &UserImage::OnPaint, this, wxID_ANY);
	Unbind(wxEVT_SIZE, &UserImage::OnSize, this, wxID_ANY);
	Unbind(wxEVT_SIZING, &UserImage::OnSize, this, wxID_ANY);
	Unbind(wxEVT_LEFT_UP, &UserImage::OnClick, this, wxID_ANY);

}

void UserImage::OnSize(wxSizeEvent& event)
{

	//User Image
	wxClientDC dc(this);
	dc.Clear();
	dc.SetBrush(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
	dc.DrawRectangle(300, 100, 300, 300);
	wxSize SizeWindow = this->GetSize();
	int height = (SizeWindow.x / 2) - 22;
	int length = (SizeWindow.y / 2) - 22;
	dc.DrawBitmap(*this->UserPhoto, height, length, false);

	if (this->status == UserImage::ID_ON_ACTIVE)
	{

		dc.DrawBitmap(*this->FrameOnActive, height, length, false);

	}
	else
	{

		dc.DrawBitmap(*this->FrameOnDisActive, height, length, false);

	};

}


void UserImage::OnPaint(wxPaintEvent& WXUNUSED(event))
{

	//User Image
	wxClientDC dc(this);
	dc.Clear();
	dc.SetBrush(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
	dc.DrawRectangle(300, 100, 300, 300);
	wxSize SizeWindow = this->GetSize();
	int height = (SizeWindow.x / 2) - 22;
	int length = (SizeWindow.y / 2) - 22;
	dc.DrawBitmap(*this->UserPhoto, height, length, false);

	if (this->status == UserImage::ID_ON_ACTIVE)
	{
	
		dc.DrawBitmap(*this->FrameOnActive, height, length, false);
	}

	else
	{

		dc.DrawBitmap(*this->FrameOnDisActive, height, length, false);

	};


}


