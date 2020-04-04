/////////////////////////////////////////////////////////////////////////////
// Name:        MainWindow.cpp
// Author:      Mateusz Kosmala <mateuszkosmala1@gmail.com>
// Created:     2012-03-03
// Copyright:   (c) 2020 by Mateusz Kosmala
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/richtext/richtextctrl.h>
#include <wx/panel.h>
#include <wx/dataview.h>
#include <wx/treectrl.h>
#include <UserImage.h>
#include <MainWindow.h>
#include <Utils.h>
#include <MenuButton.h>
#include <SearchWindow.h>
#include <ColumnRender.h>
#include <AppList.h>
#include<UserModelData.h>
#include<MainApp.h>
#include<MainXmlDocument.h>
#include <AddUserButton.h>
#include <wx/toolbar.h>
#include <wx/statbmp.h>
#include<ScrolledPanel.h>
#include<MainSearchCtrl.h>
#include <thread> 

enum
{
	ID_ON_START = wxID_HIGHEST + 1,
	ID_MENU,
	ID_SEARCH,
	ID_TREE,
	ID_USERBUTTON,
	ID_TOOLBAR,
	ID_TOOLBAR_STATUS,
	ID_TOOLBAR_PREFE,
	ID_TOOLBAR_SETTINGS,
	ID_TOOLBAR_HELP,
	ID_TOOLBAR_LOGOUT,
	ID_VIDEO,
	ID_SETTINGS,
	ID_ATTACHMENT,
	ID_MAIN_TEXT,
	ID_SEND,
	ID_LIST,
	NUMBER_UPDATE_ID,
	ID_TEST_TIMER,
	ID_PANEL1,
	ID_PANEL2
};

//---------------------------------------------------------------------------
// EVENT TABLE
//---------------------------------------------------------------------------

BEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_MENUBTN_ACTIVATED(ID_MENU, MainWindow::OnMenuClick)
EVT_ADDUSRBTN_ACTIVATED(ID_VIDEO, MainWindow::OnVideoClick)
EVT_ADDUSRBTN_ACTIVATED(ID_SETTINGS, MainWindow::OnSettingsClick)
EVT_ADDUSRBTN_ACTIVATED(ID_ATTACHMENT, MainWindow::OnAttachClick)
EVT_ADDUSRBTN_ACTIVATED(ID_SEND, MainWindow::OnSendClick)
EVT_COMMAND(NUMBER_UPDATE_ID, wxEVT_COMMAND_TEXT_UPDATED, MainWindow::OnUpdate)
EVT_DATAVIEW_SELECTION_CHANGED(ID_LIST, MainWindow::SelectionChanged)
EVT_TIMER(ID_TEST_TIMER, MainWindow::OnTimer)
EVT_IDLE(MainWindow::Testing)
END_EVENT_TABLE()



