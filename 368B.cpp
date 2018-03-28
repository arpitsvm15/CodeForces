#include<bits/stdc++.h>
#include<sys/time.h>
using namespace std;
int find(int ele,int arr[],int s,int e)
	{	if(s>e)
			return 0;
		sort(arr+s,arr+e+1);	
		if(binary_search(arr+s,arr+e,ele))
				return 1;	
		else	
				return 0;	
	}

int main()
	{
		int n,m,x;
		cin>>n>>m;
		int arr[n];
		int frr[100001];
		memset(frr,0,(100001)*sizeof(int));
		for(int i=0;i<n;i++)
			{cin>>arr[i];frr[arr[i]]+=1;}
		
		int dp[n+1];
		memset(dp,0,(n+1)*sizeof(int));
		dp[n]=1;
		for(int i=n-2;i>=0;i--)
			{
				int f=frr[arr[i]];
				f=1-f;
				cout<<"f  "<<f<<endl;
				dp[i+1]=dp[i+2]+f;
				cout<<"array   "<<dp[i+1]<<endl;
			}
		for(int i=0;i<m;i++)
			{cin>>x;cout<<dp[x]<<endl;}	


	}	