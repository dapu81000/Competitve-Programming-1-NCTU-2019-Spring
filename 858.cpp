#include<bits/stdc++.h>
using namespace std;
#define int long long
int arr[123456],n,k;
bool check(int val){
	int cnt=0,cur_max=0,cur_len=0;
	for(int i=1;i<=n;i++){
		if(arr[i]>val) return false;
		cur_max=max(cur_max,arr[i]);
		cur_len++;
		if(cur_len*cur_max>val){
			cnt++;
			cur_max=arr[i];
			cur_len=1;
		}
	}
	return cnt<k;
}
int32_t main(){
	ios::sync_with_stdio();
	cin.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		cin>>arr[i];
	int l=0,r=1e15;
	while(l<r){
		int m=(l+r)>>1;
		if(check(m)) r=m;
		else		 l=m+1;
	}
	cout<<l<<endl;
}