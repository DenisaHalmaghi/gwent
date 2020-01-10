//---------------------------------------------------------------------------

#ifndef AbilityH
#define AbilityH
#include <string>
#include "Battlefield.h"
#include "Util.h"
#define C_Bleed 0
#define C_Vitality 1
#define C_Poison 4
#define C_Boost 2
#define C_Damage 3
#define C_Purify 5
#define C_Lock 6
#define C_Destroy 7


using namespace std;


class Ability
{
friend class JocGwent;

protected:
	 int name;
	 int quantum;
	 TCaption type;

	 UnicodeString description;
public:
	 Ability();
	 Ability(int,int,TCaption tp="deploy");
	 TCaption getAbilityType();
	 void triggerAbility();
	 int getName();

	 void virtual CopiazaAbility(Ability*&);
     int getQuantum();
	 int virtual getZeal();
	 int virtual getCooldown();
	 int  virtual getNoOfCharges();
	 void virtual prepare(Battlefield* btl,int){return;};     //battlefield baza
	 UnicodeString getAbilityDescription();



};
//---------------------------------------------------------------------------
#endif
