/////////////////////////////////////////////////////////////////////////////
// Name:        ScrolledPanel.cpp
// Author:      Mateusz Kosmala <mateuszkosmala1@gmail.com>
// Created:     2012-03-03
// Copyright:   (c) 2020 by Mateusz Kosmala
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#include <wx/datetime.h>
#include<ScrolledPanel.h>
#include <wx/graphics.h>
#include <vector>
#include <cmath>

const wxWindowIDRef ID_NEWBUTTON = wxWindow::NewControlId();

wxBEGIN_EVENT_TABLE(ScrolledPanel, wxScrolled<wxPanel>)
EVT_PAINT(ScrolledPanel::OnPaint)
EVT_SCROLLWIN(ScrolledPanel::OnScroll)
EVT_SCROLLWIN_THUMBTRACK(ScrolledPanel::OnScroll)
EVT_SCROLLWIN_THUMBRELEASE(ScrolledPanel::OnScroll)
wxEND_EVENT_TABLE()

ScrolledPanel::ScrolledPanel(wxWindow* parent)
	: wxScrolled<wxPanel>(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL)
{
	doc.Load(wxString("C:\\Users\\metju\\Desktop\\Programming\\ConsoleApplications\\SEth\\SEth\\docs\\MessagesStructure.xml"), "UTF-8");
	//Rest
	SetScrollRate(20, 20);
	wxSize Size1 = this->GetSize();
	SetVirtualSize(Size1.x, 2000);
	wxSize Size = GetVirtualSize();
	SetBackgroundColour("WHITE");
	Number_Controls = 0;
	HEIGHT_POINT = 2000;
	activity = new wxActivityIndicator(this, wxID_ANY, wxPoint(300, 50), wxSize(25, 25), 0, wxString("Za³aduj wiêcej"));
	activity->Start();
	activity->SetHelpText(wxString("Za³aduj wiêcej"));
	this->HEIGHT_POINTSCROLL = 2000;
}

void ScrolledPanel::OnScroll(wxScrollWinEvent& event)
{
	if (this->GetScrollPos(wxVERTICAL) == 1)
	{
		activity->Hide();
		this->Freeze();
		this->Clear();
		this->HEIGHT_POINTSCROLL = this->HEIGHT_POINTSCROLL * 2;
		this->HEIGHT_POINT = this->HEIGHT_POINTSCROLL;
		this->Scroll(0, 0);
		this->ShowScrollbars(wxSHOW_SB_NEVER, wxSHOW_SB_NEVER);
		this->SetVirtualSize(200, this->HEIGHT_POINTSCROLL);
		this->AddTextToModel(wxEmptyString, this->LAST);
		this->ShowScrollbars(wxSHOW_SB_NEVER, wxSHOW_SB_ALWAYS);
		this->Scroll(400, 100000);
		this->Refresh();
		this->Layout();
		activity->Show();
		this->Thaw();
	}

	event.Skip();
}

void ScrolledPanel::OnPaint(wxPaintEvent& WXUNUSED(event))
{
	wxPaintDC dc(this);
	PrepareDC(dc);
	
}

bool ScrolledPanel::Clear(void)
{
	int i = bitmaps.size();
	if (i == 0)
		return true;

	--i;
	for (i; i >= 0; --i)
	{
		delete bitmaps[i];
	}
	bitmaps.resize(0);
	HEIGHT_POINT = 2000;
	return true;
}

