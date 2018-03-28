#include <bits/stdc++.h>
#define LL unsigned long long
const long infn =1e9;
using namespace std;
long min(long a,long b)
    {
   
    return a<b?a:b;
    }
long findways(int n)
    {
    long dp[n+1];
    fill_n(dp,n+1,0);
    for(int i=1;i<=n;i++)
        {long a=infn,b=infn,c=infn;
         if(i>=1)
             a=dp[i-1];
         if(i>=3)
             b=dp[i-3];
         if(i>=5)
             c=dp[i-5];
         dp[i]=1+min(a,min(b,c));
         
        }
    return dp[n];
    }
int equal(vector <int> arr) {

    int low=1000;
    for(int i=0;i<arr.size();i++)
        {if(arr[i]<low)
        low=arr[i];
        
        }
    long least=0,temp=0;
    long count=0;
    for(int i=0;i<arr.size();i++)
        { 
            while(abs(arr[i]-low)>=5)
            {arr[i]-=5;count++;}
        
        }
    least=2*arr.size();
    for(long i=low;i>low-5;i--)
        {
         for(int j=0;j<arr.size();j++)
                 { 
                   temp+=findways(arr[j]-i);
        
                 }
        if(temp<least)
            least=temp;
        temp=0;
        }
    count+=least;
  
    return (int)count;
    
    // Complete this function
}

int main() {
    int t;
    cin >> t;
    for(int a0 = 0; a0 < t; a0++){
        int n;
        cin >> n;
        vector<int> arr(n);
        for(int arr_i = 0; arr_i < n; arr_i++){
           cin >> arr[arr_i];
        }
        int result = equal(arr);
        cout << result << endl;
    }
    return 0;
}