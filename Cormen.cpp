#include<bits/stdc++.h>
#include<sys/time.h>
using namespace std;


int main()
	{
		int n,k;
		cin>>n>>k;
		int arr[n];
		for(int i=0;i<n;i++)
			{cin>>arr[i];}
		int brr[n];
		brr[0]=arr[0]+k;
		for(int i=1;i<n;i++)
			{brr[i]=arr[i]+arr[i-1];}
		int count=0;
		for(int i=0;i<n;i++)
			{
				if(i<n-1 && brr[i]<k)
					{brr[i+1]+=k-brr[i];arr[i]+=k-brr[i];count+=k-brr[i];brr[i]=k;}
				else if(brr[i]<k)
					{arr[i]+=k-brr[i];count+=k-brr[i];brr[i]=k;}
			}
			cout<<count<<endl;
		for(int i=0;i<n;i++)
			{cout<<(arr[i])<<' ';}
	}