#include<bits/stdc++.h>
using namespace std;
#define ll unsigned long long 
const int maxn= 1e5;
const unsigned int M = 1000000007;
int main()
	{
		int t,k;
		ll dp[maxn];
		fill_n(dp,maxn,0);
		cin>>t>>k;
		for(int j=1;j<k;j++)
			{
			dp[j]=1;	
			}
			dp[k]=2;
		for(int i=k+1;i<=maxn;i++)
			{
			dp[i]=(dp[i-1]+dp[i-k])%M;			
			}
		for(int i=1;i<=maxn;i++)	
			{
			dp[i]=(dp[i]+(dp[i-1]));

			}
		while(t--)
			{	int a,b;
				ll sum=0;
				cin>>a>>b;
				sum=(dp[b]-dp[a-1])%M;
				cout<<sum<<endl;	

			}

	}