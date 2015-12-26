#include <iostream>
#include <string.h>
#include "lib.h"
#include "appinfo.h"



Lib::Lib()
{
	
}

Lib::~Lib()
{
}

int Lib::Sum(int a,int b)
{
	return a + b;
}

std::string Lib::Message()
{	
	std::string msg("Message from library: FIRST");
	return msg;
}
