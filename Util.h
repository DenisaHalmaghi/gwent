//---------------------------------------------------------------------------

#ifndef UtilH
#define UtilH
#include <vector>
using namespace std;

class Util{
	public:
	int winner;
    Util(int);
	static  vector<int> split(UnicodeString,UnicodeString);
	static  UnicodeString join(vector<UnicodeString>,UnicodeString );
	static  UnicodeString join(vector<int>,UnicodeString );
	static  UnicodeString join(vector <pair<int,int>>,UnicodeString );
	static  vector<int> desfaPairs(vector <pair<int,int>>);
	static  void stergeIndex(vector<int>&,int);
};
//---------------------------------------------------------------------------
#endif
