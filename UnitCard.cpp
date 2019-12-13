//---------------------------------------------------------------------------

#pragma hdrstop

#include "UnitCard.h"


UnitCard::UnitCard():Card(){

	rowRestriction=0;
	power=4;

}

UnitCard::UnitCard(int index,TCaption name,UnicodeString faction,UnicodeString image,int pc,
bool target,Ability* ab,int pw,int rs)
:Card(index,name,faction,image,pc,"unit",target,ab)
{
	  power=pw;
	  rowRestriction=rs;
}

void UnitCard::buildCardUI(TPoint pos,TForm* parent)
{
	cardInterface=new UnitCardUI(pos,parent,image, faction, provisionCost, ability, power,nrInst);
}

void UnitCard::placeOnBattlefield()
{
	return;

}


//---------------------------------------------------------------------------

void Artefact::placeOnBattlefield()
{
	return;
}

Artefact::Artefact()
{


}
#pragma package(smart_init)
