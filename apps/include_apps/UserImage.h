/////////////////////////////////////////////////////////////////////////////
// Name:        UserImage.cpp
// Author:      Mateusz Kosmala <mateuszkosmala1@gmail.com>
// Created:     2012-03-03
// Copyright:   (c) 2020 by Mateusz Kosmala
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _USERBTN_H__
#define _USERBTN_H__

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif


class UserImage : public wxControl
{

	public:
	
		enum
		{

			ID_ON_ACTIVE = 0,
			ID_ON_DISACTIVE


		};

	UserImage() { }
	UserImage(wxWindow* parent, wxWindowID id, wxPoint pos, wxSize size,int status );
	wxString* PathToPhoto;
	virtual ~UserImage();
	bool ChangeStatus(int status);
	void OnSize(wxSizeEvent& event);
	bool ChangePhoto(wxString path);

	protected:
	
	virtual wxSize DoGetBestSize() const
	{ //Use as default size of control
		return wxSize(26, 26);
	}
	
	void OnPaint(wxPaintEvent& evt);
	void OnClick(wxMouseEvent& event);
	
	private:
	
	wxBitmap* UserPhoto;
	wxBitmap* FrameOnActive;
	wxBitmap* FrameOnDisActive;
	int status;
	wxDECLARE_DYNAMIC_CLASS(UserImage);

};

#endif