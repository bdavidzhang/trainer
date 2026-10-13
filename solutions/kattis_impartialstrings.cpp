#include <bits/stdc++.h>
using namespace std;
int main(){
    int K; cin>>K;
    while(K--){
        string A,S,T; cin>>A>>S>>T;
        int idx[26]; memset(idx,-1,sizeof idx); int sg=A.size();
        for(int i=0;i<sg;i++)idx[A[i]-'a']=i;
        vector<vector<int>> go(1,vector<int>(sg,-1)); vector<int> es(1,0),et(1,0);
        auto add=[&](const string&s,vector<int>&mark){
            int c=0; for(char ch:s){int x=idx[ch-'a']; if(go[c][x]<0){go[c][x]=go.size(); go.push_back(vector<int>(sg,-1)); es.push_back(0); et.push_back(0);} c=go[c][x];}
            mark[c]=1;
        };
        add(S,es); add(T,et);
        int V=go.size(); vector<int> fail(V,0);
        queue<int> q;
        for(int x=0;x<sg;x++){ if(go[0][x]<0)go[0][x]=0; else {fail[go[0][x]]=0;q.push(go[0][x]);} }
        while(!q.empty()){
            int u=q.front();q.pop();
            es[u]|=es[fail[u]]; et[u]|=et[fail[u]];
            for(int x=0;x<sg;x++){
                int v=go[u][x];
                if(v<0||false){ go[u][x]=go[fail[u]][x]; }
                else { fail[v]=go[fail[u]][x]; q.push(v); }
            }
        }
        // note: children detection above relies on -1; nodes created have -1 for missing
        vector<int> w(V); for(int i=0;i<V;i++)w[i]=es[i]-et[i];
        vector<pair<int,int>> edges; vector<int> toRoot;
        for(int u=0;u<V;u++){
            vector<int> t(go[u]); sort(t.begin(),t.end()); t.erase(unique(t.begin(),t.end()),t.end());
            for(int v:t){ if(v==0)toRoot.push_back(u); else edges.push_back({u,v}); }
        }
        auto hasPos=[&](int sgn){
            vector<int> d(V,0);
            for(int it=0;it<=V+1;it++){
                bool ch=false;
                int mx=INT_MIN; for(int u:toRoot)mx=max(mx,d[u]);
                if(mx>d[0]){d[0]=mx;ch=true;}
                for(auto&e:edges){ int nd=d[e.first]+sgn*w[e.second]; if(nd>d[e.second]){d[e.second]=nd;ch=true;} }
                if(!ch)return false;
            }
            return true;
        };
        bool p=hasPos(1), ng=hasPos(-1);
        puts((p&&ng)?"0":"1");
    }
}
