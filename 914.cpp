#include<bits/stdc++.h>
using namespace std;
struct state{
	char cur[5][5];
	int g,last;
	state(char ch[5][5],int gg,int lt){
		for(int i=0;i<5;i++)
			for(int j=0;j<5;j++)
				cur[i][j]=ch[i][j];
		g=gg;
		last=lt;
	}
	state(){g=0;last=-1;}
};
state st,ed;
int dif(state a){
	int res=0;
	for(int i=0;i<5;i++)
		for(int j=0;j<5;j++)
			if(a.cur[i][j]!=ed.cur[i][j])
				res++;
	return res;
}
#define pii pair<int,int>
pii find_w(state a){
	for(int i=0;i<5;i++)
		for(int j=0;j<5;j++)
			if(a.cur[i][j]=='W')
				return make_pair(i,j);
	return make_pair(0,0);
}
#define psi pair<state,int>
bool operator<(psi a,psi b){
	return a.first.g+a.second>b.first.g+b.second;
}
int dir[8][2]={1,-2,2,-1,2,1,1,2,-1,2,-2,1,-2,-1,-1,-2};
bool out(int i,int j){
	return i>=5 || i<0 || j>=5 || j<0;
}
int bfs(){
	int ans=0;
	priority_queue<psi> pq;
	pq.push(make_pair(st,dif(st)));
	while(!pq.empty()){
		psi tmp=pq.top();pq.pop();
		if(tmp.second==0){
			ans=tmp.first.g;
			break;
		}
		pii w=find_w(tmp.first);
		for(int i=0;i<8;i++){
			int pi=w.first+dir[i][0],pj=w.second+dir[i][1];
			if(out(pi,pj)) continue;
			if(tmp.first.last!=-1 && i==(tmp.first.last+4)%8) continue;
			state temp=state(tmp.first.cur,tmp.first.g+1,i);
			swap(temp.cur[pi][pj],temp.cur[w.first][w.second]);
			pq.push(make_pair(temp,dif(temp)));
		}
	}
	return ans;
}
int main(){
	ios::sync_with_stdio();
	cin.tie(0);
	int t;cin>>t;
	while(t--){
		for(int i=0;i<5;i++) cin>>st.cur[i];
		for(int i=0;i<5;i++) cin>>ed.cur[i];
		st.g=0;
		st.last=-1;
		cout<<bfs()<<endl;
	}
}
/*
1
WYBBB
BBBYB
BYBBB
BBYBB
YBBBB

YWBBB
BBBYB
BYBBB
BBYBB
YBBBB
*/