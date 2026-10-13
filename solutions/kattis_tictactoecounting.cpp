#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int b[9]; bool vis[19683]; ll wx[19683],wo[19683];
int L[8][3]={{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
int win(){ for(auto&l:L) if(b[l[0]]&&b[l[0]]==b[l[1]]&&b[l[1]]==b[l[2]])return b[l[0]]; return 0; }
int code(){int c=0;for(int i=0;i<9;i++)c=c*3+b[i];return c;}
void dfs(int turn){
    int c=code(); if(vis[c])return; vis[c]=true;
    int w=win();
    if(w==1){wx[c]=1;return;} if(w==2){wo[c]=1;return;}
    for(int i=0;i<9;i++)if(!b[i]){
        b[i]=turn; dfs(3-turn); int d=code(); b[i]=0;
        wx[c]+=wx[d]; wo[c]+=wo[d];
    }
}
int main(){
    dfs(1);
    int t; scanf("%d",&t); char s[20];
    while(t--){
        scanf("%s",s); int c=0; for(int i=0;i<9;i++)c=c*3+(s[i]=='X'?1:s[i]=='O'?2:0);
        if(!vis[c])puts("-1 -1"); else printf("%lld %lld\n",wx[c],wo[c]);
    }
}
