#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long u64;
static char buf[1<<25];
size_t blen=0,bpos=0;
int gc(){ if(bpos==blen){blen=fread(buf,1,sizeof buf,stdin);bpos=0;if(!blen)return -1;} return buf[bpos++]; }
int main(){
    auto readInt=[&]()->int{int c=gc();while(c!=-1&&(c<'0'||c>'9'))c=gc();int v=0;while(c>='0'&&c<='9'){v=v*10+c-'0';c=gc();}return v;};
    auto readKey=[&](string&s)->u64{int c=gc();while(c!=-1&&!isalpha(c))c=gc();u64 k=0;s.clear();
        while(c!=-1&&isalpha(c)){int v=(c>='a')?(c-'a'+1):(c-'A'+27);k=k*64+v;s+=(char)c;c=gc();}return k;};
    int n=readInt();
    unordered_map<u64,int> id; id.reserve(8192);
    vector<string> names; vector<u64> rnd;
    mt19937_64 rng(0x9e3779b97f4a7c15ULL^(u64)chrono::steady_clock::now().time_since_epoch().count());
    vector<u64> H(n,0); vector<int> sz(n);
    vector<int> dbl; // doubleton count per set
    unordered_map<u64,int> byHash; byHash.reserve(n*2);
    unordered_map<u64,int> byRnd;
    string s;
    for(int i=0;i<n;i++){
        int k=readInt();sz[i]=k;
        int a[2]={-1,-1};
        for(int j=0;j<k;j++){
            u64 key=readKey(s);
            auto it=id.find(key);int v;
            if(it==id.end()){v=names.size();id[key]=v;names.push_back(s);u64 r=rng();rnd.push_back(r);byRnd[r]=v;dbl.push_back(0);}
            else v=it->second;
            H[i]+=rnd[v];
            if(j<2)a[j]=v;
        }
        if(k==2){dbl[a[0]]++;dbl[a[1]]++;}
        byHash[H[i]]=i;
    }
    int K=names.size();
    vector<char> usedR(n,0),usedS(K,0);
    vector<int> L(K,0),U(K,0);
    vector<vector<int>> bySize(K+2);
    for(int i=0;i<n;i++)bySize[sz[i]].push_back(i);
    deque<int> q; u64 h=0; int pos=0,cnt=0;
    // pos = index of the next region to be placed
    while(true){
        int w=q.size();
        bool moved=false;
        // 1) drop front
        if(w>=2){
            u64 h2=h-rnd[q.front()];
            auto it=byHash.find(h2);
            if(it!=byHash.end()&&!usedR[it->second]&&sz[it->second]==w-1){
                U[q.front()]=pos;q.pop_front();h=h2;usedR[it->second]=1;cnt++;pos++;moved=true;
            }
        }
        if(moved)continue;
        // 2) add new
        if(w>=1&&w+1<=K){
            for(int r:bySize[w+1]){
                if(usedR[r])continue;
                auto it=byRnd.find(H[r]-h);
                if(it==byRnd.end()||usedS[it->second])continue;
                int y=it->second;
                usedS[y]=1;L[y]=pos;q.push_back(y);h=H[r];usedR[r]=1;cnt++;pos++;moved=true;break;
            }
        }
        if(moved)continue;
        // 3) swap (drop front, add new)
        {
            u64 hb=w?h-rnd[q.front()]:0;
            for(int r: bySize[max(w,1)]){
                if(usedR[r])continue;
                auto it=byRnd.find(H[r]-hb);
                if(it==byRnd.end()||usedS[it->second])continue;
                int y=it->second;
                if(w<=1&&dbl[y]>1)continue; // must be a chain endpoint
                if(w){U[q.front()]=pos;q.pop_front();}
                usedS[y]=1;L[y]=pos;q.push_back(y);h=H[r];usedR[r]=1;cnt++;pos++;moved=true;break;
            }
        }
        if(!moved)break;
    }
    bool ok=(cnt==n)&&q.size()==1;
    if(ok)U[q.front()]=pos;
    for(int v=0;v<K;v++)if(!usedS[v])ok=false;
    if(!ok){puts("IMPOSSIBLE");return 0;}
    string out;
    for(int v=0;v<K;v++){out+=names[v];out+=' ';out+=to_string(L[v]);out+=' ';out+=to_string(U[v]);out+='\n';}
    fputs(out.c_str(),stdout);
}
