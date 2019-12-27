//---------------------------------------------------------------------------

#ifndef BattlefieldDerivatH
#define BattlefieldDerivatH
 #include "Card.h"
 #include "Battlefield.h"
 class Battlefield_Deriv:public Battlefield
{

	vector<Card*> validTargets;
	public:
	Battlefield_Deriv(TForm * parent);
	void ActivateOrders(vector<Card*> );
	void IncresePeriodicCounter(vector<Card*>);
	int CalculateScore(vector<Card*>);
	bool highlightValidTargets(vector<Card*>,Card*);
	void  clearHighlightedTargets();
	bool  isTargetValid(Card* );
};
//---------------------------------------------------------------------------
#endif
