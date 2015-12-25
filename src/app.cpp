#include <iostream>

#include "app.h"
#include "appinfo.h"

App::App(int& argc, char** argv) 
{
	
}

App::~App()
{
}

int App::Execute()
{
	std::cout << "Hello World!";
	return 0;
}
