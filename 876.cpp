#include<bits/stdc++.h>
using namespace std;
#define int long long
int powmod(int a,int b,int p){
    int res=1;
    while(b){
        if(b&1) res=res*a,res%=p;
        a=a*a;a%=p;
        b>>=1;
    }
    return res;
}
int32_t main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;cin>>t;
    while(t--){
        int k;cin>>k;
        if(k==1) cout<<k<<endl;
        else cout<<(powmod(2,k+1,998244353)-(k+2)+998244353)%998244353<<endl;
    }
}