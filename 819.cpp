#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'
struct bigN{
	const int base=1e9,width=9;
	vector<ll> num;
	int sz;
	bigN(string st){
		num.clear();sz=0;
		int st_sz=st.size(),head=0;
		while(st[head]=='0' && head<st_sz-1) head++;
		for(int i=st_sz-1;i>=head;i-=width){
			ll x=0;
			for(int j=max(0,i-width+1);j<=i;j++)
				x=x*10+(st[j]-'0');
			num.push_back(x);
		}
		sz=num.size();
	}
	void add(bigN x){
		ll carry=0;int i=0;
		for(i=0;i<x.sz || carry;i++){
			if(i<sz){
				if(i<x.sz) num[i]+=(carry+x.num[i]);
				else num[i]+=carry;
			}else{
				if(i<x.sz) num.push_back(x.num[i]+carry);
				else num.push_back(carry);
			}
			carry=num[i]/base;
			num[i]%=base;
		}
		sz=max(sz,i);
	}
	void print(){
		while(num[sz-1]==0 && sz-1>0) sz--;
		cout<<num[sz-1];
		for(int i=sz-2;i>=0;i--)
			cout<<setw(width)<<setfill('0')<<num[i];
		cout<<endl;
	}
};
int main(){
	ios::sync_with_stdio();
	cin.tie(0);
	string st;
	while(getline(cin,st)){
		bigN ans=bigN("0");
		string x;
		stringstream ss(st);
		while(ss>>x){
			bigN tmp=bigN(x);
			ans.add(tmp);
		}
		ans.print();
	}
}