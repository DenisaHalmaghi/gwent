//---------------------------------------------------------------------------

#ifndef BattlefieldH
#define BattlefieldH


#include <vector>
#define C_MyTop 525
#define C_Left_Start 200
#define C_Left_End 1720

#define C_CardHeight 180
#define C_Ratio 0.696629



using namespace std;


class Battlefield
{
friend class JocGwent;
protected:
	bool inamic;
	vector<pair<int,int>> positions[2];
	TLabel * score;
	int pos_top[2];
	vector<int> periodic;
	vector<int> onHold;
	public:
	Battlefield(TForm *,int inamic=0);
	void pushPeriodic(int);
	void freePosition(int);
	void freeAllPositions();
	bool inOnHold(int);
	void clearOnHold();
	void adToOnHold(int);
	bool onBoard(int);
//	vector<int> getPeriodic();
//	vector<int> getOnHold();

	TPoint place(TPoint,int);


};

//---------------------------------------------------------------------------
#endif
