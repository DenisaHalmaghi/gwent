//---------------------------------------------------------------------------

#ifndef CardH
#define CardH
#include <string>
//#include "OrderTypes.h"
#include "OrderCardUI.h"
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

   Card(int,TCaption,UnicodeString ,UnicodeString ,int,bool,Ability*,UnicodeString cardType="artefact");
   Card();
   ~Card();
   Ability* getAbility();
   bool getTarget();
   int getIndex();
   void destroyUI();
   void takeCareOfOrder();
   void Bleed_Vitality(int ,int ,UnitCardUI*, vector<pair<int, int>>effects[3]);
   void virtual buildCardUI(TPoint,TForm*);
   void virtual placeOnBattlefield(Battlefield*,TPoint);
   void virtual triggerAbility(Card*,vector < pair<int,int> > [3],Battlefield*);
   void virtual modificaPower(int);
   void toggleDescription();


};
//---------------------------------------------------------------------------
#endif
