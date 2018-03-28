#include<bits/stdc++.h>
#include<sys/time.h>
using namespace std;

int Sum(int arr[],int s,int e)
	{if(e<s)
		return 0;
	int sum=0;	
	for(int j=s;j<=e;j++)
		{sum+=arr[j];}
	return sum;		
	}


int main()
	{
		int n;
		cin>>n;
		int arr[n];
		for(int i=0;i<n;i++)
			{cin>>arr[i];}
		int i=1,j=n-2,res=0;
		int s1=arr[0],s3=arr[n-1],s2=Sum(arr,0,n-1)-s1-s3;
		
		int k=1,l=n-2;
		while(l>k)	
			{
			if(s1==s2 && s2==s3)
				{res++;
				if((arr[k]==0 || arr[l]==0) && k<l && l>k)
					{int c1=0,c2=0;
					while(arr[k]==0 && k<l)
						{c1++;k++;}
					k-=c1;
					while(arr[l]==0 && l>k)
						{c2++;l--;}
					res+=(c1+c2)*2;
					}

				break;
				}
			if(s2<=s1 || s2<=s3 || s1==s3)
				break;	
			if(s1<s3)
				{s1+=arr[k];s2-=arr[k];k++;}
			else 
				{
					s3+=arr[l];s2-=arr[l];l--;

				}
			}		
		cout<<res<<endl;
		
	}