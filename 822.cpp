#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define INF 1e18
#define int long long
bitset<10000001> bs;
int32_t main(){
	ios_base::sync_with_stdio();
	cin.tie(0);
	int t;cin>>t;
	while(t--){
		int n,l,r,x;cin>>n>>l>>r;
		for(int i=0;i<n;i++){
			cin>>x;
			if(x-l<n) bs[x-l]=true;
		}
		int ans=INF;

		for(int i=0;i<=min(r-l,n-1);i++){
			if(!bs[i]){
				ans=l+i;break;
			}
		}

		if(ans==INF){
			if(r-l+1>n) cout<<l+n<<endl;
			else cout<<"^v^\n";
		}
		else cout<<ans<<endl;
		bs.reset();
	}
}