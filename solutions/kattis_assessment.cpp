#include <bits/stdc++.h>
using namespace std;
int main(){
    int N,W;scanf("%d %d",&N,&W);
    int a=(2*N+1)/3; if(a>N-1)a=N-1; if(a<1)a=1;
    int k=N-a;
    // antichain A first: deviation 1+t, quality t (t=0..a-1): mutually incomparable
    for(int t=0;t<a;t++){
        int dev=1+t;
        int w=(W<=5000)?W+dev:W-dev;
        printf("%d %d\n",w,t);
    }
    // chain C: deviation 0, quality a+s : each dominates all of A, and they form a chain
    for(int s=0;s<k;s++)printf("%d %d\n",W,a+s);
}