MainWindow::MainWindow(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
	: wxFrame(parent, id, title, pos, size, style) , m_timer(this, ID_TEST_TIMER)
{

	//Data Structure
	messagestructure = new MainXmlDocument();
	usersstructure = new MainXmlDocument();
	usersstructure->Load(wxString("C:\\Users\\metju\\Desktop\\Programming\\ConsoleApplications\\SEth\\SEth\\docs\\UserStructureData.xml"));
	usersstructure->SetRoot(new wxXmlNode(wxXML_ELEMENT_NODE, wxString("SEthProject")));

	//Icon
	wxIcon icon(wxGetAppFile(wxString("menu.png")), wxBITMAP_TYPE_PNG);
	this->SetIcon(icon);

	//Sizers
	MainSizer = new wxBoxSizer(wxVERTICAL);
	SetSizer(MainSizer);
	wxPanel* MainPanel = new wxPanel(this, ID_PANEL1);
	MainPanel->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
	MainSizer->Add(MainPanel, 1, wxEXPAND);
	wxBoxSizer* MainSizer1 = new wxBoxSizer(wxVERTICAL);
	MainPanel->SetSizer(MainSizer1);
	MainHorizontalSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* RightHorizontalSizer = new wxBoxSizer(wxVERTICAL);
	wxPanel* RightPanel = new wxPanel(MainPanel, ID_PANEL2);

	RightPanel->SetBackgroundColour(*wxWHITE);
	RightHorizontalSizer->Add(RightPanel, 1, wxEXPAND);
	wxBoxSizer* RightTopSizer = new wxBoxSizer(wxVERTICAL);
	RightPanel->SetSizer(RightTopSizer);

	/////////////////////////////////////////////////////////
	//Second part of MainWindow
	/////////////////////////////////////////////////////////

	wxBoxSizer* TopHSizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* DownHSizer = new wxBoxSizer(wxHORIZONTAL);

	//MainScrolledPanel
	myscrolledpanel = new ScrolledPanel(RightPanel);

	//StaticBitmap
	wxBitmap nullbitmap;
	userphotos = new wxStaticBitmap(RightPanel, wxID_ANY, nullbitmap, wxDefaultPosition, wxDefaultSize);
	TopHSizer->Add(userphotos, 0, wxEXPAND | wxALL, 3);

	//User Title
	usertext = new wxStaticText(RightPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE);
	TopHSizer->Add(usertext, 6, wxALIGN_CENTRE_VERTICAL | wxALL, 3);
	usertext->SetForegroundColour(wxColour(*wxBLACK));
	wxFont font1(15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_EXTRAHEAVY, false);
	usertext->SetFont(font1);

	//VideoIcon
	wxBitmap MenuButtonNormal;
	MenuButtonNormal.LoadFile(wxString("C:\\Users\\metju\\Desktop\\Programming\\ConsoleApplications\\SEth\\SEth\\extern_files\\Icons\\film.png"), wxBITMAP_TYPE_PNG);
	wxBitmap MenuButtonHover;
	MenuButtonHover.LoadFile(wxString("C:\\Users\\metju\\Desktop\\Programming\\ConsoleApplications\\SEth\\SEth\\extern_files\\Icons\\film.png"), wxBITMAP_TYPE_PNG);
	wxImage VideoIcon = MenuButtonHover.ConvertToImage();
	VideoIcon.Rescale(33, 33);
	wxBitmap VideoIconUp(VideoIcon);
	AddUserButton* Videobutton = new AddUserButton(RightPanel, ID_VIDEO, wxDefaultPosition, MenuButtonNormal, VideoIconUp, wxNullBitmap, 1);
	Videobutton->SetBackgroundColour(*wxWHITE);
	TopHSizer->Add(Videobutton, 0, wxEXPAND | wxTOP | wxBOTTOM || wxRIGHT, 4);

	//Embedded Settings
	MenuButtonNormal.LoadFile(wxString("C:\\Users\\metju\\Desktop\\Programming\\ConsoleApplications\\SEth\\SEth\\extern_files\\Icons\\menu1.png"), wxBITMAP_TYPE_PNG);
	MenuButtonHover.LoadFile(wxString("C:\\Users\\metju\\Desktop\\Programming\\ConsoleApplications\\SEth\\SEth\\extern_files\\Icons\\menu1.png"), wxBITMAP_TYPE_PNG);
	wxImage MenuIcon = MenuButtonHover.ConvertToImage();
	MenuIcon.Rescale(32, 32);
	wxBitmap MenuiconUp(MenuIcon);
	AddUserButton* Menubutton = new AddUserButton(RightPanel, ID_SETTINGS, wxDefaultPosition, MenuButtonNormal, MenuiconUp, wxNullBitmap, 1);
	Menubutton->SetBackgroundColour(*wxWHITE);
	TopHSizer->Add(Menubutton, 0, wxEXPAND | wxTOP | wxBOTTOM | wxRIGHT, 4);

	//Attachment Icon
	MenuButtonNormal.LoadFile(wxString("C:\\Users\\metju\\Desktop\\Programming\\ConsoleApplications\\SEth\\SEth\\extern_files\\Icons\\paperclip.png"), wxBITMAP_TYPE_PNG);
	MenuButtonHover.LoadFile(wxString("C:\\Users\\metju\\Desktop\\Programming\\ConsoleApplications\\SEth\\SEth\\extern_files\\Icons\\paperclip.png"), wxBITMAP_TYPE_PNG);
	wxImage AttachIcon = MenuButtonHover.ConvertToImage();
	AttachIcon.Rescale(32, 32);
	wxBitmap AttachIconUp(AttachIcon);
	AddUserButton* clip = new AddUserButton(RightPanel, ID_ATTACHMENT, wxDefaultPosition, MenuButtonNormal, AttachIconUp, wxNullBitmap, 1);
	clip->SetBackgroundColour(*wxWHITE);
	DownHSizer->Add(clip, 0, wxEXPAND);

	//Main Write Control

	searchmain = new MainSearchCtrl(RightPanel, ID_MAIN_TEXT, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxTE_MULTILINE | wxWANTS_CHARS | wxTE_CHARWRAP | wxTE_PROCESS_ENTER);
	searchmain->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
	searchmain->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_MEDIUM, false));
	wxBitmap searchbitmap(wxString("C:\\Users\\metju\\Desktop\\Programming\\ConsoleApplications\\SEth\\SEth\\extern_files\\Icons\\emoji.png"), wxBITMAP_TYPE_PNG);
	searchmain->SetSearchBitmap(searchbitmap);
	searchmain->SetDescriptiveText(wxString("Napisz Wiadomość..."));
	DownHSizer->Add(searchmain, 7, wxALIGN_CENTER_VERTICAL);

	//Send Icon
	MenuButtonNormal.LoadFile(wxString("C:\\Users\\metju\\Desktop\\Programming\\ConsoleApplications\\SEth\\SEth\\extern_files\\Icons\\send.png"), wxBITMAP_TYPE_PNG);
	MenuButtonHover.LoadFile(wxString("C:\\Users\\metju\\Desktop\\Programming\\ConsoleApplications\\SEth\\SEth\\extern_files\\Icons\\send.png"), wxBITMAP_TYPE_PNG);
	wxImage SendIcon = MenuButtonHover.ConvertToImage();
	SendIcon.Rescale(24, 24);
	wxBitmap SendIconUp(SendIcon);
	AddUserButton* send = new AddUserButton(RightPanel, ID_SEND, wxDefaultPosition, MenuButtonNormal, SendIconUp, wxNullBitmap, 1);
	send->SetBackgroundColour(*wxWHITE);
	DownHSizer->Add(send, 0, wxEXPAND | wxTOP, 6);

	//Sizer Part #2
	RightTopSizer->Add(TopHSizer, 1, wxEXPAND);

	RightTopSizer->Add(myscrolledpanel, 10, wxEXPAND); ////////////////!!!!!!!!!!!!!!!11

	RightTopSizer->Add(DownHSizer, 0, wxEXPAND);
	wxBoxSizer* LeftHorizontalSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* TopSizer = new wxBoxSizer(wxHORIZONTAL);
	LeftHorizontalSizer->Add(TopSizer, 1, wxEXPAND);
	MainHorizontalSizer->Add(LeftHorizontalSizer, 3.0, wxEXPAND);
	MainHorizontalSizer->Add(RightHorizontalSizer, 6.99, wxEXPAND);
	MainSizer1->Add(MainHorizontalSizer, 1, wxEXPAND);

	//UserImage
	MainImage = new UserImage(MainPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, UserImage::ID_ON_ACTIVE);
	TopSizer->Add(MainImage, 0, wxEXPAND | wxALL, 4);

	//App Title
	statictext = new wxStaticText(MainPanel, wxID_ANY, wxString("SEth Messenger"), wxDefaultPosition, wxDefaultSize);
	TopSizer->Add(statictext, 1, wxALIGN_CENTRE_VERTICAL, 3);
	statictext->SetForegroundColour(wxColour(*wxBLACK));
	wxFont font(13, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);
	statictext->SetFont(font);

	//Add User Button
	MenuButtonNormal.LoadFile(wxString("C:\\Users\\metju\\Desktop\\Programming\\ConsoleApplications\\SEth\\SEth\\extern_files\\Icons\\add.png"), wxBITMAP_TYPE_PNG);
	MenuButtonHover.LoadFile(wxString("C:\\Users\\metju\\Desktop\\Programming\\ConsoleApplications\\SEth\\SEth\\extern_files\\Icons\\add.png"), wxBITMAP_TYPE_PNG);
	wxImage ImageButtonHover11 = MenuButtonHover.ConvertToImage();
	ImageButtonHover11.Rescale(33, 33);
	wxBitmap MenuButtonHoverTarget11(ImageButtonHover11);
	AddUserButton* userbutton = new AddUserButton(MainPanel, ID_USERBUTTON, wxDefaultPosition, MenuButtonNormal, MenuButtonHoverTarget11, wxNullBitmap);
	TopSizer->Add(userbutton, 0, wxEXPAND | wxTOP | wxBOTTOM, 4);

	//MenuButton
	MenuButtonNormal.LoadFile(wxString("C:\\Users\\metju\\Desktop\\Programming\\ConsoleApplications\\SEth\\SEth\\extern_files\\Icons\\list.png"), wxBITMAP_TYPE_PNG);
	wxImage ImageButtonNormal = MenuButtonNormal.ConvertToImage();
	ImageButtonNormal.Rescale(28, 28);
	wxBitmap MenuButtonNormalTarget(ImageButtonNormal);
	MenuButtonHover.LoadFile(wxString("C:\\Users\\metju\\Desktop\\Programming\\ConsoleApplications\\SEth\\SEth\\extern_files\\Icons\\list.png"), wxBITMAP_TYPE_PNG);
	wxImage MenuButton1 = MenuButtonHover.ConvertToImage();
	MenuButton1.Rescale(29, 29);
	wxBitmap MenuButtonUp(MenuButton1);
	MenuButton* MenuButtonUser = new MenuButton(MainPanel, ID_MENU, wxDefaultPosition, MenuButtonNormalTarget, MenuButtonUp, wxNullBitmap);
	TopSizer->Add(MenuButtonUser, 0, wxEXPAND | wxTOP | wxBOTTOM, 4);

	// Search
	SearchWindow* Search = new SearchWindow(MainPanel, ID_SEARCH, wxEmptyString, wxDefaultPosition, wxSize(23, 23), wxBORDER_NONE);
	LeftHorizontalSizer->Add(Search, 0.99, wxEXPAND | wxALL, 10);
	Search->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
	Search->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_ITALIC,
		wxFONTWEIGHT_LIGHT, false));
	Search->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DDKSHADOW));
	Search->SetDescriptiveText(wxString("Searching"));
	Search->SetBackgroundColour(wxColour(220, 220, 220));

	wxBoxSizer* ContactSizer = new wxBoxSizer(wxHORIZONTAL);
	LeftHorizontalSizer->Add(ContactSizer, 9, wxEXPAND);

	//Contact List
	contactlist = new AppList(MainPanel, ID_LIST, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE | wxDV_NO_HEADER);
	contactlist->ShowScrollbars(wxSHOW_SB_NEVER, wxSHOW_SB_NEVER); //Never ShowScrollBar
	ContactSizer->Add(contactlist, 3, wxEXPAND | wxALL, 5);
	toolbar = new wxToolBar(MainPanel, ID_TOOLBAR, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL | wxTB_TEXT | wxTB_FLAT | wxTB_NODIVIDER | wxBORDER_SIMPLE);
	toolbar->SetMargins(10, 10);
	toolbar->SetToolSeparation(10);
	toolbar->SetToolBitmapSize(wxSize(32, 32));
	wxBitmap ToolBarPhoto;
	ToolBarPhoto.LoadFile(wxString("C:\\Users\\metju\\Desktop\\Programming\\ConsoleApplications\\SEth\\SEth\\extern_files\\Icons\\hide.png"), wxBITMAP_TYPE_PNG);
	toolbar->AddTool(ID_TOOLBAR_STATUS, wxString("Status Aktywności"), ToolBarPhoto, wxString("Status Aktywności"));
	ToolBarPhoto.LoadFile(wxString("C:\\Users\\metju\\Desktop\\Programming\\ConsoleApplications\\SEth\\SEth\\extern_files\\Icons\\user.png"), wxBITMAP_TYPE_PNG);
	toolbar->AddTool(ID_TOOLBAR_PREFE, wxString("Preferencje"), ToolBarPhoto, wxString("Preferencje"));
	ToolBarPhoto.LoadFile(wxString("C:\\Users\\metju\\Desktop\\Programming\\ConsoleApplications\\SEth\\SEth\\extern_files\\Icons\\gear.png"), wxBITMAP_TYPE_PNG);
	toolbar->AddTool(ID_TOOLBAR_SETTINGS, wxString("Ustawienia"), ToolBarPhoto, wxString("Ustawienia"));
	ToolBarPhoto.LoadFile(wxString("C:\\Users\\metju\\Desktop\\Programming\\ConsoleApplications\\SEth\\SEth\\extern_files\\Icons\\question.png"), wxBITMAP_TYPE_PNG);
	toolbar->AddTool(ID_TOOLBAR_HELP, wxString("Pomoc"), ToolBarPhoto, wxString("Pomoc"));
	ToolBarPhoto.LoadFile(wxString("C:\\Users\\metju\\Desktop\\Programming\\ConsoleApplications\\SEth\\SEth\\extern_files\\Icons\\log-out.png"), wxBITMAP_TYPE_PNG);
	toolbar->AddTool(ID_TOOLBAR_LOGOUT, wxString("Wyloguj"), ToolBarPhoto, wxString("Wyloguj"));
	toolbar_status = 0;
	toolbar->InsertStretchableSpace(0);
	toolbar->InsertStretchableSpace(6);
	MainSizer1->Add(toolbar, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
	toolbar->Realize();
	toolbar->Hide();
	toolbar->SetBackgroundColour(wxColor(210, 210, 210));
	toolbar->SetForegroundColour(*wxWHITE);

	this->Initialization(); //Initialization of XML Structure

	/////////////////////////////////////////////////////////
	//Second part of MainWindow #2
	/////////////////////////////////////////////////////////

	UserModelData* namevalue = nullptr;
	namevalue = (UserModelData*)(contactlist->GetItemData(contactlist->RowToItem(0)));
	usertext->SetLabel(namevalue->GetName() + wxT(" ") + namevalue->GetSurname());
	userphotos->SetBitmap(contactlist->PaintProfil(contactlist->RowToItem(0), 3));

	//---------------------------------------------------------------------------------------------------------------------------------------
	//Rest
	//ADD NEW USER ACCOUNT AFTER INITIALIZATION
	//UserModelData* userr = new UserModelData(false,12345,wxString("Finaffl"),wxString("Exxam"),12700,false,wxString("C:\\Users\\metju\\Desktop\\Programming\\ConsoleApplications\\SEth\\SEth\\extern_files\\Icons\\123.jpg"),
	//wxString("Oleśnica"),UserModelData::STATUS_ACTIV);
	//this->AddAccount(new UserModelData(false, 12345, wxString("Finaffl"), wxString("Exxam"), 12700, false, wxString("C:\\Users\\metju\\Desktop\\Programming\\ConsoleApplications\\SEth\\SEth\\extern_files\\Icons\\123.jpg"),
	//	wxString("Oleśnica"),UserModelData::STATUS_ACTIV));
	//
	//MainApp &reference = wxGetApp(); Reference to get MainApp
	//---------------------------------------------------------------------------------------------------------------------------------------
	//myscrolledpanel->SetVirtualSize(-1, 2000);

	myscrolledpanel->ID = namevalue->GetID();
	myscrolledpanel->Scroll(400, 100000);

	CenterOnScreen();
	contactlist->actual_item = contactlist->RowToItem(0);

	//Running Server
	TCPServerParams* serverparams = new TCPServerParams();
	//Max count of queued messages on the server
	serverparams->setMaxQueued(30);
	try {
		SocketAddress adress(Poco::Net::AddressFamily::IPv4, "127.0.0.1", "7670");
		ServerSocket socketserver(adress);
		srv = new TCPServer(new TCPServerConnectionFactoryImpl<SessionTCP>(), socketserver, serverparams);
		RejectFilter* reject = new RejectFilter();

		srv->setConnectionFilter(reject);
		srv->start();

		//std::cout << "Server Running..." << std::endl;
	}
	catch (Poco::Exception& exc)
	{
		//std::cerr << "Błąd: " << exc.displayText() << std::endl;
		wxMessageBox(exc.displayText());
	}
	ss = NULL;

	//Setting Logging
	FILE* file;
	file = fopen("C:\\Users\\metju\\Desktop\\Programming\\ConsoleApplications\\SEth\\SEth\\test_and_log\\log.txt", "w");
	logger = new wxLogStderr(file);
	logger = wxLog::SetActiveTarget(logger);
	wxLogMessage(wxT("creating config_file"));

	//Timer
	m_timer.Start(1000);

}


