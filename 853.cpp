#include<bits/stdc++.h>
using namespace std;
#define int long long
const int SIZE=32768*2;
void mul(int *res,const int *f,const int *g,int sz){
	int ans[sz<<1],f0[sz],f1[sz];
	memset(ans,0,sizeof ans);
	if(sz<=4){
		for(int i=0;i<sz;i++)
			for(int j=0;j<sz;j++){
				ans[i+j]+=f[i]*g[j];
			}
		memcpy(res,ans,(sz<<1)*sizeof(int));
		return;
	}
	for(int i=0;i<sz/2;i++){
		f0[i]=f[i]+f[i+sz/2];
		f1[i]=g[i]+g[i+sz/2];
		f0[i+sz/2]=f1[i+sz/2]=0;
	}
	mul(ans+sz/2,f0,f1,sz/2);
	mul(f0,f,g,sz/2);
	mul(f1,f+sz/2,g+sz/2,sz/2);
	for(int i=0;i<sz;i++){
		ans[i]+=f0[i];
		ans[i+sz/2]-=f0[i]+f1[i];
		ans[i+sz]+=f1[i];
	}
	memcpy(res,ans,(sz<<1)*sizeof(int));
}
int a[SIZE+1]={},b[SIZE+1]={};
int32_t main(){
	ios::sync_with_stdio();
	cin.tie(0);
	a[0]=b[0]=1;
	int t,n,m,q;cin>>n>>m>>q;
	for(int i=0;i<n;i++){
		cin>>t;
		a[t]++;
	}
	for(int i=0;i<m;i++){
		cin>>t;
		b[t]++;
	}
	int res[SIZE<<1]={};
	mul(res,a,b,SIZE);
	while(q--){
		int x;cin>>x;
		if(x>=(SIZE<<1)) cout<<0<<endl;
		else cout<<res[x]<<endl;
	}
}