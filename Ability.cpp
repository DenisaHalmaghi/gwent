//---------------------------------------------------------------------------

#pragma hdrstop

#include "Ability.h"

Ability::Ability(){
	name=C_Boost;
	quantum=3;
	type="deploy";
	repeatable=0;
}

Ability::Ability(int name,int qt,TCaption tp){
	this->name=name;
	this->type=tp;
	quantum=qt;
   //	repeatable=rep;
}

TCaption Ability::getAbilityType(){
	return type;
}

void Ability::triggerAbility(){
}

int Ability::getName(){
	return name;
}

int Ability::getZeal(){
	return -1;
}

 bool Ability::getRep(){
	return repeatable;
 }

 int  Ability::getCooldown(){
	return 0;
 }

  int  Ability::getNoOfCharges(){
	return 0;
 }

 int Ability::getQuantum()
 {
	 return quantum;
 }
//---------------------------------------------------------------------------
#pragma package(smart_init)
