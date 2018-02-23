#include<bits/stdc++.h>

using namespace std;


int main()
	{
		srand(time(NULL));
		int n,m;
		cin>>n>>m;
		int arr[m];
		for(int i=0;i<m;i++)
			{cin>>arr[i];}
		int diff=m-n;
		sort(arr,arr+m);
		int i=0,j=diff;
		int min=INT_MAX,temp;
		while(i<=diff)
			{
			temp=arr[m-1-j]-arr[i];
			if(temp<min)
				min=temp;
			
			i++;
			j--;
			}
		cout<<min;	
	}