void MainWindow::Testing(wxIdleEvent& event)
{
	if (this->resize != 0)
	{
	
		UserModelData* namevalue = nullptr;
		myscrolledpanel->Freeze();
		myscrolledpanel->HEIGHT_POINTSCROLL = 2000;
		myscrolledpanel->Clear();//Clear Background
		myscrolledpanel->ShowScrollbars(wxSHOW_SB_NEVER, wxSHOW_SB_NEVER);
		namevalue = (UserModelData*)(contactlist->GetItemData(contactlist->actual_item));
		myscrolledpanel->HEIGHT_POINT = 2000;
		myscrolledpanel->SetVirtualSize(-1, 2000);
		myscrolledpanel->ID = namevalue->GetID();
		myscrolledpanel->AddTextToModel(wxEmptyString, namevalue->GetID());
		myscrolledpanel->Scroll(400, 100000);
		myscrolledpanel->Layout();
		myscrolledpanel->ShowScrollbars(wxSHOW_SB_NEVER, wxSHOW_SB_ALWAYS);
		myscrolledpanel->Thaw();
		this->resize = 0;
	}
	event.Skip();
}

void MainWindow::OnSize(wxSizeEvent& event)
{
	++resize;
	event.Skip();
}

void MainWindow::OnUpdate(wxCommandEvent& evt)
{
	wxBitmap drawBitmap = myscrolledpanel->AddTextAndBitmap(evt.GetString(), ScrolledPanel::RECEIVE_MESSAGE);
	myscrolledpanel->bitmaps.push_back(new wxStaticBitmap(myscrolledpanel, wxID_ANY, drawBitmap, wxPoint(0, evt.GetInt() - 10), wxDefaultSize)); //Need to pass to main thread
}

