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

bool Order::getZeal(){
	return zeal;
}


