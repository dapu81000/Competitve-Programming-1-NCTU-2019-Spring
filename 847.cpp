#include<bits/stdc++.h>
using namespace std;
bool inq[1000001]={};
int G[1000001];
struct node{
	int num;
	node *pre,*nxt;
	node(int x,node *p){
		pre=p;
		num=x;
		nxt=NULL;
	}
};
node *root,*cur;
node *head[1000001];
int main(){
	ios::sync_with_stdio();
	cin.tie(0);
	root=new node(0,NULL);
	cur=root;
	int n,q,mx;cin>>n>>q;
	head[0]=NULL;
	for(int i=1;i<=n;i++) cin>>G[i],head[i]=NULL;
	while(q--){
		int cmd;cin>>cmd;
		node *tmp,*pree;
		if(cmd==1){
			int x;cin>>x;
			if(inq[x]) cout<<"Ignore\n";
			else{
				inq[x]=true;
				if(head[G[x]]!=NULL){
					pree=head[G[x]]->pre;
					tmp=head[G[x]];
					pree->nxt=new node(x,pree);
					pree->nxt->nxt=tmp;
					tmp->pre=pree->nxt;
					head[G[x]]=pree->nxt;
				}else{
					cur->nxt=new node(x,cur);
					cur=cur->nxt;
					head[G[x]]=cur;
				}
				cout<<"Successful\n";
			}
		}else{
			tmp=root->nxt;
			if(tmp==NULL) cout<<0<<endl;
			else{
				int x=tmp->num;
				if(tmp->nxt){
					if(G[tmp->nxt->num]!=G[x]) head[G[x]]=NULL;
					else				 	   head[G[x]]=tmp->nxt;
				}else head[G[x]]=NULL;
				root->nxt=tmp->nxt;
				if(tmp->nxt) tmp->nxt->pre=root;
				if(tmp==cur) cur=root;
				delete tmp;
				inq[x]=false;
				cout<<x<<endl;
			}
		}
	}
	return 0;
}