#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio();
	cin.tie(0);
	int t;cin>>t;
	while(t--){
		int r,c,x,y;cin>>r>>c>>x>>y;
		if((x-1)^(r-x)^(y-1)^(c-y)) cout<<"Taberu\n";
		else cout<<"Tabehen\n";
	}
}