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
	 return used;
 }

 void NonRep:: signalUsed()
 {
	 used=1;
 }


 Charges::Charges(int name,int qt,int charges,bool zeal):Order(name,qt,zeal)
 {
	this-> charges=charges;
 }

 bool Charges::canBeUsed()
 {
	 return charges>0;
 }

 void Charges::signalUsed()
 {
	 charges--;
 }

  Periodic::Periodic(int name,int qt,int cd,bool zeal):Order(name,qt,zeal)
 {
	cooldown=cd;
	contor=zeal?0:-1;
 }

 bool Periodic::canBeUsed()
 {
	 return !cooldown;
 }

 void Periodic::signalUsed()
 {
	 contor=++contor%cooldown;
 }

 void  Periodic::prepare(Battlefield* btl,int index)
 {
	 btl->pushPeriodic(index);
 }
