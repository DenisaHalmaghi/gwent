//---------------------------------------------------------------------------

#pragma hdrstop

#include "Battlefield.h"
#include "JocGwent.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

Battlefield::Battlefield(TForm * parent,int inamic)
{

	//set up score
	this->inamic=inamic;
	score= new TLabel(parent);
	score->Parent=parent;
	score->Caption=0;
	score->Font->Color=clWhite;
	score->Font->Size=43;
	score->Font->Style=TFontStyles() << fsBold;
	score->Left=15;
	if(inamic)
	{
	  score->Top=C_MyTop-160;
	}
	else
	{
       score->Top=C_MyTop+80;
    }


	//set up positions
	int width=C_CardHeight*C_Ratio;
	int left=C_Left_Start;
	int s= positions[0].size();

	while(left+width+5<C_Left_End)
	{
	   pair entry=make_pair(left,-1);
	   positions[0].push_back(entry);
	   positions[1].push_back(entry);
	   left=left+width+5;
	}
	int c=0;


	pos_top[0]=C_MyTop;
	pos_top[1]=pos_top[0]+C_CardHeight+20;

}

TPoint Battlefield::place(TPoint currPos,int cardIndex)
{
	  int index=(abs(pos_top[1]-currPos.Y)>/*!!*/ abs(pos_top[0]-currPos.Y))?0:1;
	  int minIndex=0;
	  int dm=9000; //DIF MIN
	  int temp;
	  int sus= pos_top[0];
	  int jos= pos_top[1];
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

	  int top=pos_top[index];
	  if(inamic)
	  {
		top=C_MyTop- C_CardHeight-50;
		if(index)
		{
			top-=C_CardHeight+15;
        }
      }
	  positions[index][minIndex].second= cardIndex;//punem indexul cartii in vector
	  return Point(positions[index][minIndex].first,top);
}

void Battlefield::freePosition(int card)
{

		for(int i=0;i<periodic.size();i++)
	   {
		   if(periodic[i]==  card)
		   {
				 periodic.erase(periodic.begin()+i);
				 break;
		   }
	   }

		for(int i=0;i<onHold.size();i++)
	   {
		   if(onHold[i]==  card)
		   {
				 onHold.erase(onHold.begin()+i);
				 break;
		   }
	   }

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

 Battlefield::~Battlefield()
{
	delete score;
}

