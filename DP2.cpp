#include<bits/stdc++.h>

using namespace std;


int main()
	{
		
		int n,sum;
		cin>>n>>sum;
		if(sum==0 && n>1)
			{cout<<"-1"<<'\t'<<"-1"<<endl;return 0;}
		int tsum=sum,digit=0;
		while(tsum)
			{tsum/=10;digit++;}
		
		if(n<digit || 9*n<sum)
			{cout<<"-1"<<'\t'<<"-1"<<endl;return 0;}
		
		
		int arr[n][sum+1];
		memset(arr,0,sizeof(int)*(sum+1)*(n));
		arr[0][0]=0;
		for(int m=1;m<=sum;m++)
			arr[0][m]=1;
		int l=n-1;
		for(int k=2;k<=sum;k++)
			{	
				if(arr[l][k-1]<9)
					{arr[l][k]=arr[l][k-1]+1;
					
					}
				else
					{k--;
					for(int f=k;f<=sum;f++)	
						{arr[l][f]=9;}
					l--;
					}	

			}	
		
		
		for(int k=0;k<n;k++)
			{
				cout<<arr[k][sum];
			}
			cout<<endl;
		int x[n];
		memset(x,0,sizeof(int)*n);
		int c=0;
		while(sum)
			{if(sum>=9)
				{x[n-1-c]=9;sum-=9;}
			else
				{x[n-1-c]=sum;sum=0;}	
			c++;
			}
		for(int k=0;k<n;k++)
			{
				cout<<x[n-1-k];
			}
			cout<<endl;
		return 0;
	}