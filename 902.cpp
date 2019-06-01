#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,N;
int x,y;
int pow2[31];
int id;
inline void find_id(int cur,int r,int c){
	if(!cur) return;
	int m=pow2[cur-1];
	if(r<=m && c<=m) find_id(cur-1,r,c);
	else if(r<=m && c>m){
		id+=m*m;
		find_id(cur-1,r,c-m);
	}else if(r>m && c<=m){
		id+=2*m*m;
		find_id(cur-1,r-m,c);
	}else{
		id+=3*m*m;
		find_id(cur-1,r-m,c-m);
	}
}
inline void find_pos(int cur,int id){
	if(!cur) return;
	int m=pow2[cur-1];
	if(m*m>=id) find_pos(cur-1,id);
	else if(2*m*m>=id){
		y+=m;
		find_pos(cur-1,id-m*m);
	}else if(3*m*m>=id){
		x+=m;
		find_pos(cur-1,id-m*m*2);
	}else{
		x+=m;
		y+=m;
		find_pos(cur-1,id-3*m*m);
	}
}
int32_t main(){
	ios::sync_with_stdio();
	cin.tie(0);
	pow2[0]=1;
	for(int i=1;i<=30;i++) pow2[i]=pow2[i-1]*2;
	int t;cin>>t;
	while(t--){
		int q;cin>>n>>q;
		while(q--){
			int cmd;cin>>cmd;
			if(cmd==1){
				int r,c;cin>>r>>c;
				id=0;
				find_id(n,r,c);
				cout<<id+1<<endl;
			}else{
				cin>>id;
				x=y=0;
				find_pos(n,id);
				cout<<x+1<<' '<<y+1<<endl;
			}
		}
	}
}