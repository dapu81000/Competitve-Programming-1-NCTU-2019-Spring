#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
int arr[1234567];
int main(){
	ios::sync_with_stdio();
	cin.tie(0);
	int t;cin>>t;
	while(t--){
		int n;cin>>n;
		for(int i=1;i<=n;i++) cin>>arr[i];
		stack<int> st;
		st.push(arr[n]);
		int ans=1;
		for(int i=n-1;i>=1;i--){
			while(!st.empty() && st.top()<arr[i]) st.pop();
			st.push(arr[i]);
			ans=max(ans,(int)st.size());
		}
		cout<<ans<<endl;
	}
}