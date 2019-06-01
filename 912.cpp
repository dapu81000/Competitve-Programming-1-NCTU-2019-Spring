#include<bits/stdc++.h>
using namespace std;
int dp[1234][1234];
int main(){
	ios::sync_with_stdio();
	cin.tie(0);
	int t;cin>>t;
	while(t--){
		memset(dp,0x3f,sizeof dp);
		int n,m,x,y,z;cin>>n>>m>>x>>y>>z;
		string a,b;cin>>b>>a;
		for(int i=0;i<=m;i++) dp[i][0]=i*y;
		for(int i=0;i<=n;i++) dp[0][i]=i*x;
		for(int i=1;i<=m;i++){
			for(int j=1;j<=n;j++){
				if(a[i-1]==b[j-1]) dp[i][j]=dp[i-1][j-1];
				else dp[i][j]=min(dp[i-1][j]+y,min(dp[i-1][j-1]+z,dp[i][j-1]+x));
			}
		}
		cout<<dp[m][n]<<endl;
	}
}