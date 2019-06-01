#include<bits/stdc++.h>
using namespace std;
int arr[33];
bitset<3000001> bit;
int main(){
	ios::sync_with_stdio();
	cin.tie(0);
	int t;cin>>t;
	while(t--){
		bit.reset();
		bit[0]=true;
		int n,k,sum=0;cin>>n>>k;
		for(int i=0;i<n;i++){
			cin>>arr[i];
			bit=(bit|(bit<<arr[i]));
			sum+=arr[i];
		}
		int val=((sum*100)/(100+k)*k)/100;
		if((sum*100)%(100+k) || !bit[val]) cout<<"No\n";
		else cout<<"Yes\n";
	}
}