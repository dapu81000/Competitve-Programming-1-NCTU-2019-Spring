#include<bits/stdc++.h>
using namespace std;
inline string decode(string st){
	string newone;
	int sz=st.size();
	for(int i=0;i<sz;i++){
		if(st[i]<='Z' && st[i]>='A')
			st[i]=(st[i]-'A'+'a');
		if(st[i]>='a' && st[i]<='z'){
			newone+=st[i];
		}
	}
	return newone;
}
int main(){
	ios::sync_with_stdio();
	cin.tie(0);
	string st;
	map<string,int> mp;
	vector<string> ans;
	while(getline(cin,st)){
		stringstream ss(st);
		while(ss>>st){
			st=decode(st);
			if(st.size()==0) continue;
			if(!mp[st]++){
				ans.push_back(st);
			}
		}
	}
	int sz=ans.size();
	for(int i=0;i<sz;i++){
		cout<<ans[i]<<' '<<mp[ans[i]]<<endl;
	}
}