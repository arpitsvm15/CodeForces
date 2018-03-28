#include<bits/stdc++.h>
#include<sys/time.h>
using namespace std;


int main()
	{	string s;
		cin>>s;
		int n;
		
		int dp[s.length()];
		dp[0]=0;
		for(int k=1;k<s.size();k++)
			{
				if(s[k-1]==s[k])
					dp[k]=dp[k-1]+1;
				else
					dp[k]=dp[k-1];
			}
		cin>>n;
		int b,e;
		for(int i=0;i<n;i++)
			{cin>>b;
			cin>>e;
			cout<<(dp[e-1]-dp[b-1])<<endl;
			}	

			return 0;
	}		