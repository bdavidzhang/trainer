#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
int main(){int r,c;scanf("%d %d",&r,&c);vector<int>a(r*c);int z=0,one=0,two=0;for(auto&x:a){scanf("%d",&x);if(x==0)z++;else if(x==1)one++;else two++;}
    int n=r*c;
    if(r==1||c==1){ // only prefix cuts
        ull best=~0ULL;
        for(int k=1;k<n;k++){int z1=0,t1=0,z2=0,t2=0;for(int i=0;i<n;i++){if(i<k){if(a[i]==0)z1++;if(a[i]==2)t1++;}else{if(a[i]==0)z2++;if(a[i]==2)t2++;}}
            ull p1=z1?0:(1ULL<<t1),p2=z2?0:(1ULL<<t2);ull d=p1>p2?p1-p2:p2-p1;best=min(best,d);}
        printf("%llu\n",best);return 0;}
    if(z>=2){puts("0");return 0;}
    if(z==1){puts(one?"1":"2");return 0;}
    int x=two/2,y=two-x;ull d=(1ULL<<y)-(1ULL<<x);printf("%llu\n",d);
}