void MainWindow::SelectionChanged(wxDataViewEvent& event)
{
	UserModelData* namevalue = nullptr;
	namevalue = (UserModelData*)(contactlist->GetItemData(event.GetItem()));

	usertext->Freeze();
	userphotos->Freeze();
	usertext->SetLabel(namevalue->GetName() + wxT(" ") + namevalue->GetSurname());
	usertext->Thaw();

	userphotos->SetBitmap(contactlist->PaintProfil((contactlist->actual_item), 3));
	userphotos->Thaw();

	//Add Bitmap with text to Interface Model
	myscrolledpanel->Freeze();
	myscrolledpanel->HEIGHT_POINTSCROLL = 2000;
	myscrolledpanel->Clear();//Clear Background
	myscrolledpanel->ShowScrollbars(wxSHOW_SB_NEVER, wxSHOW_SB_NEVER);
	namevalue = (UserModelData*)(contactlist->GetItemData(contactlist->actual_item));
	myscrolledpanel->HEIGHT_POINT = 2000;
	myscrolledpanel->SetVirtualSize(-1, 2000);
	myscrolledpanel->ID = namevalue->GetID();
	myscrolledpanel->AddTextToModel(wxEmptyString, namevalue->GetID());
	myscrolledpanel->Scroll(400, 100000);
	myscrolledpanel->Layout();
	myscrolledpanel->ShowScrollbars(wxSHOW_SB_NEVER, wxSHOW_SB_ALWAYS);
	myscrolledpanel->Thaw();

	//Deleting socket
	if (ss != NULL)
	{
		//
	}

	
	//Connect to given user
	try {
		wxString address = namevalue->GetIP();
		std::string address1 = address.char_str();
		SocketAddress sa(address1, "7675"); //for testing should be changed on 7671 as default

		ss = new StreamSocket(sa);
		int n = SessionTCP::ID_MESSAGE;
		ss->sendBytes(&n, sizeof(int));

		wxLogMessage("Complete in connection");
	}
	catch (Poco::Exception& exc)
	{
		wxLogMessage("Error in connection: ");
		wxString text;
		text << exc.displayText();
		wxLogMessage(text);
	}
	
}

