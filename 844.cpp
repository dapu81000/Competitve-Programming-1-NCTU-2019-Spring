#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio();
	cin.tie(0);
	int n,k;cin>>n>>k;
	int arr[20],cnt=0;
	for(int i=0;i<n;i++) cin>>arr[i];
	while(next_permutation(arr,arr+n) && cnt<k){
		for(int i=0;i<n;i++){
			if(i) cout<<' ';
			cout<<arr[i];
		}
		cout<<endl;
		cnt++;
	}
	if(!cnt) cout<<"hello world!\n";
	return 0;
}