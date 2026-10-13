#include <bits/stdc++.h>
using namespace std;
int adj[26][26], col[26], cnt[3], am[26], cm[3];
vector<int> L;
bool go(int i){
    if(i==(int)L.size()) return true;
    int v=L[i];
    for(int c=0;c<3;c++){
        if(cnt[c]>=6) continue;
        if(i==0&&c>0) break;
        if(am[v]&cm[c]) continue;
        col[v]=c;cnt[c]++;cm[c]|=1<<v;
        if(go(i+1)) return true;
        col[v]=-1;cnt[c]--;cm[c]&=~(1<<v);
    }
    return false;
}
int main(){
    int n;cin>>n;bool bad=false;bool used[26]={};
    for(int i=0;i<n;i++){string s;cin>>s;
        for(int a=0;a<3;a++){used[s[a]-'a']=1;for(int b=a+1;b<3;b++){ if(s[a]==s[b])bad=true; adj[s[a]-'a'][s[b]-'a']=adj[s[b]-'a'][s[a]-'a']=1;}}}
    for(int i=0;i<26;i++){col[i]=-1;if(used[i])L.push_back(i);}
    if(bad||L.size()>18){puts("0");return 0;}
    // order: by degree descending helps pruning
    int deg[26]={};for(int i=0;i<26;i++)for(int j=0;j<26;j++)deg[i]+=adj[i][j];
    sort(L.begin(),L.end(),[&](int a,int b){return deg[a]>deg[b];});
    for(int i=0;i<26;i++)for(int j=0;j<26;j++)if(adj[i][j])am[i]|=1<<j;
    if(!go(0)){puts("0");return 0;}
    string d[3];
    for(int v:L)d[col[v]]+=char('a'+v);
    for(int i=0;i<26;i++)if(!used[i]){for(int c=0;c<3;c++)if(d[c].size()<6){d[c]+=char('a'+i);break;}}
    cout<<d[0]<<" "<<d[1]<<" "<<d[2]<<"\n";
}
