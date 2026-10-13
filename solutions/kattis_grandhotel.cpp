#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// Grow the tree room by room: weighted A* from the new room through cells that touch no tree cell,
// stopping at a cell that touches exactly one non-room tree cell; then remove chords from the path.
static const int S=400;
struct C{int x[4];};
static inline ll key(const C&c){return ((ll)(c.x[0]*S+c.x[1])*S+c.x[2])*S+c.x[3];}
static inline C unkey(ll k){C c;for(int i=3;i>=0;i--){c.x[i]=k%S;k/=S;}return c;}
static inline int dist(const C&a,const C&b){int d=0;for(int i=0;i<4;i++)d+=abs(a.x[i]-b.x[i]);return d;}
struct HS{ // open addressing set of keys with a 1-bit flag (room)
    vector<ll> t;ll mask;
    HS(int lg):t(1<<lg,-1),mask((1<<lg)-1){}
    static inline unsigned long long h(ll k){unsigned long long z=k*0x9E3779B97F4A7C15ULL;return z^(z>>29);}
    int get(ll k)const{ // 0 none, 1 cell, 2 room
        ll i=h(k)&mask;
        while(t[i]!=-1){if((t[i]>>1)==k)return 1+(int)(t[i]&1);i=(i+1)&mask;}
        return 0;
    }
    void put(ll k,int room){ll i=h(k)&mask;while(t[i]!=-1){if((t[i]>>1)==k)return;i=(i+1)&mask;}t[i]=k*2+room;}
};
int n;vector<C> R;vector<char> conn;
HS tree(22);
vector<ll> treeCells;vector<char> treeIsRoom;
unordered_map<ll,int> ball;
void addCell(ll k,int room){if(tree.get(k))return;tree.put(k,room);treeCells.push_back(k);treeIsRoom.push_back(room);}
struct Node{ll k;int par;int g;};
// returns path keys from room r to the final cell (attach cell, or target room in first mode)
vector<ll> search(int r,int firstTarget){
    C T;
    if(firstTarget>=0)T=R[firstTarget];
    else{
        int bd=INT_MAX;ll bk=-1;
        for(size_t i=0;i<treeCells.size();i++)if(!treeIsRoom[i]){
            int d=dist(unkey(treeCells[i]),R[r]);
            if(d<bd){bd=d;bk=treeCells[i];}
        }
        T=unkey(bk);
    }
    ll tk=key(T);
    vector<Node> nodes;
    unordered_set<ll> vis;vis.reserve(1<<16);
    typedef tuple<int,int,int> E; // f,h,id
    priority_queue<E,vector<E>,greater<E>> pq;
    const int W=3;
    nodes.push_back({key(R[r]),-1,0});vis.insert(key(R[r]));
    pq.push(E(W*dist(R[r],T),dist(R[r],T),0));
    int fin=-1;
    while(!pq.empty()&&fin<0){
        int id=get<2>(pq.top());pq.pop();
        C u=unkey(nodes[id].k);int g=nodes[id].g;
        for(int d=0;d<4&&fin<0;d++)for(int s=-1;s<=1;s+=2){
            C c=u;c.x[d]+=s;
            if(c.x[d]<0||c.x[d]>=S)continue;
            ll ck=key(c);
            if(vis.count(ck))continue;
            auto it=ball.find(ck);
            if(firstTarget>=0){
                if(ck==tk){nodes.push_back({ck,id,g+1});fin=nodes.size()-1;break;}
                if(it!=ball.end()&&it->second!=r&&it->second!=firstTarget)continue;
            }else{
                if(tree.get(ck))continue;
                if(it!=ball.end()&&it->second!=r&&!conn[it->second])continue;
                int cnt=0;bool bad=false;
                for(int e=0;e<4;e++)for(int q=-1;q<=1;q+=2){
                    C w=c;w.x[e]+=q;
                    if(w.x[e]<0||w.x[e]>=S)continue;
                    int v=tree.get(key(w));
                    if(v==2)bad=true;
                    if(v)cnt++;
                }
                if(bad||cnt>=2)continue;
                if(cnt==1){nodes.push_back({ck,id,g+1});fin=nodes.size()-1;break;}
            }
            vis.insert(ck);
            nodes.push_back({ck,id,g+1});
            int h=dist(c,T);
            pq.push(E(g+1+W*h,h,(int)nodes.size()-1));
        }
    }
    vector<ll> p;
    if(fin<0)return p;
    for(int i=fin;i>=0;i=nodes[i].par)p.push_back(nodes[i].k);
    reverse(p.begin(),p.end());
    // remove chords: from each kept cell jump to the furthest path cell adjacent to it
    unordered_map<ll,int> idx;idx.reserve(p.size()*2);
    for(size_t i=0;i<p.size();i++)idx[p[i]]=i;
    vector<ll> q;
    size_t i=0;
    while(true){
        q.push_back(p[i]);
        if(i+1==p.size())break;
        C u=unkey(p[i]);size_t best=i+1;
        for(int d=0;d<4;d++)for(int s=-1;s<=1;s+=2){
            C c=u;c.x[d]+=s;if(c.x[d]<0||c.x[d]>=S)continue;
            auto it=idx.find(key(c));
            if(it!=idx.end()&&(size_t)it->second>best)best=it->second;
        }
        i=best;
    }
    return q;
}
int main(){
    scanf("%d",&n);R.resize(n);conn.assign(n,0);
    for(auto&c:R)scanf("%d %d %d %d",&c.x[0],&c.x[1],&c.x[2],&c.x[3]);
    for(int i=0;i<n;i++){
        C c;
        for(int a=-3;a<=3;a++)for(int b=-3;b<=3;b++)for(int d=-3;d<=3;d++)for(int e=-3;e<=3;e++){
            if(abs(a)+abs(b)+abs(d)+abs(e)>3)continue;
            c.x[0]=R[i].x[0]+a;c.x[1]=R[i].x[1]+b;c.x[2]=R[i].x[2]+d;c.x[3]=R[i].x[3]+e;
            bool ok=true;for(int j=0;j<4;j++)if(c.x[j]<0||c.x[j]>=S)ok=false;
            if(ok)ball[key(c)]=i;
        }
    }
    // order: start with the closest pair partner of room 0, then nearest-to-connected (Prim-like on rooms)
    int j0=1;for(int j=1;j<n;j++)if(dist(R[0],R[j])<dist(R[0],R[j0]))j0=j;
    vector<ll> p=search(0,j0);
    for(size_t i=0;i<p.size();i++)addCell(p[i],(i==0||i+1==p.size())?1:0);
    conn[0]=conn[j0]=1;
    vector<int> md(n,INT_MAX);
    for(int j=0;j<n;j++)if(!conn[j])md[j]=min(dist(R[j],R[0]),dist(R[j],R[j0]));
    for(int it=2;it<n;it++){
        int r=-1;for(int j=0;j<n;j++)if(!conn[j]&&(r<0||md[j]<md[r]))r=j;
        p=search(r,-1);
        for(size_t i=0;i<p.size();i++)addCell(p[i],i==0?1:0);
        conn[r]=1;
        for(int j=0;j<n;j++)if(!conn[j])md[j]=min(md[j],dist(R[j],R[r]));
    }
    string out;out.reserve(treeCells.size()*18);
    out+=to_string(treeCells.size())+"\n";
    for(ll k:treeCells){C c=unkey(k);char buf[64];int l=snprintf(buf,64,"%d %d %d %d\n",c.x[0],c.x[1],c.x[2],c.x[3]);out.append(buf,l);}
    fwrite(out.data(),1,out.size(),stdout);
}
