#include<bits/stdc++.h>

using namespace std;

int main()
	{
		int arr[]={1,2,3,1,3,4,4,4,4,4,4,4,4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
		unordered_map<int,int> mp;
		int mxcnt=0;
		for(int i=0;i<sizeof(arr)/sizeof(int);i++)
			{
				mp[arr[i]]++;
				if(mp[arr[i]]>mxcnt)
					mxcnt=mp[arr[i]];
			}
		cout<<"Max count is	"<<mxcnt<<endl;	

	}