bool ScrolledPanel::AddAllToControl(wxString text, int SCROLL)
{
	wxBitmap drawBitmap = this->AddTextAndBitmap(text);
	wxSize Size = GetVirtualSize();
	wxSize BitmapSize = drawBitmap.GetSize();
	HEIGHT_POINT = HEIGHT_POINT - BitmapSize.y - 3;

	if (SCROLL == NEW_SELECT)
	{
		this->Scroll(0, 0);
	}
	else if (SCROLL == USER_TEXT)
	{
		this->SetVirtualSize(-1, Size.y + BitmapSize.y + 1); //WEIRD BEHAVIOUR IN CHANGING BETWEEN 1,2,3 ETC !
		wxSize size1 = this->GetSize();
		bitmaps.push_back(new wxStaticBitmap(this, wxID_ANY, drawBitmap, wxPoint(Size.x - 300, size1.y - 10), wxDefaultSize));
		return true;
	}
	else if (SCROLL == RECEIVE_MESSAGE)
	{
		this->SetVirtualSize(-1, Size.y + BitmapSize.y + 1);
		wxSize size1 = this->GetSize();
		wxCommandEvent event(wxEVT_COMMAND_TEXT_UPDATED, 6017);
		event.SetInt(size1.y);
		event.SetString(text);
		m_parent->GetEventHandler()->AddPendingEvent(event);
		return true;
	}
	else if(SCROLL == RECEIVE_MESSAGE_START)
	{
		this->Scroll(0, 0);
		wxBitmap drawBitmap = this->AddTextAndBitmap(text, ScrolledPanel::RECEIVE_MESSAGE);
		bitmaps.push_back(new wxStaticBitmap(this, wxID_ANY, drawBitmap, wxPoint(0, HEIGHT_POINT - 10), wxDefaultSize));
		return true;
	}
	
	bitmaps.push_back(new wxStaticBitmap(this, wxID_ANY, drawBitmap, wxPoint(Size.x - 300 - 17, HEIGHT_POINT - 10), wxDefaultSize));

	return true;
}

wxBitmap  ScrolledPanel::AddTextAndBitmap(wxString string, int mode)
{
	double lenght = string.Length();
	int x = 1;
	int start = 0;
	int end = 35;
	double upper = (lenght / 36);
	int i = ceil(upper);
	wxBitmap test(300, i * 19);
	wxMemoryDC dc(test);
	dc.SetBrush(*wxBLACK_BRUSH);
	dc.SetPen(*wxBLACK_PEN);
	dc.SetBrush(*wxWHITE_BRUSH);
	dc.SetPen(*wxWHITE_PEN);

	dc.DrawRectangle(0, 0, 300, i * 19 + 10);
	wxGraphicsContext* gc = wxGraphicsContext::Create(dc);

	if (mode == RECEIVE_MESSAGE)
	{
		wxBrush brush(wxColor(235, 235, 235), wxBRUSHSTYLE_SOLID);
		wxPen pen(wxColor(245, 245, 245));
		gc->SetBrush(brush);
		gc->SetPen(pen);
	}
	else
	{
		wxBrush brush(wxColor(0, 153, 255), wxBRUSHSTYLE_SOLID);
		wxPen pen(wxColor(0, 153, 255));
		gc->SetBrush(brush);
		gc->SetPen(pen);
	}

	gc->DrawRoundedRectangle(1, 1, 299, i * 19, 10);
	if (mode == RECEIVE_MESSAGE)
		gc->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_MEDIUM, false), wxColor(0, 0, 0));

	else
		gc->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_MEDIUM, false), wxColor(255, 255, 255));

	for (int y = 0; y < i; ++y)
	{
		gc->DrawText(string.SubString(start, end), 7, x); //The same as radius-2
		x += 19;
		start += 36;
		end += 36;
	}

	return test;
}

bool ScrolledPanel::AddTextToModel(wxString text, long long ID)
{
	wxString workingstring;
	workingstring << ID;
	LAST = ID;
	wxXmlNode* root = this->doc.GetRoot();
	wxXmlNode* children = root->GetChildren();

	if (children == NULL)
		return false;

	else
	{
		wxXmlNode* subchildren = children;
		while (subchildren)
		{
			if (subchildren->GetAttribute(wxString("ID")) == workingstring)
			{
				//EXISITNG WITH GIVEN ID!
				wxXmlNode* message = subchildren->GetChildren();

				if (message == NULL)
					return false;

				else
				{
					//HAS ANY MESSAGES!
					wxXmlNode* submessage = message;

					while (submessage)
					{
						if (HEIGHT_POINT < 70)
							return true;

						//Through every Content
						wxXmlNode* content = submessage->GetChildren();

						wxXmlAttribute* attribute = submessage->GetAttributes();
						wxString attributetext = attribute->GetName();

						if (attributetext.IsSameAs("R"))
							this->AddAllToControl(content->GetContent(), RECEIVE_MESSAGE_START);
						else
							this->AddAllToControl(content->GetContent());

						submessage = submessage->GetNext();
					}
				}

				return true;
			}

			else
				subchildren = subchildren->GetNext();
		}

		return false;
	}

	return true;
}