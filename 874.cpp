#include<bits/stdc++.h>
using namespace std;
int b[1234567<<2]={},tag[1234567<<2]={};
void up(int idx){
    b[idx]=b[idx<<1]+b[idx<<1|1];
}
void build(int l,int r,int idx){
    if(l==r){
        b[idx]=1;
        tag[idx]=0;
        return;
    }
    int m=(l+r)>>1;
    build(l,m,idx<<1);
    build(m+1,r,idx<<1|1);
    up(idx);
}
void down(int l,int r,int idx){
    if(tag[idx]==1){
        tag[idx<<1]=tag[idx<<1|1]=tag[idx];
        b[idx<<1]=b[idx<<1|1]=0;
        tag[idx]=0;
    }else if(tag[idx]==2){
        tag[idx<<1]=tag[idx<<1|1]=tag[idx];
        int m=(l+r)>>1;
        b[idx<<1]=m-l+1;
        b[idx<<1|1]=r-m;
        tag[idx]=0;
    }
}
void update(int l,int r,int ql,int qr,int req,int idx){
    if(ql<=l && r<=qr){
        tag[idx]=req;
        if(req==1) b[idx]=0;
        else b[idx]=(r-l+1);
        return;
    }
    down(l,r,idx);
    int m=(l+r)>>1;
    if(ql<=m) update(l,m,ql,qr,req,idx<<1);
    if(m< qr) update(m+1,r,ql,qr,req,idx<<1|1);
    up(idx);
}
int query(int l,int r,int ql,int qr,int idx){
    if(ql<=l && r<=qr){
        return b[idx];
    }
    down(l,r,idx);
    int m=(l+r)>>1,ans=0;
    if(ql<=m) ans+=query(l,m,ql,qr,idx<<1);
    if(m< qr) ans+=query(m+1,r,ql,qr,idx<<1|1);
    up(idx);
    return ans;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    build(0,1e6+1,1);
    int t;cin>>t;
    while(t--){
        int req,l,r;cin>>req>>l>>r;r--;
        int ans=query(0,1e6+1,l,r,1);
        if(req==1) cout<<ans<<endl;
        else cout<<(r-l+1-ans)<<endl;
        update(0,1e6+1,l,r,req,1);
    }

}