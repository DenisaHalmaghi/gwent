//---------------------------------------------------------------------------

#ifndef TargetH
#define TargetH

class Target
{
	protected:
	int side;
	UnicodeString type;
	friend class Card;
	//string condition
	public:
	Target(int,UnicodeString);
	UnicodeString getType();
	int getSide();
};

//---------------------------------------------------------------------------
#endif
