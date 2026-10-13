#include <bits/stdc++.h>
using namespace std;
int main(){
    int R,C; cin>>R>>C; vector<string> g(R); for(auto&r:g)cin>>r;
    for(int c=0;c<C;c++){
        int fr=R-1;
        for(int r=R-1;r>=0;r--){
            if(g[r][c]=='#')fr=r-1;
            else if(g[r][c]=='a'){g[r][c]='.';g[fr][c]='a';fr--;}
        }
    }
    for(auto&r:g)cout<<r<<"\n";
}
