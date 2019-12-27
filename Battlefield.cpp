//---------------------------------------------------------------------------

#pragma hdrstop

#include "Battlefield.h"
#include "JocGwent.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

Battlefield::Battlefield(TForm * parent)
{

	//set up score
	score= new TLabel(parent);
	score->Parent=parent;
	score->Caption=0;
	score->Font->Color=clWhite;
	score->Font->Size=43;
	score->Font->Style=TFontStyles() << fsBold;
	score->Left=15;
	score->Top=C_MyTop;

	//set up positions
	int width=C_CardHeight*C_Ratio;
	int left=C_Left_Start;
	int s= positions[0].size();
	//vector<pair<int,int>> temp;
	while(left+width+5<C_Left_End)
	{
	   pair entry=make_pair(left,-1);
	   positions[0].push_back(entry);
	   positions[1].push_back(entry);
	   left=left+width+5;
	}
	int c=0;
	pos_top[0]=C_MyTop;
	pos_top[1]=C_MyTop+C_CardHeight+7;
}

TPoint Battlefield::place(TPoint currPos,int cardIndex)
{
	  int index=(abs(currPos.Y-pos_top[0])> abs(currPos.Y-pos_top[1]))?1:0;
	  int minIndex=0;
	  int dm=1000; //DIF MIN
	  int temp;
	  for(int i=0;i<positions[index].size();i++)
	  {
		  pair current= positions[index][i];
		  temp=abs(current.first-currPos.X);
		 if(temp<dm&&current.second==-1)  //if you move cards around second becomes occupied!!!

		 {
			 minIndex=i;
			 dm=temp;

		 }
	  }

	  positions[index][minIndex].second= cardIndex;//punem indexul cartii in vector
	  return Point(positions[index][minIndex].first,pos_top[index]);
}

void Battlefield::freePosition(int card)
{
	   for(int i=0;i<2;i++)
	   {
		   for(int j=0;j<positions[i].size();j++)
		   {
			   if(positions[i][j].second==card)
			   {
					positions[i][j].second=-1;
					return;
			   }
		   }
	   }
}

bool Battlefield::onBoard(int card)
{
	for(int j=0;j<2;j++)
	{

		for(int i=0;i< positions[j].size();i++)
		{
			if(positions[j][i].second==card)
			{
			   return true;
			}

		}

    }

	return false;
}


void Battlefield::freeAllPositions()
{
	   for(int i=0;i<2;i++)
	   {
		   for(int j=0;j<positions[i].size();j++)
		   {

				positions[i][j].second=-1;

		   }
	   }
}

void Battlefield::pushPeriodic(int index)
{

	periodic.push_back(index);
}

bool Battlefield::inOnHold(int index)
{
	for(int i=0;i< onHold.size();i++)
	{
		if(onHold[i]==index)
		{
		   return true;
		}

	}
	return false;
}

void Battlefield::clearOnHold()
{

	onHold.clear();
}

void Battlefield::adToOnHold(int index)
{

	onHold.push_back(index);
}

//vector<int> Battlefield::getPeriodic()
//{
//
//	return periodic;
//}
//
//vector<int> Battlefield::getOnHold()
//{
//    return onHold;
//}
