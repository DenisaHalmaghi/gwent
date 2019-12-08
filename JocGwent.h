//---------------------------------------------------------------------------

#ifndef JocGwentH
#define JocGwentH
#include "UnitCard.h"
#include "UnitCardUI.h"
#include "NonUnitCardUI.h"

#define C_MyTop 525
#define C_Left_Start 200
#define C_Left_End 1700
class JocGwent
{
TImage* board;
TTimer* targetTimer;
vector<Card*> Cards;
vector<pair<int,int>> effects[3];

//game logic vars
bool targetWasSelected;
Card* targetedCard;
Card* droppedCard;
bool myTurn;
bool placedCard;
int turn;
vector<pair<int,int>> positions[2];
int pos_top[2];

public:
 JocGwent(TForm*,TImage*);
 ~JocGwent();
 void Init(TForm*);
 bool endTurn();
 bool switchTurn();

 void __fastcall cardMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
 void __fastcall boardDragOver(TObject *Sender, TObject *Source, int X,
		  int Y, TDragState State, bool &Accept);
 void __fastcall boardDragDrop(TObject *Sender, TObject *Source, int X,
		  int Y);
 void __fastcall targetTimerTimer(TObject *Sender);
 void __fastcall cardClicked(TObject *Sender);


};
//---------------------------------------------------------------------------
#endif
