#include<bits/stdc++.h>

using namespace std;


int main()
	{
		
		int n;
		cin>>n;
		int arr[3];
		for(int i=0;i<3;i++)
			{cin>>arr[i];}
		sort(arr,arr+3);
		int brr[n+1];
		brr[0]=0;
		int a,b,c;
		for(int i=1;i<=n;i++)
			{ a=-1;b=-1;c=-1;
				if(i>=arr[0])
					a=brr[i-arr[0]];
				if(i>=arr[1])
					b=brr[i-arr[1]];
				if(i>=arr[2])
					c=brr[i-arr[2]];
				if(a==-1 && b==-1 && c==-1)
					{brr[i]=-1;}
				else
					brr[i]=1+max(max(a,b),c);		
			}
		cout<<brr[n];
		return 0;
	}