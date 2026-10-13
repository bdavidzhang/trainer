#include <bits/stdc++.h>
using namespace std;
int main(){
    int h,w; cin>>h>>w;
    vector<string> g(h); for(auto&s:g) cin>>s;
    const double INF=1e18, ARC=acos(-1.0)*2.5;
    // H[i][j]: midpoint of top side of cell (i,j) (i in 0..h); V[i][j]: midpoint of left side of cell (i,j) (j in 0..w)
    vector<vector<double>> H(h+1,vector<double>(w,INF)), V(h,vector<double>(w+1,INF));
    H[0][0]=5; V[0][0]=5;
    auto rel=[](double&a,double b){ if(b<a) a=b; };
    for(int i=0;i<=h;i++) for(int j=0;j<=w;j++){
        if(j<w && H[i][j]<INF){
            if(j+1<w) rel(H[i][j+1],H[i][j]+10);
            if(i<h) rel(V[i][j+1],H[i][j]+(g[i][j]=='O'?ARC:10.0));
        }
        if(i<h && V[i][j]<INF){
            if(i+1<h) rel(V[i+1][j],V[i][j]+10);
            if(j<w) rel(H[i+1][j],V[i][j]+(g[i][j]=='O'?ARC:10.0));
        }
    }
    printf("%.10f\n",min(H[h][w-1],V[h-1][w])+5);
}
