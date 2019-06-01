#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
int b[123456];
int bit[123456];
int lowbit(int x){return x&-x;}
int findmax(int x){
	int ans=0;
	while(x){
		ans=max(ans,bit[x]);
		x-=lowbit(x);
	}
	return ans;
}
void add(int x,int val,int n){
	while(x<=n){
		bit[x]=max(bit[x],val);
		x+=lowbit(x);
	}
}
int ans[123456];
int main(){
	ios::sync_with_stdio();
	cin.tie(0);
	int t;cin>>t;
	while(t--){
		memset(bit,0,sizeof bit);
		memset(ans,0,sizeof ans);
		int n;cin>>n;
		vector<pii> v;
		for(int i=0;i<n;i++){
			int x,y;cin>>x>>y;
			v.push_back(make_pair(x,y));
		}
		sort(v.begin(),v.end());
		vector<int> arr;

		for(int i=0;i<n;i++){
			arr.push_back(v[i].second);
			b[i]=v[i].second;
		}
		sort(b,b+n);
		for(int i=0;i<n;i++){
			arr[i]=lower_bound(b,b+n,arr[i])-b+1;
			ans[i]=findmax(arr[i])+1;
			add(arr[i],ans[i],n);
		}
		cout<<*max_element(ans,ans+n)<<endl;
	}
}