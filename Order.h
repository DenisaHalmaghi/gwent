//---------------------------------------------------------------------------

#ifndef OrderH
#define OrderH
#include "Ability.h"

class Order:public Ability{
	bool zeal;

   public:
	Order();
	Order(int,int,bool zeal=0);
	bool getZeal();
	bool virtual canBeUsed()=0;
	void virtual signalUsed()=0;

};
//---------------------------------------------------------------------------
#endif
