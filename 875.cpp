#include<bits/stdc++.h>
using namespace std;
string num[10]={"0","1","2","3","4","5","6","7","8","9"};
string decode(string a){
    int ptr=0,sz=a.size();
    while(a[ptr]=='0' && ptr<sz-1) ptr++;
    return a.substr(ptr,sz-ptr);
}
string add(string a,string b){
    a=decode(a),b=decode(b);
    reverse(a.begin(),a.end());
    reverse(b.begin(),b.end());
    string c="";
    int a_sz=a.size(),b_sz=b.size();
    int carry=0;
    for(int i=0;i<max(a_sz,b_sz);i++){
        int cur=0;
        if(i<a_sz) cur+=(a[i]-'0');
        if(i<b_sz) cur+=(b[i]-'0');
        cur+=carry;
        carry=cur/10;
        cur%=10;
        c+=num[cur];
    }
    if(carry) c+=num[1];
    return c;
}
string mul(string a,string b){
    a=decode(a),b=decode(b);
    reverse(a.begin(),a.end());
    reverse(b.begin(),b.end());
    int dig[123]={};
    int a_sz=a.size(),b_sz=b.size();
    int carry=0;
    for(int i=0;i<b_sz;i++){
        for(int j=0;j<a_sz;j++){
            int aa=a[j]-'0',bb=b[i]-'0';
            dig[i+j]+=aa*bb;
        }
    }
    int i=0;
    string ans="";
    for(;i<a_sz+b_sz-1;i++){
        dig[i]+=carry;
        carry=dig[i]/10;
        dig[i]%=10;
        ans+=num[dig[i]];
    }
    while(carry){
        ans+=num[carry%10];
        carry/=10;
    }
    return ans;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;cin>>t;t++;
    string str,tmp;
    while(t--){
        getline(cin,str);
        if(str.size()==0) continue;
        stringstream ss(str);
        stack<string> st;
        while(ss>>tmp){
            int sz=tmp.size();
            int pre=0;
            for(int i=0;i<sz;i++){
                if(tmp[i]=='+' || tmp[i]=='*'){
                    string c;
                    string a,b;
                    if(pre!=i){
                        a=st.top(),b=tmp.substr(pre,i-pre);st.pop();reverse(a.begin(),a.end());
                        if(tmp[i]=='+') c=add(a,b);
                        else c=mul(a,b);
                        pre=i+1;
                    }else{
                        a=st.top();st.pop();reverse(a.begin(),a.end());
                        b=st.top();st.pop();reverse(b.begin(),b.end());
                        if(tmp[i]=='+') c=add(a,b);
                        else c=mul(a,b);
                        pre=i+1;
                    }
                    st.push(c);
                }
            }
            if(pre<sz){
                string c=tmp.substr(pre,sz-pre);
                reverse(c.begin(),c.end());
                st.push(c);
            }
        }
        string ans=st.top();
        reverse(ans.begin(),ans.end());
        cout<<ans<<endl;
    }

}