//---------------------------------------------------------------------------

#ifndef OrderH
#define OrderH
#include "Ability.h"

class Order:public Ability{
protected:
	bool zeal;

   public:
	Order();
	Order(int,int,bool zeal=0);

	int getZeal();
	bool virtual canBeUsed()=0;
	void virtual signalUsed()=0;
	int getNoOfCharges();


};
//---------------------------------------------------------------------------
#endif