bool  MainWindow::Initialization(void)
{
	MainXmlDocument* userstructure = new MainXmlDocument();
	usersstructure->Load(wxString("C:\\Users\\metju\\Desktop\\Programming\\ConsoleApplications\\SEth\\SEth\\docs\\UserStructureData.xml"));
	UserModelData* workmodel = new UserModelData(NULL);
	wxXmlNode* root = usersstructure->GetRoot();
	wxXmlNode* node = root->GetChildren();
	wxXmlNode* subnode;
	wxXmlNode* subcontentnode;

	while (node)
	{
		wxString variable;
		wxString innervariable;
		long value;
		variable = node->GetAttribute(wxString("ID"));
		variable.ToLong(&value);
		workmodel->SetID(value);

		subnode = node->GetChildren();

		while (subnode)
		{
			variable = subnode->GetName();
			subcontentnode = subnode->GetChildren();
			innervariable = subcontentnode->GetContent();

			if (variable == "Photo_Path")
			{
				workmodel->SetPath(innervariable);
			}

			else if (variable == "Favorite")
			{
				innervariable.ToLong(&value);
				bool b = (value != 0);
				workmodel->SetFavourite(b);
			}

			else if (variable == "Surname")
			{
				workmodel->SetSurname(innervariable);
			}

			else if (variable == "Name")
			{
				workmodel->SetName(innervariable);
			}
			else if (variable == "IP_ADRESS")
			{
				workmodel->SetIP(innervariable);
			}

			subnode = subnode->GetNext();
		}

		workmodel->SetStatus(UserModelData::STATUS_ACTIV); // SHOULD BE CHANGED IN-RUN!
		contactlist->CreateAccount(workmodel);

		node = node->GetNext();
		if (node)
			workmodel = new UserModelData(NULL);
	}

	delete userstructure;
	return true;
}

