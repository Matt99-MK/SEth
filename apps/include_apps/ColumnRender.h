/////////////////////////////////////////////////////////////////////////////
// Name:        ColumnRender.h
// Author:      Mateusz Kosmala <mateuszkosmala1@gmail.com>
// Created:     2012-03-03
// Copyright:   (c) 2020 by Mateusz Kosmala
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _RENDER_H__
#define _RENDER_H__

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/dataview.h>

class ColumnRender : public wxDataViewCustomRenderer
{

public:

	ColumnRender(){}
	ColumnRender(wxDataViewCellMode mode);
	virtual bool Render(wxRect rect, wxDC* dc, int state) wxOVERRIDE;
	virtual bool ActivateCell(const wxRect& WXUNUSED(cell), wxDataViewModel* WXUNUSED(model), const wxDataViewItem& WXUNUSED(item),
			unsigned int WXUNUSED(col), const wxMouseEvent* mouseEvent) wxOVERRIDE;
	virtual wxSize GetSize() const wxOVERRIDE;
	virtual bool SetValue(const wxVariant& value) wxOVERRIDE;
	virtual bool GetValue(wxVariant& WXUNUSED(value)) const wxOVERRIDE;
	virtual wxString GetAccessibleDescription() const wxOVERRIDE;
	virtual bool HasEditorCtrl() const wxOVERRIDE;
	virtual wxWindow* CreateEditorCtrl(wxWindow* parent, wxRect labelRect, const wxVariant& value) wxOVERRIDE;
	virtual bool GetValueFromEditorCtrl(wxWindow* ctrl, wxVariant& value) wxOVERRIDE;

private:

	wxString m_value;
	wxDECLARE_DYNAMIC_CLASS(ColumnRender);

};

#endif











