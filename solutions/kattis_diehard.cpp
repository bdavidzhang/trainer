#include <bits/stdc++.h>
using namespace std;
int main(){
    int d[3][6];
    for(auto&r:d) for(int&x:r) cin>>x;
    auto ok=[&](int a,int b){
        int w=0,l=0;
        for(int i=0;i<6;i++) for(int j=0;j<6;j++){ if(d[a][i]>d[b][j]) w++; else if(d[a][i]<d[b][j]) l++; }
        return w+l>0 && w>=l;
    };
    for(int i=0;i<3;i++){
        bool g=true;
        for(int j=0;j<3;j++) if(j!=i && !ok(i,j)) g=false;
        if(g){ cout<<i+1<<"\n"; return 0; }
    }
    cout<<"No dice\n";
}
