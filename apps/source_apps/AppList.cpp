/////////////////////////////////////////////////////////////////////////////
// Name:        AppList.cpp
// Author:      Mateusz Kosmala <mateuszkosmala1@gmail.com>
// Created:     2012-03-03
// Copyright:   (c) 2020 by Mateusz Kosmala
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#include<ColumnRender.h>
#include <AppList.h>
#include<MainXmlDocument.h>
#include<MainWindow.h>
#include<MainApp.h>
#include "DatabaseConnection.h"
#include<Poco/Tuple.h>
#include <wx/dcgraph.h>
#include <Poco/Nullable.h>

using namespace Poco::Data::Keywords;
using Poco::Data::Session;
using Poco::Data::Statement;

wxIMPLEMENT_DYNAMIC_CLASS(AppList, wxDataViewListCtrl);

BEGIN_EVENT_TABLE(AppList, wxDataViewListCtrl)
EVT_DATAVIEW_SELECTION_CHANGED(wxID_ANY, AppList::SelectionChanged)
END_EVENT_TABLE()



AppList::AppList(wxWindow* parent, wxWindowID id,
	const wxPoint& pos, const wxSize& size, long style, const wxValidator& validator)
	: wxDataViewListCtrl(parent, id, pos, size, style, validator)
{

	Last_focused = 0;
	Row_counts = 0;
	AppendBitmapColumn(wxString("BitMapColumn"), 0);
	wxDataViewTextRenderer* const markupRenderer = new wxDataViewTextRenderer();
	markupRenderer->EnableMarkup();
	wxDataViewColumn* m_attributes = new wxDataViewColumn("attributes", markupRenderer, 1, 80, wxALIGN_LEFT);
	AppendColumn(m_attributes);
	SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
	SetRowHeight(60);
	FrameOnActiveBack.LoadFile(wxString("C:\\Users\\metju\\Desktop\\Programming\\ConsoleApplications\\SEth\\SEth\\extern_files\\Icons\\color3.png"), wxBITMAP_TYPE_PNG);
	FrameOnDisActiveBack.LoadFile(wxString("C:\\Users\\metju\\Desktop\\Programming\\ConsoleApplications\\SEth\\SEth\\extern_files\\Icons\\color1.png"), wxBITMAP_TYPE_PNG);
	CircleOnActive.LoadFile(wxString("C:\\Users\\metju\\Desktop\\Programming\\ConsoleApplications\\SEth\\SEth\\extern_files\\Icons\\circle1.png"), wxBITMAP_TYPE_PNG);
	wxImage Circle = FrameOnActiveBack.ConvertToImage();
	Circle.Rescale(58, 58, wxIMAGE_QUALITY_HIGH);
	FrameOnActiveBack = Circle;
	this->model = nullptr;
	wxImage Circle1 = FrameOnDisActiveBack.ConvertToImage();
	Circle1.Rescale(58, 58, wxIMAGE_QUALITY_HIGH);
	FrameOnDisActiveBack = Circle1;

	connection = new DatabaseConnection("192.168.0.105");

	//MainApp& reference = wxGetApp();
	//users = reference.frame->usersstructure;

}

bool AppList::RecreateList(void)
{

	int i = 0;
	while (!(i >= this->Row_counts))
	{
		this->SetValue(wxVariant(PaintProfil(this->RowToItem(i), UserModelData::STATUS_DISACTIVE)), this->ItemToRow(this->RowToItem(i)), 0);
		++i;
	}

	return true;

}

void AppList::SelectionChanged(wxDataViewEvent& event)
{
	this->UnselectAll();

	if (this->Last_focused != 0 || this->Last_focused == 0)
	{

		this->SetValue(wxVariant(PaintProfil(this->RowToItem(this->Last_focused), UserModelData::STATUS_DISACTIVE)), this->Last_focused, 0);

	}

	wxDataViewItem item;

	if (item = event.GetItem())

	{
		actual_item = item;
		this->Select(item);
		this->Last_focused = this->ItemToRow(item);
		this->SetValue(wxVariant(PaintProfil(item, UserModelData::STATUS_ACTIV)), this->Last_focused, 0);
	    event.Skip();

	}
	
}

