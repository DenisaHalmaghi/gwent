//---------------------------------------------------------------------------

#ifndef AbilityH
#define AbilityH
#include <string>
#include "Battlefield.h"

#define C_Bleed 0
#define C_Vitality 1
#define C_Poison 2
#define C_Boost 3
#define C_Damage 4
#define C_Purify 5
#define C_Lock 6
#define C_Destroy 7
#define C_GiveCharges 8

using namespace std;


class Ability
{
protected:
	 int name;
	 int quantum;
	 TCaption type;
	 bool repeatable;     //wat is dis? :))
	 UnicodeString description;
public:
	 Ability();
	 Ability(int,int,TCaption tp="deploy");
	 TCaption getAbilityType();
	 void triggerAbility();
	 int getName();
	 bool getRep();
	 void virtual CopiazaAbility(Ability*&);
     int getQuantum();
	 int virtual getZeal();
	 int virtual getCooldown();
	 int  virtual getNoOfCharges();
	 void virtual prepare(Battlefield* btl,int){return;};     //battlefield baza
	 UnicodeString getAbilityDescription();

   //	 ~Ability();

};
//---------------------------------------------------------------------------
#endif
