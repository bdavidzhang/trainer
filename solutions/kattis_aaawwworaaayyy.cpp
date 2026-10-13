#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,m,r; cin>>n>>m>>r;
    vector<string> g(n);
    for(auto&s:g)cin>>s;
    vector<int> ord(n); iota(ord.begin(),ord.end(),0); // ord[pos]=team
    int fav=r-1;
    while(true){
        int pos=-1,col=-1;
        for(int p=n-1;p>=0&&pos<0;p--){
            size_t c=g[ord[p]].find('P');
            if(c!=string::npos){pos=p;col=(int)c;}
        }
        if(pos<0)break;
        string a,b; if(!(cin>>a>>b))break;
        int team=ord[pos];
        if(b.size()>1 && b[3]=='y'){
            g[team][col]='A';
            int y=0; for(char ch:b) if(ch=='y')y++;
            int pass=y-3;
            for(int i=0;i<pass&&pos>0;i++){ swap(ord[pos],ord[pos-1]); pos--; }
        } else g[team][col]='R';
    }
    for(int p=0;p<n;p++) if(ord[p]==fav) printf("%d\n",p+1);
}
