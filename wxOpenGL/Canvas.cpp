#include "Canvas.h"
#include "Main.h"

wxBEGIN_EVENT_TABLE(Canvas, wxPanel)
	EVT_PAINT(Canvas::OnPaint)
	EVT_SIZE(Canvas::Resized)
    EVT_IDLE(Canvas::OnIdle)
wxEND_EVENT_TABLE()

Canvas::Canvas(wxWindow* parent) : wxGLCanvas(parent, wxID_ANY)
{
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
	mainPtr = (Main*)parent;

    // GL stuff
    context = new wxGLContext(this);

    while (!IsShown()) {};  // Force the Shown
    wxGLCanvas::SetCurrent(*context);

    glLoadIdentity();
    GLenum err = glewInit();

    err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }

    shader = new Shader(Shader::Compile("basic.shader"));
    shader->Bind();

    verts = new float[6]{0.0f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f};
    vertCount = 3;

    va = new VertexArray;
    vb = new VertexBuffer(verts, sizeof(float) * vertCount * 2);
    vbl = new VertexBufferLayout;

    vbl->Push<float>(2);
    va->AddVBuffer(*vb, *vbl);

    SetWireframe(false);
}

Canvas::~Canvas()
{
    delete context;
    delete vb;
    delete vbl;
    delete va;
    delete shader;
    delete[] verts;
}

void Canvas::OnDraw()
{
    SetCurrent(*context);
    glViewport(0, 0, (GLint)GetSize().x, (GLint)GetSize().y);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, vertCount);

    glFlush();
    SwapBuffers();
}

void Canvas::OnPaint(wxPaintEvent& evt)
{
	GetSize(&w, &h);
    if (!resizing) OnDraw();
	evt.Skip();
}

void Canvas::Resized(wxSizeEvent& evt)
{
    if (wxGetMouseState().LeftIsDown()) resizing = true;
	evt.Skip();
}

void Canvas::OnIdle(wxIdleEvent& evt)
{
    if (resizing)
    {
        if (!wxGetMouseState().LeftIsDown())
        {
            resizing = false;
            Refresh();
        }
    }
}