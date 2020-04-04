#include "MainXmlDocument.h"
#include <wx/log.h>


bool MainXmlDocument::AddUser(UserModelData* usermodel) //Used At the end of program
{

	wxXmlNode* root = this->GetRoot();
	wxString workingstring;
	workingstring << usermodel->GetID();
	wxXmlNode* user1 = new wxXmlNode(root, wxXML_ELEMENT_NODE, wxString("User"));
	user1->AddAttribute(wxString("ID"), workingstring);//ZMIANA NA STRING
	wxXmlNode* ipadress = new wxXmlNode(user1, wxXML_ELEMENT_NODE, wxString("IP_ADRESS"));
	workingstring.clear();
	workingstring << usermodel->GetIP();
	ipadress->AddChild(new wxXmlNode(ipadress, wxXML_TEXT_NODE, wxEmptyString, workingstring));
	wxXmlNode* Name = new wxXmlNode(user1, wxXML_ELEMENT_NODE, wxString("Name"));
	Name->AddChild(new wxXmlNode(Name, wxXML_TEXT_NODE, wxEmptyString, usermodel->GetName()));
	wxXmlNode* Surname = new wxXmlNode(user1, wxXML_ELEMENT_NODE, wxString("Surname"));
	Surname->AddChild(new wxXmlNode(Surname, wxXML_TEXT_NODE, wxEmptyString, usermodel->GetSurname()));
	wxXmlNode* Favorite = new wxXmlNode(user1, wxXML_ELEMENT_NODE, wxString("Favorite"));
	workingstring.clear();
	workingstring << usermodel->GetFavourite();
	Favorite->AddChild(new wxXmlNode(Favorite, wxXML_TEXT_NODE, wxEmptyString, workingstring));
	wxXmlNode* Photo_Path = new wxXmlNode(user1, wxXML_ELEMENT_NODE, wxString("Photo_Path"));
	Photo_Path->AddChild(new wxXmlNode(Photo_Path, wxXML_TEXT_NODE, wxEmptyString, usermodel->GetPath()));

    return true;

}


