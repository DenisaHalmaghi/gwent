//---------------------------------------------------------------------------

#ifndef CardH
#define CardH
#include <string>
#include "Ability.h"
#include "UnitCardUI.h"
#include "NonUnitCardUI.h"
#include <vector>

using namespace std;

class Card
{
protected:

   TCaption name;
   UnicodeString image,faction,cardType;
   int provisionCost;
   Ability* ability;
   bool target;
   int nrInst;
public:
	CardUI* cardInterface;

   Card(int,TCaption,UnicodeString ,UnicodeString ,int,UnicodeString,bool,Ability*);
   Card();
   ~Card();
   Ability* getAbility();
   bool getTarget();
   int getIndex();
   void destroyUI();
   void Bleed_Vitality(int ,int ,UnitCardUI*, vector<pair<int, int>>effects[3]);
   void virtual buildCardUI(TPoint,TForm*);
   void triggerAbility(Card*,vector < pair<int,int> > [3]);
   void modificaPower(int);

};
//---------------------------------------------------------------------------
#endif
