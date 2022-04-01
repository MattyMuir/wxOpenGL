#include "Canvas.h"
#include "Main.h"

wxBEGIN_EVENT_TABLE(Canvas, wxPanel)
	EVT_PAINT(Canvas::OnPaint)
	EVT_SIZE(Canvas::Resized)
    EVT_IDLE(Canvas::OnIdle)
    EVT_KEY_DOWN(Canvas::OnKeyDown)
wxEND_EVENT_TABLE()

Canvas::Canvas(wxWindow* parent, int* attribs) : wxGLCanvas(parent, wxID_ANY, attribs)
{
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
	mainPtr = (Main*)parent;

    // GL stuff
    context = new wxGLContext(this);

    while (!IsShown()) {};
    SetCurrent(*context);

    glLoadIdentity();
    GLenum err = glewInit();

    err = glewInit();
    if (GLEW_OK != err)
    {
        DebugBreak();
    }

    shader = new Shader(Shader::Compile("basic.shader"));
    shader->Bind();

    verts = new float[6]{ 0.0f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f };
    vertCount = 3;

    va = new VertexArray;
    vb = new VertexBuffer(verts, sizeof(float) * vertCount * 2);
    vbl = new VertexBufferLayout;

    vbl->Push<float>(2);
    va->AddVBuffer(*vb, *vbl);

    SetWireframe(false);

    fout.open("C:\\Users\\matty\\Desktop\\wxglout.txt");
}

Canvas::~Canvas()
{
    fout.close();

    delete context;
    delete vb;
    delete vbl;
    delete va;
    delete shader;
    delete[] verts;
}

void Canvas::OnDraw()
{
    TIMER(t);
    glViewport(0, 0, w, h);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, vertCount);

    glFlush();
    SwapBuffers();

    STOP_LOG(t);
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

    evt.Skip();
}

void Canvas::OnKeyDown(wxKeyEvent& evt)
{
    if (evt.GetKeyCode() == WXK_RETURN)
    {
        // Randomly change all verticies for demo purposes
        for (int i = 0; i < vertCount * 2; i++)
            verts[i] = (float)rand() / RAND_MAX * 2 - 1;

        vb->SetData(verts);

        Refresh();
    }
    evt.Skip();
}