UserModelData* MainWindow::GetRestInfoDateBase(UserModelData* usermodel) //USING POCO AND DATABASE
{
	return nullptr;
}

UserModelData* MainWindow::GetRestInfoSettings(UserModelData* usermodel) //USING POCO AND DATABASE
{
	return nullptr;
}

void MainWindow::OnTimer(wxTimerEvent& event)
{
	//
}

MainXmlDocument* MainWindow::ReturnUS(void)
{
	return this->usersstructure;
}

bool MainWindow::AddAccount(UserModelData* usermodelid)
{
	contactlist->CreateAccount(usermodelid);
	return true;
}

MainWindow::~MainWindow()
{
	//Stop Server running
	srv->stop();

	wxXmlNode* root = usersstructure->GetRoot();
	wxXmlNode* node = root->GetChildren();
	autoremove(node);
	int rows = contactlist->Row_counts;

	//Saving User Structure at the end of Program
	for (rows; rows > 0; --rows)
	{
		usersstructure->AddUser((UserModelData*)(contactlist->GetItemData(contactlist->RowToItem(rows - 1))));
	}

	usersstructure->Save(wxString("C:\\Users\\metju\\Desktop\\Programming\\ConsoleApplications\\SEth\\SEth\\docs\\UserStructureData.xml"));
	myscrolledpanel->Clear(); //Is it necessery?
}

