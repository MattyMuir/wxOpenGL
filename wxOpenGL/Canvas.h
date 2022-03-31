#pragma once
#include "wx/wx.h"
#include <wx/dcclient.h>
#include <wx/dcmemory.h>
#include <wx/dcbuffer.h>

#include "glall.h"
#include "glhelpers.h"
#include <wx/glcanvas.h>

#include <string>

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "Shader.h"

class Main;

class Canvas : wxGLCanvas
{
public:
	Canvas(wxWindow* parent);
	~Canvas();
	Main* mainPtr;

protected:
	int w, h;
	bool resizing = false;

	wxGLContext* context;
	VertexBuffer* vb;
	VertexBufferLayout* vbl;
	VertexArray* va;
	Shader* shader;
	float* verts;
	int vertCount;

	void OnDraw();
	void OnPaint(wxPaintEvent& evt);
	void Resized(wxSizeEvent& evt);
	void OnIdle(wxIdleEvent& evt);

	wxDECLARE_EVENT_TABLE();
};