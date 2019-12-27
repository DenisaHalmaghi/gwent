//---------------------------------------------------------------------------

#pragma hdrstop

#include "Target.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

Target::Target(int side,UnicodeString type)
{
	this->side=side;
	this->type=type;
}

int Target::getSide()
{
	return side;
}

UnicodeString Target::getType()
{
	return type;
}
