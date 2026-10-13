#include <bits/stdc++.h>
using namespace std;
// pluses needed to build value v from a fresh "1" via doubling (d+) and increment (1+)
static int cost(long long v){int b=63-__builtin_clzll(v);return b+__builtin_popcountll(v)-1;}
int main(){int n;scanf("%d",&n);vector<long long>x(n),t(n);for(auto&a:x)scanf("%lld",&a);
    long long P=0; // pluses executed after entry i is finished
    for(int i=n-1;i>=0;i--){t[i]=x[i]+P;P+=cost(t[i]);}
    string s;
    for(int i=0;i<n;i++){long long v=t[i];int b=63-__builtin_clzll(v);
        s+='1';
        for(int k=b-1;k>=0;k--){s+="d+";if(v>>k&1)s+="1+";}
    }
    puts(s.c_str());}
