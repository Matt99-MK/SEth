/////////////////////////////////////////////////////////////////////////////
// Name:        ColumnRender.h
// Author:      Mateusz Kosmala <mateuszkosmala1@gmail.com>
// Created:     2012-03-03
// Copyright:   (c) 2020 by Mateusz Kosmala
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#include<ColumnRender.h>

wxIMPLEMENT_DYNAMIC_CLASS(ColumnRender, wxDataViewCustomRenderer);

ColumnRender::ColumnRender(wxDataViewCellMode  mode) : wxDataViewCustomRenderer(wxString("string"), mode, wxALIGN_CENTER)
{

}


bool ColumnRender::Render(wxRect rect, wxDC* dc, int state)  
{

	dc->SetBrush(*wxLIGHT_GREY_BRUSH);
	dc->SetPen(*wxTRANSPARENT_PEN);
	rect.Deflate(2);
	rect.SetHeight(80);
	dc->DrawRoundedRectangle(rect, 5);
	RenderText(m_value,0,wxRect(dc->GetTextExtent(m_value)).CentreIn(rect),dc,state);
	return true;

}

bool ColumnRender::ActivateCell(const wxRect& WXUNUSED(cell),wxDataViewModel* WXUNUSED(model),const wxDataViewItem& WXUNUSED(item),unsigned int WXUNUSED(col),const wxMouseEvent* mouseEvent) 
{

	wxString position;
	if (mouseEvent)
		position = wxString::Format("via mouse at %d, %d", mouseEvent->m_x, mouseEvent->m_y);
	else
		position = "from keyboard";
	wxLogMessage("ColumnRender ActivateCell() %s", position);
	return false;

}

wxSize ColumnRender::GetSize() const 
{

	return wxSize(60, 20);

}

bool ColumnRender::SetValue(const wxVariant& value) 
{
		
	m_value = value.GetString();
	return true;

}

bool ColumnRender::GetValue(wxVariant& WXUNUSED(value)) const 
{ 

	return true; 

}

wxString ColumnRender::GetAccessibleDescription() const 
{

	return m_value;

}

bool ColumnRender::HasEditorCtrl() const 
{ 
		
	return true; 

}

wxWindow* ColumnRender::CreateEditorCtrl(wxWindow* parent, wxRect labelRect, const wxVariant& value) 
{

	wxTextCtrl* text = new wxTextCtrl(parent, wxID_ANY, value,
			labelRect.GetPosition(),
			labelRect.GetSize(),
			wxTE_PROCESS_ENTER);
	text->SetInsertionPointEnd();
	return text;

}

bool ColumnRender::GetValueFromEditorCtrl(wxWindow* ctrl, wxVariant& value) 
{

	wxTextCtrl* text = wxDynamicCast(ctrl, wxTextCtrl);
	if (!text)
		return false;

	value = text->GetValue();

	return true;

}
