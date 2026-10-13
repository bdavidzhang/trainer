#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,m; scanf("%d %d",&n,&m); vector<int> a(m); for(auto&v:a)scanf("%d",&v);
    string st(n+1,0); st[n]=1;
    unordered_set<string> layer; layer.insert(st);
    for(int d=0;d<m;d++){
        int A=a[d]; unsigned lim=(A>=31)?0xFFFFFFFFu:((1u<<(A+1))-1);
        unordered_set<string> nxt;
        for(const string&s:layer){
            int c1=s[1]; vector<int> parts; for(int z=2;z<=n;z++)for(int t=0;t<s[z];t++)parts.push_back(z);
            string base(n+1,0); base[1]=c1;
            unordered_map<string,unsigned> cur; cur[base]=1;
            for(int z:parts){
                unordered_map<string,unsigned> nw; nw.reserve(cur.size()*2);
                for(auto&kv:cur){ unsigned mk=kv.second;
                    for(int b=0;2*b<=z;b++){
                        unsigned nm=((mk<<b)|(mk<<(z-b)))&lim; if(!nm)continue;
                        string k=kv.first; if(b==0)k[z]++; else {k[b]++;k[z-b]++;}
                        nw[k]|=nm;
                    }
                }
                cur.swap(nw);
            }
            int lo=max(0,A-c1);
            for(auto&kv:cur){ unsigned mk=kv.second>>lo; if(mk) nxt.insert(kv.first); }
        }
        layer.swap(nxt);
    }
    int best=0; for(const string&s:layer)best=max(best,(int)s[1]);
    printf("%d\n",best);
}
