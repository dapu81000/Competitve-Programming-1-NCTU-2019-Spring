#include<bits/stdc++.h>
using namespace std;
#define int long long
int arr[123456],n,k;
bool check(int val){
	int cnt=0,cur=0;
	for(int i=1;i<=n;i++){
		if(arr[i]>val) return false;
		cur+=arr[i];
		if(cur>val){
			cnt++;
			cur=arr[i];
		}
	}
	return cnt<k;
}
int32_t main(){
	ios::sync_with_stdio();
	cin.tie(0);
	int t;cin>>t;
	while(t--){
		cin>>n>>k;
		for(int i=1;i<=n;i++) cin>>arr[i];
		int l=0,r=1e15;
		while(l<r){
			int m=(l+r)>>1;
			if(check(m)) r=m;
			else		 l=m+1;
		}
		cout<<l<<endl;
	}
}