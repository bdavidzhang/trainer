#include <bits/stdc++.h>
using namespace std;
int main(){
    int W,K,C;cin>>W>>K>>C;
    vector<bitset<512>> f(K+1),pre(K+1);
    for(int k=1;k<=K;k++){
        if(k<=W)f[k][k]=1;
        if(k-C>=1){
            // k-1 real wishes plus whatever a conjured genie of rank <= k-C yields
            bitset<512> t=pre[k-C];
            for(int w=0;w+k-1<=W;w++)if(t[w])f[k][w+k-1]=1;
        }
        pre[k]=pre[k-1]|f[k];
    }
    puts(f[K][W]?"yes":"no");
}
