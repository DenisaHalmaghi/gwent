//---------------------------------------------------------------------------

#ifndef JocGwentH
#define JocGwentH
#include "UnitCard.h"
#include "Deck.h"
#include "BattlefieldDerivat.h"

class JocGwent
{

TImage* board;
TTimer* targetTimer;

vector<Card*> prototypes;
vector<Card*> Cards;
vector<int> hand;
vector<pair<int,int>> effects[3];
Battlefield_Deriv* btl;
Deck* deck;
//game logic vars
bool targetWasSelected;    //mai trebuie?
Card* targetedCard;
Card* droppedCard;
bool myTurn;
int roundNumber;
int turn;
//vector<pair<int,int>> positions[2];
//int pos_top[2];

public:
 JocGwent(TForm*,TImage*,vector<Card*>,vector<pair<int,int>>);
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
 void __fastcall cardClicked(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);


};
//---------------------------------------------------------------------------
#endif
