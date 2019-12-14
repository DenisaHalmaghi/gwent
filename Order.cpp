//---------------------------------------------------------------------------

#pragma hdrstop

#include "Order.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

Order::Order(){
	type="order";

}

Order::Order(int name,int qt,bool zeal):Ability(name,qt,"order"){
   this->zeal=zeal;

}

int Order::getZeal(){
	return zeal;
}

int Order::getNoOfCharges()
{
   return canBeUsed()?1:0;
}


