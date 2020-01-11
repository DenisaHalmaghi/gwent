//---------------------------------------------------------------------------

#ifndef CardH
#define CardH
#include <string>
//#include "OrderTypes.h"
#include "OrderCardUI.h"
#include "NonUnitCardUI.h"
#include "Target.h"
#include <vector>

#define C_Self  0
#define C_Ally  1
#define C_Enemy  2
#define C_Any   3

using namespace std;


class Card
{
	friend class JocGwent;
protected:

   TCaption name;
   UnicodeString image,faction,cardType;
   int provisionCost;
   Ability* ability;
   Target* target;
   int nrInst;

   void copiazaEsentiale(Ability*&,Target*&);
   void Bleed_Vitality(int ,int ,UnitCardUI*, vector<pair<int, int>>effects[2]);

public:
	CardUI* cardInterface;

	Card(int,TCaption,UnicodeString ,UnicodeString ,int,Target*,Ability*,UnicodeString cardType="artefact");
	Card();
	~Card();

	Ability* getAbility();
	int getIndex();
	UnicodeString getFaction();
	int getProvisionCost();


	void destroyUI();
	void virtual Copiaza(Card*&,int);
	void takeCareOfOrder();
	void virtual takeCareOfSpecialCard(){};
	void virtual buildCardUI(TPoint,TWinControl*);
	void virtual placeOnBattlefield(Battlefield*,TPoint);
	void virtual triggerAbility(Card*,vector < pair<int,int> > [3],Battlefield*,Battlefield*);
	void virtual modificaPower(int);
	void  clearFromEffects(vector < pair<int,int> > [3]);
	void toggleDescription();
	Target* getTargetObject();
	bool checkTargetMatch(Target*);

};


//---------------------------------------------------------------------------
#endif
