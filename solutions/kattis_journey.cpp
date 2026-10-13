#include <bits/stdc++.h>
using namespace std;
static char *buf; static size_t bp=0,bl=0;
static inline void skipws(){while(bp<bl&&(unsigned char)buf[bp]<=' ')bp++;}
static inline int readInt(){skipws();int x=0;while(bp<bl&&buf[bp]>='0'&&buf[bp]<='9'){x=x*10+buf[bp]-'0';bp++;}return x;}
static inline int readTime(){
    skipws();int d=0;while(buf[bp]!='d'){d=d*10+buf[bp]-'0';bp++;}bp++;
    int h=(buf[bp]-'0')*10+buf[bp+1]-'0';bp+=3;
    int m=(buf[bp]-'0')*10+buf[bp+1]-'0';bp+=2;
    return d*1440+h*60+m;
}
int main(){
    {
        size_t cap=1<<26;buf=(char*)malloc(cap);
        size_t r;
        while((r=fread(buf+bl,1,cap-bl,stdin))>0){bl+=r;if(bl==cap){cap*=2;buf=(char*)realloc(buf,cap);}}
    }
    int n=readInt();
    vector<int> S(n),T(n),D(n),A(n);
    unordered_map<string,int> id;id.reserve(2*n+10);
    auto readName=[&]()->int{
        skipws();size_t st=bp;while(bp<bl&&(unsigned char)buf[bp]>' ')bp++;
        string s(buf+st,bp-st);
        auto it=id.find(s);
        if(it!=id.end())return it->second;
        int k=id.size();id.emplace(move(s),k);return k;
    };
    for(int i=0;i<n;i++){
        S[i]=readName();D[i]=readTime();T[i]=readName();A[i]=readTime();
    }
    int m=readInt();
    vector<int> f(m);for(auto&x:f)x=readInt()-1;
    int V=id.size();
    int dest=T[f[m-1]];
    const int MAXT=367*1440;
    // sort flights by dep descending
    vector<int> cntT(MAXT+2,0);
    for(int i=0;i<n;i++)cntT[D[i]]++;
    // descending: position start for time t = number of flights with dep > t
    vector<int> startT(MAXT+2,0);
    {int acc=0;for(int t=MAXT;t>=0;t--){startT[t]=acc;acc+=cntT[t];}}
    vector<int> order(n);
    for(int i=0;i<n;i++)order[startT[D[i]]++]=i;
    vector<int> off(V+1,0);
    for(int i=0;i<n;i++)off[S[i]+1]++;
    for(int v=0;v<V;v++)off[v+1]+=off[v];
    vector<int> fillp(off.begin(),off.begin()+V);
    const int INF=INT_MAX;
    vector<int> sd(n),m1(n),m1i(n),m2(n);
    auto query=[&](int a,int Tm,int ex)->int{
        if(a==dest)return Tm;
        int lo=off[a],hi=fillp[a]; // entries dep descending; count with dep>=Tm
        int base=lo;
        while(lo<hi){int mid=(lo+hi)/2;if(sd[mid]>=Tm)lo=mid+1;else hi=mid;}
        if(lo==base)return INF;
        int p=lo-1;
        if(m1i[p]==ex)return m2[p];
        return m1[p];
    };
    for(int k=0;k<n;k++){
        int i=order[k];
        int b=(T[i]==dest)?A[i]:query(T[i],A[i],-1);
        int a=S[i];
        int p=fillp[a]++;
        sd[p]=D[i];
        if(p==off[a]){m1[p]=b;m1i[p]=i;m2[p]=INF;}
        else{
            if(b<m1[p-1]){m1[p]=b;m1i[p]=i;m2[p]=m1[p-1];}
            else{m1[p]=m1[p-1];m1i[p]=m1i[p-1];m2[p]=min(m2[p-1],b);}
        }
    }
    int planned=A[f[m-1]];
    long long ans=0;bool stranded=false;
    for(int k=0;k<m;k++){
        int i=f[k];
        int q=query(S[i],D[i],i);
        if(q==INF){stranded=true;break;}
        ans=max(ans,(long long)q-planned);
    }
    if(stranded)puts("stranded");else printf("%lld\n",ans);
}
