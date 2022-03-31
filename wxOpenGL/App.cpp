#include "App.h"

wxIMPLEMENT_APP(App);

App::App()
{

}

bool App::OnInit()
{
	frame = new Main;
	frame->Show();

	return true;
}