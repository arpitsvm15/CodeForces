#include<bits/stdc++.h>
#include<sys/time.h>
using namespace std;
/*void PrintA(int arr[],int n)
	{
	for(int i=0;i<n;i++)
		{cout<<arr[i]<<'\t';}
		cout<<endl;	
	}*/
int main()
	{
		string s;
		cin>>s;
		size_t n=s.size();
		
		string s1="AB";
		string s2="BA";
		
	
		int arr[n-1];
		memset(arr,0,(n-1)*sizeof(int));
		int brr[n-1];
		memset(brr,0,(n-1)*sizeof(int));
		for(size_t i=0;i<n-1;i++)
			{	
			
				if(s1==s.substr(i,2))
					{arr[i]=1;}

						
				else if(s2==s.substr(i,2))
					{brr[i]=1;}
					
			}
		/*	PrintA(arr,n-1);
			PrintA(brr,n-1);*/
		int  p=0,q=0;
		while(p<n-1)
			{while(q<n-1 && arr[p])
				{if(arr[p] && brr[q] && abs(p-q)>1)
					{cout<<"YES"<<endl;return 0;}
					q++;
				}
				q=0;
				p++;
			}
			
		
		
			cout<<"NO"<<endl;

			return 0;
	}