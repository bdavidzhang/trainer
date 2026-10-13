#include <bits/stdc++.h>
using namespace std;
typedef array<int,10> St;
map<St,bool> memo;
// returns true if the player to move (token at vertex s[9]) wins
bool win(const St&s){
    auto it=memo.find(s); if(it!=memo.end()) return it->second;
    int v=s[9]; bool w=false;
    for(int j=0;j<3&&!w;j++) if(s[v*3+j]>0){
        St t=s; t[v*3+j]--; t[9]=j;
        if(!win(t)) w=true;
    }
    return memo[s]=w;
}
int main(){
    int n; cin>>n;
    int id[26]; memset(id,-1,sizeof id); int k=0;
    int cnt[3][3]={};
    for(int i=0;i<n;i++){
        string w; cin>>w; int a=w[0]-'a', b=w.back()-'a';
        if(id[a]<0) id[a]=k++;
        if(id[b]<0) id[b]=k++;
        cnt[id[a]][id[b]]++;
    }
    int ans=0;
    for(int i=0;i<3;i++) for(int j=0;j<3;j++) if(cnt[i][j]>0){
        int c[3][3]; memcpy(c,cnt,sizeof c); c[i][j]--;
        for(int a=0;a<3;a++) c[a][a]&=1;               // paired loops cancel
        for(int a=0;a<3;a++) for(int b=a+1;b<3;b++){   // opposite edges cancel
            int m=min(c[a][b],c[b][a]); c[a][b]-=m; c[b][a]-=m;
        }
        St s; for(int a=0;a<3;a++) for(int b=0;b<3;b++) s[a*3+b]=c[a][b];
        s[9]=j;
        memo.clear();
        if(!win(s)) ans+=cnt[i][j];
    }
    printf("%d\n",ans);
}
