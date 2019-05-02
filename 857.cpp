#include<bits/stdc++.h>
using namespace std;
int sum[123456]={};
int main(){
	ios::sync_with_stdio();
	cin.tie(0);
	int x,n,q;cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>x;
		sum[i]=sum[i-1]^x;
	}
	while(q--){
		int l,r;cin>>l>>r;
		cout<<(sum[r]^sum[l-1])<<endl;
	}
}