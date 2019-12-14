//---------------------------------------------------------------------------

#ifndef OrderTypesH
#define OrderTypesH
#include "Order.h"

class NonRep:public Order
{
	bool used;
	public:
	NonRep(int,int,bool zeal=0);
	bool virtual canBeUsed();
	void virtual signalUsed();

};

class Charges:public Order
{
	int charges;
	public:
	Charges(int,int,int,bool zeal=0);
	bool virtual canBeUsed();
	void virtual signalUsed();
	int  virtual getNoOfCharges();
};

class Periodic:public Order
{
	int cooldown;
	int contor;
	public:
	Periodic(int,int,int cd=2,bool zeal=0);
	void cresteContor();
	bool virtual canBeUsed();
	void virtual signalUsed();
	void virtual prepare(Battlefield* btl,int );


};
//---------------------------------------------------------------------------
#endif
