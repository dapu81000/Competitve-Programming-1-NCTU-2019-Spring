#include<bits/stdc++.h>
using namespace std;
int arr[123456],b[123456<<2];
int gcd(int a,int b){
	if(!b) return a;
	return gcd(b,a%b);
}
void up(int idx){
	b[idx]=gcd(b[idx<<1],b[idx<<1|1]);
}
void build(int l,int r,int idx){
	if(l==r){
		b[idx]=arr[l];
		return;
	}
	int m=(l+r)>>1;
	build(l,m,idx<<1);
	build(m+1,r,idx<<1|1);
	up(idx);
}
void update(int l,int r,int x,int val,int idx){
	if(l==r){
		b[idx]=val;
		return;
	}
	int m=(l+r)>>1;
	if(x<=m) update(l,m,x,val,idx<<1);
	else	 update(m+1,r,x,val,idx<<1|1);
	up(idx);
}
int query(int l,int r,int ql,int qr,int idx){
	if(ql<=l && r<=qr) return b[idx];
	int m=(l+r)>>1,res1=0,res2=0;
	if(ql<=m) res1=query(l,m,ql,qr,idx<<1);
	if(m< qr) res2=query(m+1,r,ql,qr,idx<<1|1);
	if(!res1) return res2;
	if(!res2) return res1;
	return gcd(res1,res2);
}
int main(){
	ios::sync_with_stdio();
	cin.tie(0);
	int t;cin>>t;
	while(t--){
		int n,q;cin>>n>>q;
		fill(arr,arr+n+1,1);
		build(1,n,1);
		while(q--){
			int cmd,x,y;cin>>cmd>>x>>y;
			if(cmd==1){
				update(1,n,x,y,1);
			}else{
				int l=x,r=n;
				while(l<r){
					int m=(l+r)>>1;
					if(query(1,n,x,m,1)>y) l=m+1;
					else				   r=m;
				}
				if(l==n && query(1,n,x,n,1)>y) cout<<"DOYA!\n";
				else cout<<l<<endl;
			}
		}
	}
}