void MainWindow::autoremove(wxXmlNode* root) //TERRIBLE!
{
	if (root == NULL)
		return;

	wxXmlNode* rootTrue = usersstructure->GetRoot();
	wxXmlNode* node = root;
	wxXmlNode* neww;

	if (node)
	{
		neww = node->GetNext();
		autoremove(neww);
		rootTrue->RemoveChild(node);
	}

	return;
}

void MainWindow::OnMenuClick(MenuButtonEvent& event)
{
	if (!(this->toolbar_status))
	{
		toolbar->Show();
		toolbar->Realize();
		this->toolbar_status = 1;
		this->Layout();
		this->SetSize(this->GetSize());
	}

	else
	{
		toolbar->Hide();
		this->toolbar_status = 0;
		this->Layout();
		this->SetSize(this->GetSize());
	}

	myscrolledpanel->Scroll(400, 100000);
}

void MainWindow::OnAttachClick(AddUserButtonEvent& event)
{
	//wxMessageBox(wxString("Working!"));
}

void MainWindow::OnSettingsClick(AddUserButtonEvent& event)
{
	//wxMessageBox(wxString("Working!"));
}

void MainWindow::OnSendClick(AddUserButtonEvent& event)
{
	wxString Text_Value = searchmain->GetValue();
	searchmain->Clear();

	if (!(Text_Value.IsEmpty()))
	{
		UserModelData* namevalue = nullptr;
		namevalue = (UserModelData*)(contactlist->GetItemData(contactlist->actual_item));
		wxString workingstring;
		wxXmlNode* root = myscrolledpanel->doc.GetRoot();
		wxXmlNode* children = root->GetChildren();

		if (children == NULL) //NO MESSAGE ANYWAY!
		{
			wxXmlNode* user = new wxXmlNode(root, wxXML_ELEMENT_NODE, wxString("User"));
			workingstring << namevalue->GetID();
			user->AddAttribute(wxString("ID"), workingstring);
			workingstring.clear();
			wxXmlNode* message = new wxXmlNode(user, wxXML_ELEMENT_NODE, wxString("DATA"));
			wxDateTime time = wxDateTime::Now();
			message->AddAttribute(wxString("S"), time.FormatISOCombined());
			message->AddChild(new wxXmlNode(message, wxXML_TEXT_NODE, wxEmptyString, Text_Value));
		}

		bool FOUND = 0;
		workingstring.clear();
		workingstring << namevalue->GetID();
		wxXmlNode* sub = children;
		wxXmlNode* found;
		while (sub)
		{
			if (sub->GetAttribute(wxString("ID")) == workingstring)
			{
				FOUND = 1;
				found = sub;
			}

			sub = sub->GetNext();
		}

		if (FOUND == 1)
		{
			children = found;
			wxXmlNode* subchildren = children->GetChildren();

			if (!(subchildren == NULL)) //EXISTING MESSAGE
			{
				wxXmlNode* insert = subchildren;
				wxXmlNode* message = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, wxString("DATA"));
				wxDateTime time = wxDateTime::Now();
				message->AddAttribute(wxString("S"), time.FormatISOCombined());
				message->AddChild(new wxXmlNode(message, wxXML_TEXT_NODE, wxEmptyString, Text_Value));
				children->InsertChild(message, insert);
			}
		}
		else
		{
			wxXmlNode* user = new wxXmlNode(root, wxXML_ELEMENT_NODE, wxString("User"));
			workingstring.clear();
			workingstring << namevalue->GetID();
			user->AddAttribute(wxString("ID"), workingstring);
			workingstring.clear();

			wxXmlNode* message = new wxXmlNode(user, wxXML_ELEMENT_NODE, wxString("DATA"));
			wxDateTime time = wxDateTime::Now();
			message->AddAttribute(wxString("S"), time.FormatISOCombined());
			message->AddChild(new wxXmlNode(message, wxXML_TEXT_NODE, wxEmptyString, Text_Value));
		}

		myscrolledpanel->Freeze();
		myscrolledpanel->Scroll(400, 100000);
		myscrolledpanel->AddAllToControl(Text_Value, ScrolledPanel::USER_TEXT);
		myscrolledpanel->Scroll(400, 100000);
		myscrolledpanel->Thaw();
		myscrolledpanel->doc.Save(wxString("C:\\Users\\metju\\Desktop\\Programming\\ConsoleApplications\\SEth\\SEth\\docs\\MessagesStructure.xml"));

		int size;
		size = Text_Value.size();
		try {
			ss->sendBytes(&size, sizeof(int));
			ss->sendBytes(Text_Value.data(), (int)Text_Value.size());
		}

		catch (Poco::Exception& exc)
		{
			wxString text;
			text << exc.displayText();
			wxMessageBox(text);
		}
	}
}

