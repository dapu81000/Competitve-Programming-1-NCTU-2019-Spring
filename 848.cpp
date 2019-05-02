#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
vector<pii> sky;
int32_t main(){
	ios::sync_with_stdio();
	cin.tie(0);
	int n;
	cin>>n;
	for(int i=0;i<n;i++){
		int x,h,w;cin>>x>>h>>w;
		sky.push_back(make_pair(x,-h));
		sky.push_back(make_pair(x+w,h));
	}
	sort(sky.begin(),sky.end());
	multiset<int> height;
	int pre_x;
	int area=0,len=0;
	for(int i=0;i<2*n;i++){
		int x=sky[i].first,h=sky[i].second;
		if(height.empty()){
			height.insert(-h);
			len+=-h;
			pre_x=x;
			continue;
		}
		if(h<0){
			int cur_h=*height.rbegin();
			height.insert(-h);
			if(-h>cur_h){
				len+=(x-pre_x);
				len+=(-h-cur_h);
				area+=(cur_h)*(x-pre_x);
				pre_x=x;
			}
		}else{
			height.erase(height.find(h));
			if(height.empty()){
				len+=h;
				len+=(x-pre_x);
				area+=h*(x-pre_x);
				continue;
			}
			int cur_h=*height.rbegin();
			if(cur_h<=h){
				len+=(x-pre_x);
				len+=(h-cur_h);
				area+=h*(x-pre_x);
				pre_x=x;
			}
		}
	}
	cout<<len<<' '<<area<<endl;
}