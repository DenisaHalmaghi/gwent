//---------------------------------------------------------------------------

#ifndef BattlefieldDerivatH
#define BattlefieldDerivatH
 #include "Card.h"
 #include "Battlefield.h"
 class Battlefield_Deriv:public Battlefield
{

   //	vector<Card*> Cards;
	public:
	Battlefield_Deriv(TForm * parent);
	void ActivateOrders(vector<Card*> );
	void IncresePeriodicCounter(vector<Card*>);
	int CalculateScore(vector<Card*>);


};
//---------------------------------------------------------------------------
#endif
