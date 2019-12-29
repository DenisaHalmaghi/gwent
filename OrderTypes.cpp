//---------------------------------------------------------------------------

#pragma hdrstop

#include "OrderTypes.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

 NonRep::NonRep(int name,int qt,bool zeal):Order(name,qt,zeal)
 {
	 used=0;
 }

 bool NonRep::canBeUsed()
 {
	 return !used;
 }

 void NonRep:: signalUsed()
 {
	 used=1;
 }

 void  NonRep::CopiazaAbility(Ability*& copie)
{
	  copie=new NonRep(name,quantum,zeal);
}


 Charges::Charges(int name,int qt,int charges,bool zeal):Order(name,qt,zeal)
 {
	this-> charges=charges;
	description="\nCharges:"+IntToStr(charges)+description;
	description+="\nCharges:Number of times order can be activated";
 }

 bool Charges::canBeUsed()
 {
	 return charges>0;
 }

 void Charges::signalUsed()
 {
	 charges--;
 }

 int Charges::getNoOfCharges()
{
   return charges;
}

 void  Charges::CopiazaAbility(Ability*& copie)
{
	  copie=new Charges(name,quantum,charges,zeal);
}

  Periodic::Periodic(int name,int qt,int cd,bool zeal):Order(name,qt,zeal)
 {
	cooldown=cd;
	contor=zeal?cd:cd-1;
 }

 bool Periodic::canBeUsed()
 {
	int ct=  contor;
	int cd=cooldown;
	 return contor>=cooldown;
 }

 void Periodic::signalUsed()
 {
	 contor=0;
 }

 void  Periodic::prepare(Battlefield* btl,int index)
 {
	 btl->pushPeriodic(index);
 }

 void Periodic::operator++()
 {
	   contor++;
 }

 void  Periodic::CopiazaAbility(Ability*& copie)
{
	  copie=new Periodic(name,quantum,cooldown,zeal);
}




