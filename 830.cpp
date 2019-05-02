#include<bits/stdc++.h>
using namespace std;
#define pii pair<double,double>
#define ff first
#define ss second
#define double long double
double dist(pii a,pii b){
	return ((a.ff-b.ff)*(a.ff-b.ff)+(a.ss-b.ss)*(a.ss-b.ss));
}
int main(){
	ios::sync_with_stdio();
	cin.tie(0);
	pii p[3];
	while(cin>>p[0].ff>>p[0].ss){
		for(int i=1;i<3;i++) cin>>p[i].ff>>p[i].ss;
		double dis[3];
		int pdis[3];
		for(int i=0;i<3;i++) pdis[i]=i,dis[i]=dist(p[i],p[(i+1)%3]);
		for(int i=0;i<3;i++){
			for(int j=i+1;j<3;j++){
				if(dis[i]>dis[j]){
					swap(dis[i],dis[j]);
					swap(pdis[i],pdis[j]);
				}
			}
		}
		pii ppp;
		ppp.ff=(p[pdis[2]].ff+p[(pdis[2]+1)%3].ff)/2.0;
		ppp.ss=(p[pdis[2]].ss+p[(pdis[2]+1)%3].ss)/2.0;
		if(dis[2]>=4.0*dist(ppp,p[(pdis[2]+2)%3])){
			cout<<fixed<<setprecision(6)<<ppp.ff<<' '<<ppp.ss<<' '<<sqrt(dis[2])/2.0<<endl;
			continue;
		}
		pii pp;
		double up=0,down=0;
		for(int i=0;i<3;i++){
			up+=(p[i].ff*p[i].ff+p[i].ss*p[i].ss)*p[(i+1)%3].ss;
			up-=(p[i].ff*p[i].ff+p[i].ss*p[i].ss)*p[(i+2)%3].ss;
		}
		for(int i=0;i<3;i++){
			down+=(p[i].ff*p[(i+1)%3].ss);
			down-=(p[i].ff*p[(i+2)%3].ss);
		}
		pp.ff=up/2.0/down;
		up=0;
		for(int i=0;i<3;i++){
			up+=(p[i].ff*p[i].ff+p[i].ss*p[i].ss)*p[(i+2)%3].ff;
			up-=(p[i].ff*p[i].ff+p[i].ss*p[i].ss)*p[(i+1)%3].ff;
		}
		pp.ss=up/2.0/down;
		cout<<fixed<<setprecision(6)<<pp.ff<<' '<<pp.ss<<' '<<sqrt(dist(pp,p[0]))<<endl;
	}
}