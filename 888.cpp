#include<bits/stdc++.h>
using namespace std;
int arr[10000001];
int b[10000001<<2];
inline void up(int idx){
	b[idx]=b[idx<<1]+b[idx<<1|1];
}
inline void build(int l,int r,int idx){
	if(l==r){
		b[idx]=arr[l];
		return;
	}
	int m=(l+r)>>1;
	build(l,m,idx<<1);
	build(m+1,r,idx<<1|1);
	up(idx);
}
inline void update(int l,int r,int x,int val,int idx){
	if(l==r){
		b[idx]+=val;
		return;
	}
	int m=(l+r)>>1;
	if(x<=m) update(l,m,x,val,idx<<1);
	else	 update(m+1,r,x,val,idx<<1|1);
	up(idx);
}
inline int queryid(int l,int r,int val,int idx){
	int cur=0;
	while(l!=r){
		int m=(l+r)>>1;
		if(cur+b[idx<<1]+(m-l+1)<val){
			cur+=b[idx<<1]+(m-l+1);
			idx=idx<<1|1;
			l=m+1;
		}else{
			r=m;
			idx=idx<<1;
		}
	}
	return l;
}
int main(){
	ios::sync_with_stdio();
	cin.tie(0);
	int t;cin>>t;
	while(t--){
		int n,q;cin>>n>>q;
		fill(arr,arr+n+1,0);
		build(1,n,1);
		while(q--){
			int cmd,x;cin>>cmd>>x;
			if(cmd==1){
				arr[x]++;
				update(1,n,x,1,1);
			}else if(cmd==2){
				update(1,n,x,-arr[x],1);
				arr[x]=0;
			}else if(cmd==3){
				int ans=queryid(1,n,x,1);
				if(b[1]+n<x) cout<<"endro~!\n";
				else{
					cout<<ans<<endl;
					update(1,n,ans,-1,1);
					arr[ans]--;
				}
			}else{
				cout<<b[1]<<endl;
			}
		}
	}
}