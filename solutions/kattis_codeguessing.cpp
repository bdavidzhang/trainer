#include <bits/stdc++.h>
using namespace std;
int main(){ int p,q; string s; cin>>p>>q>>s; int c=0,ra=0,rb=0;
    for(int a=1;a<=9;a++) for(int b=a+1;b<=9;b++){
        if(a==p||a==q||b==p||b==q) continue;
        vector<pair<int,char>> v={{p,'A'},{q,'A'},{a,'B'},{b,'B'}}; sort(v.begin(),v.end());
        string t; for(auto&x:v) t+=x.second;
        if(t==s){c++;ra=a;rb=b;}
    }
    if(c==1) cout<<ra<<" "<<rb<<"\n"; else cout<<-1<<"\n"; }
