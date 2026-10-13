#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
static int nxt[1000005][27];
static int fl[1000005];
static ull val[1000005];
int main(){
    int n,m,k;
    string line;
    getline(cin,line);
    sscanf(line.c_str(),"%d %d %d",&n,&m,&k);
    vector<int> endNode(n);
    int cnt=1;
    auto id=[](char c){return c==' '?26:c-'a';};
    for(int i=0;i<n;i++){
        getline(cin,line);
        while(!line.empty()&&(line.back()=='\r'||line.back()=='\n'))line.pop_back();
        int cur=0;
        for(char c:line){int x=id(c);if(!nxt[cur][x])nxt[cur][x]=cnt++;cur=nxt[cur][x];}
        endNode[i]=cur;
    }
    mt19937_64 rng(0x9e3779b97f4a7c15ULL^(ull)chrono::steady_clock::now().time_since_epoch().count());
    vector<ull> W(n,0);
    for(int i=0;i<m;i++){
        getline(cin,line);
        int u,v;sscanf(line.c_str(),"%d %d",&u,&v);u--;v--;
        ull r=rng()|1;
        W[u]+=r;W[v]-=r;
    }
    for(int i=0;i<n;i++)val[endNode[i]]+=W[i];
    vector<int> q;q.reserve(cnt);
    for(int c=0;c<27;c++)if(nxt[0][c])q.push_back(nxt[0][c]);
    for(size_t h=0;h<q.size();h++){
        int u=q[h];
        val[u]+=val[fl[u]];
        for(int c=0;c<27;c++){
            int v=nxt[u][c];
            if(v){fl[v]=nxt[fl[u]][c];q.push_back(v);}
            else nxt[u][c]=nxt[fl[u]][c];
        }
    }
    string out;
    for(int i=0;i<k;i++){
        getline(cin,line);
        while(!line.empty()&&(line.back()=='\r'||line.back()=='\n'))line.pop_back();
        int cur=0;ull h=0;
        for(char c:line){cur=nxt[cur][id(c)];h+=val[cur];}
        out+= h==0?"yes\n":"no\n";
    }
    fputs(out.c_str(),stdout);
}
