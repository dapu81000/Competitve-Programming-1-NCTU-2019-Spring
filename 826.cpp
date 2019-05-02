#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long
bool used[1234][1234];
int n,m;
int cal(int x,int y){
	int ans=0,miny=0,minx=0;
	x=min(x,n);
	y=min(y,m);
	for(int i=x;i>minx;i--){
		if(miny>=y) break;
		for(int j=y;j>miny;j--){
			if(used[i][j]){
				miny=j;
				break;
			}
			ans++;
			used[i][j]=true;
		}
	}
	return ans;
}
int32_t main(){
	ios::sync_with_stdio();
	cin.tie(0);
	memset(used,false,sizeof used);
	int q,tot=0;
	cin>>n>>m>>q;
	for(int i=0;i<q;i++){
		int x,y;cin>>x>>y;
		int res=cal(x,y);
		if(res==0) cout<<"QAQ\n";
		else cout<<res<<endl;
		tot+=res;
	}
	cout<<n*m-tot<<endl;
	return 0;
}