#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define ll long long
struct bigN{
	const int base=1e9,width=9;
	vector<ll> num;
	int sz=0;
	bigN(string st){
		num.clear();sz=0;
		int st_sz=st.size();
		int ptr=0;
		while(st[ptr]=='0' && ptr<st_sz-1) ptr++;
		for(int i=st_sz-1;i>=ptr;i-=width){
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
	void mul(bigN x){
		if(x.sz==1 && x.num[0]==0){
			num.clear();
			num.push_back(0);
			sz=1;
			return;
		}
		vector<ll> res;
		int nowsz=0;
		ll carry=0;
		for(int i=0;i<x.sz;i++){
			for(int j=0;j<sz;j++){
				if(nowsz>j+i){
					res[j+i]+=(carry+num[j]*x.num[i]);
					carry=res[j+i]/base;
					res[j+i]%=base;
				}else{
					nowsz++;
					res.push_back(carry+num[j]*x.num[i]);
					carry=res[j+i]/base;
					res[j+i]%=base;
				}
			}
			int ptr=i+sz;
			while(carry){
				if(ptr>=nowsz){
					nowsz++;
					res.push_back(carry);
				}else res[ptr]+=carry;
				
				carry=res[ptr]/base;
				res[ptr]%=base;
				ptr++;
			}
		}
		num.clear();
		num=res;
		sz=max(nowsz,sz);
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
	while(cin>>st){
		bigN ans=bigN("0");
		char pre='+';int sz=st.size();
		string cur="";
		for(int i=0;i<sz;i++){
			if(st[i]=='+' || st[i]=='*'){
				if(pre=='+') ans.add(bigN(cur));
				else		 ans.mul(bigN(cur));
				pre=st[i];
				cur="";
			}else cur+=st[i];
		}
		if(cur!="")
			if(pre=='+') ans.add(bigN(cur));
			else	 	 ans.mul(bigN(cur));
		ans.print();
	}
}