//---------------------------------------------------------------------------

#pragma hdrstop

#include "UnitCard.h"


UnitCard::UnitCard():Card(){

	rowRestriction=0;
	power=4;

}

UnitCard::UnitCard(int index,TCaption name,UnicodeString faction,UnicodeString image,int pc,
Target* target,Ability* ab,int pw,int rs)
:Card(index,name,faction,image,pc,target,ab,"unit")
{
	  power=pw;
	  rowRestriction=rs;
}

void UnitCard::buildCardUI(TPoint pos,TForm* parent)
{
	if(ability->getAbilityType()=="deploy")
	{
	   cardInterface=new UnitCardUI(pos,parent,image, faction, provisionCost, ability, power,nrInst);
	}
	else
	{
		cardInterface=new OrderCardUI(pos,parent,image, faction, provisionCost, ability, power,nrInst);
    }

}

void UnitCard::placeOnBattlefield(Battlefield* btl,TPoint pos)
{
		Card::placeOnBattlefield(btl,pos);
		//baga orders
		ability->prepare(btl,nrInst);
}

void UnitCard::modificaPower(int dp)
{
    UnitCardUI* unit=(UnitCardUI*)cardInterface;
	int oldPower= unit->getPower();
	int newPower= oldPower+dp;
	TColor newColor=clWhite;
	if(newPower<power)
	{
		  newColor=clRed;
	}
	else if(newPower>power)
	{
		  newColor=clLime;
    }
	unit->setPower(newPower);
	unit->setColor(newColor);
}

void UnitCard::Copiaza(Card*& copie,int index)
{
	Ability* ab;
	Target* tg;
	copiazaEsentiale(ab,tg);
	copie=new UnitCard(index,name,faction,image,provisionCost,tg,ab,power,rowRestriction);
}

//---------------------------------------------------------------------------
Special_Card::Special_Card(int index,TCaption name,UnicodeString faction,UnicodeString image,int pc,
Target* target,Ability* ab)
:Card(index,name,faction,image,pc,target,ab,"special_card")
{

}

void Special_Card::Copiaza(Card*& copie,int index)
{
	Ability* ab;
	Target* tg;
	copiazaEsentiale(ab,tg);
	copie=new Special_Card(index,name,faction,image,provisionCost,tg,ab);
}

void Special_Card::placeOnBattlefield(Battlefield* btl,TPoint pos)
{
	cardInterface->Muta(C_Left_End+30,435);
}

//void Special_Card::buildCardUI(TPoint pos,TForm* parent)
//{
//	cardInterface=new NonUnitCardUI(pos,parent,image,faction,provisionCost,ability,"artefact",nrInst);
//}
void Special_Card::triggerAbility(Card* tg, vector<pair<int, int>>effects[3],Battlefield* btl){
	Card::triggerAbility(tg,effects,btl);
	destroyUI();
}


#pragma package(smart_init)
