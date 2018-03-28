#include<bits/stdc++.h>
#include<sys/time.h>
using namespace std;


int main()
	{	
		int n,m;
		cin>>n;
		int arr[n];
		for(int i=0;i<n;i++)
			{cin>>arr[i];}
		cin>>m;
		int brr[m];
		for(int i=0;i<m;i++)
			{cin>>brr[i];}
		sort(arr,arr+n);
		sort(brr,brr+m);
		int p=0,q=0,count=0;
		while(p<n && q<m)
			{if(abs(arr[p]-brr[q])<=1)
				{count++;p++;q++;}
			else if(brr[q]>arr[p])
				{p++;}
			else
				{q++;}		
			}
		cout<<count;	
		return 0;	
	}