bool ImageToCircle(const wxImage& sourceImage,
	const wxPoint& circleCenter, const wxCoord circleRadius,
	wxImage& resultImage)
{
	
	const wxRect circleRect(circleCenter.x - circleRadius, circleCenter.y - circleRadius,
		2 * circleRadius, 2 * circleRadius);
	wxRect resultRect(wxPoint(0, 0), sourceImage.GetSize());

	resultRect.Intersect(circleRect);


	wxBitmap maskBitmap(sourceImage.GetSize(), 1);
	wxBitmap resultBitmap(sourceImage);


	// Draw the mask to mask out the part of the resulting image
	// outside the circle.    
	wxMemoryDC       memoryDC(maskBitmap);
	wxDCBrushChanger brushChanger(memoryDC, *wxWHITE_BRUSH);
	wxDCPenChanger   penChanger(memoryDC, *wxWHITE_PEN);

	// black pixels will be fully transparent
	memoryDC.SetBackground(*wxBLACK_BRUSH);
	memoryDC.Clear();
	memoryDC.SetBackground(wxNullBrush);

	// white pixels inside the circle will remain unchanged
	memoryDC.DrawCircle(circleCenter, circleRadius);
	memoryDC.SelectObject(wxNullBitmap);

	resultBitmap.SetMask(new wxMask(maskBitmap));
	resultImage = resultBitmap.GetSubBitmap(resultRect).ConvertToImage();
	

	return true;
}


wxBitmap AppList::PaintProfil(const wxDataViewItem& profil, const int& background)
{

	model = (UserModelData*)(this->GetItemData(profil));
	image.LoadFile(model->GetPath(), wxBITMAP_TYPE_JPEG);
	image.Rescale(58, 58, wxIMAGE_QUALITY_HIGH);
	
	
	wxBitmap Photo(image);
	wxMemoryDC changer(Photo);

	
	if(UserModelData::STATUS_ACTIV == background)
		changer.DrawBitmap(FrameOnActiveBack, wxPoint(0, 0));

	else
		changer.DrawBitmap(FrameOnDisActiveBack, wxPoint(0, 0));
	
	if (model->GetStatus() == UserModelData::STATUS_ACTIV)
		changer.DrawBitmap(CircleOnActive, wxPoint(40, 40));

	return Photo;

}

bool AppList::CreateAccount(UserModelData* usermodel) //INPUT -AND OUTPUT FULL DATE INFO OF USER
{

	//#Getting information from database
	Poco::Tuple<int, std::string, std::string, std::string, std::string> Data1 = connection->SelectOne(usermodel->GetID());
	usermodel->SetName(Data1.get<1>());
	usermodel->SetSurname(Data1.get<2>());
	usermodel->SetIP(Data1.get<3>());
	usermodel->SetCity(Data1.get<4>());

	data.clear();
	image.LoadFile(usermodel->GetPath(), wxBITMAP_TYPE_JPEG);
	image.Rescale(58, 58);
	wxBitmap Photo(image);
	wxMemoryDC changer(Photo);
	changer.DrawBitmap(FrameOnDisActiveBack, wxPoint(0, 0));
	changer.DrawBitmap(CircleOnActive, wxPoint(40, 40));
	wxString FinalColumnname("<span color=\"#000000\" size=\"100\">");
	FinalColumnname.Append(usermodel->GetName());
	FinalColumnname.Append(" ");
	FinalColumnname.Append(usermodel->GetSurname());
	FinalColumnname.Append("</span> ");
	data.push_back(wxVariant(Photo));
	data.push_back(wxVariant(FinalColumnname.c_str()));
	AppendItem(data);
	wxDataViewItem item = this->RowToItem(Row_counts);
	this->SetItemData(item, (wxUIntPtr)usermodel);
	++Row_counts;
	
	return true;
}

AppList::~AppList()
{
	delete connection;
}