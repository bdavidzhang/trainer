#include <bits/stdc++.h>
using namespace std;
int n;vector<int> m;int best=0;
void go(int i,int used,int c){
    if(c+(n-i)<=best)return;
    if(i==n){best=c;return;}
    if(!(used&m[i]))go(i+1,used|m[i],c+1);
    go(i+1,used,c);
}
int main(){int p,t;cin>>p>>t;
    for(int i=0;i<t;i++){string s;cin>>s;int k=0;bool ok=true;
        for(char c:s){int b=c-'A';if(b>=p||(k>>b&1))ok=false;else k|=1<<b;}
        if(ok)m.push_back(k);}
    n=m.size();go(0,0,0);cout<<best<<"\n";}
