#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
struct node{
	int cnt;
	node *l,*r;
	node(){
		cnt=1;
		l=r=NULL;
	}
};
node *cur;
int main(){
	ios::sync_with_stdio();
	cin.tie(0);
	cur=new node();
	int n,maxsize=0;cin>>n;
	while(n--){
		string st;cin>>st;
		int sz=st.size();
		maxsize=max(maxsize,sz);
		node *tmp=cur;
		for(int i=0;i<sz;i++){
			if(st[i]=='0'){
				if(tmp->l==NULL)
					tmp->l=new node();
				else tmp->l->cnt++;
				tmp=tmp->l;
			}else{
				if(tmp->r==NULL)
					tmp->r=new node();
				else tmp->r->cnt++;
				tmp=tmp->r;
			}
		}
	}
	int q;cin>>q;
	while(q--){
		string st;cin>>st;
		int ans=-1,sz=st.size();
//		if(sz>maxsize){cout<<0<<endl;continue;}
		node *tmp=cur;
		for(int i=0;i<sz;i++){
			if(st[i]=='0'){
				if(tmp->l==NULL){
					ans=0;break;
				}
				tmp=tmp->l;
			}else{
				if(tmp->r==NULL){
					ans=0;break;
				}
				tmp=tmp->r;
			}
		}
		cout<<(ans==-1?tmp->cnt:ans)<<endl;
	}
}