bool  MainWindow::OnReceive(std::string text, std::string IP)
{
	wxString Text_Value = text;

	if (!(Text_Value.IsEmpty()))
	{
		UserModelData* namevalue = nullptr;
		namevalue = (UserModelData*)(contactlist->GetItemData(contactlist->actual_item));

		wxString workingstring;
		wxXmlNode* root = myscrolledpanel->doc.GetRoot();
		wxXmlNode* children = root->GetChildren();

		if (children == NULL) //NO MESSAGE ANYWAY!
		{
			wxXmlNode* user = new wxXmlNode(root, wxXML_ELEMENT_NODE, wxString("User"));
			workingstring << namevalue->GetID();
			user->AddAttribute(wxString("ID"), workingstring);
			workingstring.clear();
			wxXmlNode* message = new wxXmlNode(user, wxXML_ELEMENT_NODE, wxString("DATA"));
			wxDateTime time = wxDateTime::Now();
			message->AddAttribute(wxString("S"), time.FormatISOCombined());
			message->AddChild(new wxXmlNode(message, wxXML_TEXT_NODE, wxEmptyString, Text_Value));
		}

		bool FOUND = 0;
		workingstring.clear();

		workingstring << contactlist->connection->GetIDFromIP(IP);
		wxXmlNode* sub = children;
		wxXmlNode* found;
		while (sub)
		{
			if (sub->GetAttribute(wxString("ID")) == workingstring)
			{
				FOUND = 1;
				found = sub;
			}

			sub = sub->GetNext();
		}

		if (FOUND == 1)
		{
			children = found;
			wxXmlNode* subchildren = children->GetChildren();

			if (!(subchildren == NULL)) //EXISTING MESSAGE
			{
				wxXmlNode* insert = subchildren;
				wxXmlNode* message = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, wxString("DATA"));
				wxDateTime time = wxDateTime::Now();
				message->AddAttribute(wxString("R"), time.FormatISOCombined());
				message->AddChild(new wxXmlNode(message, wxXML_TEXT_NODE, wxEmptyString, Text_Value));
				children->InsertChild(message, insert);
			}
		}
		else
		{
			wxXmlNode* user = new wxXmlNode(root, wxXML_ELEMENT_NODE, wxString("User"));
			workingstring.clear();
			workingstring << namevalue->GetID();
			user->AddAttribute(wxString("ID"), workingstring);
			workingstring.clear();

			wxXmlNode* message = new wxXmlNode(user, wxXML_ELEMENT_NODE, wxString("DATA"));
			wxDateTime time = wxDateTime::Now();
			message->AddAttribute(wxString("R"), time.FormatISOCombined());
			message->AddChild(new wxXmlNode(message, wxXML_TEXT_NODE, wxEmptyString, Text_Value));
		}

		myscrolledpanel->Freeze();
		myscrolledpanel->Scroll(400, 100000);

		if (namevalue->GetIP() == IP)
			myscrolledpanel->AddAllToControl(text, ScrolledPanel::RECEIVE_MESSAGE);

		myscrolledpanel->Scroll(400, 100000);
		myscrolledpanel->Thaw();
		myscrolledpanel->doc.Save(wxString("C:\\Users\\metju\\Desktop\\Programming\\ConsoleApplications\\SEth\\SEth\\docs\\MessagesStructure.xml"));
	}

	return true;
}

void ShowImage(void)
{
	using namespace std;
	using namespace cv;
	using namespace Poco::Net;
	VideoCapture cap(0);
	Mat frame;

	try {

		SocketAddress sa("127.0.0.1", "7670");
		StreamSocket ss(sa);
		SocketStream istr(ss);
		VideoCapture cap(0);
		Mat frame;    //Mat is 2-dimensional array.

		int bytes = 3;
		ss.sendBytes(&bytes, sizeof(int));

		bool bSuccess = cap.read(frame); //Cacth frame

		while (true)
		{
			if (!cap.read(frame)) 
			{
				break;
			}

			int imgSize = frame.total() * frame.elemSize(); //Total size to send in bytes = .total()-pixel in image or size of array * size of each element in matrix 

			ss.sendBytes(frame.data, imgSize, 0); //return pointer to uchar data
		}

	}


	catch (Poco::Exception& exc)
	{
		wxString text;
		text << exc.displayText();
		wxMessageBox(text);
	}

}

void MainWindow::OnVideoClick(AddUserButtonEvent& event)
{
	
	std::thread thread(ShowImage);
	thread.detach();

}