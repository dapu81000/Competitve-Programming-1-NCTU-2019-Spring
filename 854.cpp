#include<bits/stdc++.h>
using namespace std;
#define int long long
int32_t main(){
	ios::sync_with_stdio();
	cin.tie(0);
	int n;cin>>n;
	while(n--){
		int a,p;cin>>a>>p;
		int cnt=p-2,res=1;
		while(cnt){
			if(cnt&1) res=res*a,res%=p;
			a*=a;a%=p;
			cnt>>=1;
		}
		cout<<res<<endl;
	}
}