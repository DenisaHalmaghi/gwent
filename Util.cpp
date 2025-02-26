//---------------------------------------------------------------------------

#pragma hdrstop

#include "Util.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

Util::Util(int winner)
{
	this->winner=winner;
}
vector<int> Util::split(UnicodeString string,UnicodeString delimiter)
{
		int stringLength=string.Length();
		vector<int> elements;
		int prev=1;

		for(int i=prev;i<=stringLength;i++)
		{
			if(delimiter==string[i])
			{
				UnicodeString sub=string.SubString( prev,  i-prev);
				elements.push_back( StrToInt(sub));
				prev=i+1;
			}
		}


		return  elements;
}

UnicodeString Util::join(vector<UnicodeString> strings,UnicodeString token )
{
	UnicodeString returnedValue="";
	for(int i=0;i<strings.size();i++)
	{
	   returnedValue+=strings[i]+token;
	}

	return returnedValue;
}

UnicodeString Util::join(vector<int> ints,UnicodeString token )
{
	UnicodeString returnedValue="";
	for(int i=0;i<ints.size();i++)
	{
	   returnedValue+=IntToStr(ints[i])+token;
	}

	return returnedValue;
}

UnicodeString Util::join(vector<pair<int,int>> ints,UnicodeString token )
{
	UnicodeString returnedValue="";
	for(int i=0;i<ints.size();i++)
	{


		pair<int,int> current= ints[i];
			for(int j=0;j<current.second;j++)
			{
				returnedValue+=IntToStr(current.first)+token;

			}
	}

	return returnedValue;
}

vector<int> Util::desfaPairs(vector <pair<int,int>>perechi)
{
	vector<int> ints;
	for(int i=0;i<perechi.size();i++)
	{
		pair<int,int> current= perechi[i];
		for(int j=0;j<current.second;j++)
		{
			ints.push_back(current.first);
		}
	}
	return ints;
}

int Util::stergeIndex(vector<int>& container,int index)
{
	 for(int i=0;i<container.size();i++)
	 {
		 if(container[i]==index)
		 {
			container.erase(container.begin()+i);
			return i;
         }
     }
}

int Util::randomNumber(int max)
{
	return abs(rand()%max);
}
