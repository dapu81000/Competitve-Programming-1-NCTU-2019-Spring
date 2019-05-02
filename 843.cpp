#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
int32_t main(){
	ios::sync_with_stdio();
	cin.tie(0);
	int n,m,x,y,q;cin>>n>>m>>q;
	int tot=0;
	map<int,int> mp;
	mp[1e9+7]=0;
	mp[0]=1e9+7;
	while(q--){
		cin>>x>>y;
		x=min(x,n);
		y=min(y,m);
		if(x<=0 || y<=0){cout<<"QAQ\n";continue;}
		int res=0,pre=x,prey=0;
		auto it=mp.lower_bound(x);
//		for(map<int,int>::iterator itt=mp.begin();itt!=mp.end();itt++)
//			cout<<itt->first<<' '<<itt->second<<endl;
		if(mp.size()==2) res+=x*y;
		else{
			while(it->second<=y || it->first==0){
				int xx=it->first,yy=it->second;
//				cout<<xx<<' '<<yy<<endl;
				if(!xx){
					res+=pre*(y-prey);
					break;
				}else if(!yy){
					prey=0;it--;
					continue;
				}else{
					auto tmp=it--;
					if(xx<=x && yy<=y){
						if(xx!=x || yy!=y) mp.erase(tmp);
					}
					res+=((pre-xx)<=0?0:(pre-xx))*(y-prey);
					pre=(pre-xx)>=0?xx:x;
					prey=yy;
				}
			}
			if(it->second>y && it->first<pre && it->first) res+=(y-prey)*(pre-it->first); 
		}
		if(res) mp[x]=y,cout<<res<<endl;
		else cout<<"QAQ\n";
		tot+=res;
	}
	cout<<n*m-tot<<endl;
	return 0;
}