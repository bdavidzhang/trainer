#include <bits/stdc++.h>
using namespace std;
map<string,string> par;
string ord(int n){ string s=to_string(n); int m=n%100; if(m>=11&&m<=13)return s+"th"; if(n%10==1)return s+"st"; if(n%10==2)return s+"nd"; if(n%10==3)return s+"rd"; return s+"th"; }
int main(){
    int t,p; cin>>t>>p;
    for(int i=0;i<t;i++){ string s; int d; cin>>s>>d; while(d--){string x;cin>>x;par[x]=s;} }
    while(p--){
        string a,b; cin>>a>>b;
        map<string,int> da; { string x=a; int d=0; while(true){ da[x]=d; auto it=par.find(x); if(it==par.end())break; x=it->second; d++; } }
        string x=b; int n=0; while(!da.count(x)){ x=par[x]; n++; }
        int m=da[x];
        auto desc=[&](const string&child,const string&anc,int k){
            string rel; if(k==1)rel="child"; else { for(int i=0;i<k-2;i++)rel+="great "; rel+="grandchild"; }
            cout<<child<<" is the "<<rel<<" of "<<anc<<"\n"; };
        if(m==0) desc(b,a,n);
        else if(n==0) desc(a,b,m);
        else if(m==n){ if(m==1) cout<<a<<" and "<<b<<" are siblings\n"; else cout<<a<<" and "<<b<<" are "<<ord(m-1)<<" cousins\n"; }
        else { int lo=min(m,n),df=abs(m-n); cout<<a<<" and "<<b<<" are "<<ord(lo-1)<<" cousins, "<<df<<(df==1?" time":" times")<<" removed\n"; }
    }
}
