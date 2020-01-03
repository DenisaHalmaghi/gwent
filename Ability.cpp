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

	//create description
    	UnicodeString text[]=
		{"Give bleeding for","Give vitality for","Boost a unit by","Damage a unit by",
		"Poison a unit","Purify a unit","Lock a unit","Destroy a unit "};

		UnicodeString abilityDescription[]=
		{"Bleeding:Damages a unit by 1 on turn end","Vitality:Boosts a unit by 1 on turn end",
		"Boost:Increase a Unit's current Power.","Damage:Decrease a Unit's current Power."
		,"Poison:If a unit has two Poison statuses, destroy it.","Purify:Remove all statuses.",
		"Lock:Status that disables a card's abilities.","Destroy:Remove a card from the battlefied"

		};

		description+=(type=="order"?"\nOrder:":"\nDeploy:")+text[name]+" "+(name<4?IntToStr(quantum):"")+ (name<2?" rounds":"")
		+"\n\n"+abilityDescription[name];
		description+=(type=="order"?"\nOrder:Lets the player manually trigger the ability":
	   "\nDeploy:Trigger this ability when played.");

       if(!qt)
		{
			description="\nNo ability";
		}

   //	repeatable=rep;
}

TCaption Ability::getAbilityType(){
	return type;
}

void  Ability::CopiazaAbility(Ability*& copie)
{
	  copie=new Ability(name,quantum,type);
}

UnicodeString Ability::getAbilityDescription(){
	return description;
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
