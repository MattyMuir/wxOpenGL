#pragma once
#include "wx/wx.h"

#include "glall.h"
#include "glhelpers.h"
#include <wx/glcanvas.h>

#include <string>
#include <fstream>

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "Shader.h"

#include "Timer.h"

#define TIMING 0

#if TIMING
#define TIMER(x) Timer x
#define STOP_LOG(x) x.Stop(); fout << x.duration * 0.001 << "ms\n"
#else
#define TIMER(x)
#define STOP_LOG(x)
#endif

class Main;

class Canvas : wxGLCanvas
{
public:
	Canvas(wxWindow* parent, int* attribs);
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

	std::ofstream fout;

	void OnDraw();
	void OnPaint(wxPaintEvent& evt);
	void Resized(wxSizeEvent& evt);
	void OnIdle(wxIdleEvent& evt);
	void OnKeyDown(wxKeyEvent& evt);

	wxDECLARE_EVENT_TABLE();
};