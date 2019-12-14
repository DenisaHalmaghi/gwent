//---------------------------------------------------------------------------

#ifndef BattlefieldH
#define BattlefieldH


#include <vector>
#define C_MyTop 525
#define C_Left_Start 200
#define C_Left_End 1720

#define C_CardHeight 190
#define C_Ratio 0.696629

using namespace std;

class Battlefield
{
	vector<pair<int,int>> positions[2];
	int pos_top[2];
	vector<int> periodic;
	vector<int> onHold;
	public:
	Battlefield();
	void pushPeriodic(int);
	void freePosition(int);
	void freeAllPositions();
	bool inOnHold(int);
	void clearOnHold();
	void adToOnHold(int);
	bool onBoard(int);
	vector<int> getPeriodic();
	vector<int> getOnHold();

	TPoint place(TPoint,int);


};
//---------------------------------------------------------------------------
#endif
