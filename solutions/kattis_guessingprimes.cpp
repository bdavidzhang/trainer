#include <bits/stdc++.h>
using namespace std;
// Wordle on 5-digit primes. Precompute the full feedback table (8363^2 bytes), then build a
// greedy decision tree lazily (guess maximising the number of distinct feedback classes,
// ties broken towards guesses that are still candidates). Verified offline: depth <= 6.
static vector<int> pr; static int M;
static vector<unsigned char> fb; // fb[g*M+s]
static int feedback(int g,int s){
    int gd[5],sd[5],res[5]={0,0,0,0,0},cnt[10]={0};
    for(int i=4;i>=0;i--){ gd[i]=g%10; g/=10; sd[i]=s%10; s/=10; }
    for(int i=0;i<5;i++){ if(gd[i]==sd[i]) res[i]=2; else cnt[sd[i]]++; }
    for(int i=0;i<5;i++) if(res[i]==0 && cnt[gd[i]]>0){ res[i]=1; cnt[gd[i]]--; }
    int c=0; for(int i=0;i<5;i++) c=c*3+res[i];
    return c;
}
struct Node{ vector<int> cand; int guess=-1; map<int,int> ch; };
static vector<Node> nodes;
static void choose(int id){
    Node& nd=nodes[id];
    if(nd.guess>=0) return;
    if(nd.cand.size()<=2){ nd.guess=nd.cand[0]; return; }
    vector<char> isc(M,0); for(int c:nd.cand) isc[c]=1;
    int bestG=-1; long long bestScore=-1;
    int stamp[243]; memset(stamp,-1,sizeof(stamp));
    for(int g=0;g<M;g++){
        const unsigned char* row=&fb[(size_t)g*M];
        int k=0;
        for(int c:nd.cand){ int f=row[c]; if(stamp[f]!=g){ stamp[f]=g; k++; } }
        long long sc=2LL*k+isc[g];
        if(sc>bestScore){ bestScore=sc; bestG=g; }
        if(k==(int)nd.cand.size() && isc[g]) break;
    }
    nd.guess=bestG;
}
static int child(int id,int f){
    auto it=nodes[id].ch.find(f);
    if(it!=nodes[id].ch.end()) return it->second;
    Node nn; int g=nodes[id].guess;
    for(int c:nodes[id].cand) if(fb[(size_t)g*M+c]==f) nn.cand.push_back(c);
    nodes.push_back(nn);
    int nid=nodes.size()-1;
    nodes[id].ch[f]=nid;
    return nid;
}
int main(int argc,char**argv){
    vector<char> comp(100000,0);
    for(int i=2;i<100000;i++){ if(!comp[i]){ if(i>=10000) pr.push_back(i); for(long long j=(long long)i*i;j<100000;j+=i) comp[j]=1; } }
    M=pr.size();
    fb.resize((size_t)M*M);
    for(int g=0;g<M;g++) for(int s=0;s<M;s++) fb[(size_t)g*M+s]=feedback(pr[g],pr[s]);
    nodes.reserve(20000);
    Node root; root.cand.resize(M); iota(root.cand.begin(),root.cand.end(),0);
    nodes.push_back(root);
    if(argc>1){ // offline self-test over all secrets
        int worst=0; long long tot=0;
        for(int s=0;s<M;s++){
            int id=0,q=0;
            while(true){ choose(id); q++; int f=fb[(size_t)nodes[id].guess*M+s]; if(f==242) break; id=child(id,f); }
            worst=max(worst,q); tot+=q;
        }
        printf("worst %d avg %.3f nodes %zu\n",worst,(double)tot/M,nodes.size());
        return 0;
    }
    int n; if(!(cin>>n)) return 0;
    while(n--){
        int id=0;
        while(true){
            choose(id);
            cout<<pr[nodes[id].guess]<<endl;
            string r; if(!(cin>>r)) return 0;
            int f=0; for(char ch:r) f=f*3+(ch=='g'?2:ch=='y'?1:0);
            if(f==242) break;
            id=child(id,f);
            if(nodes[id].cand.empty()) return 0;
        }
    }
}
