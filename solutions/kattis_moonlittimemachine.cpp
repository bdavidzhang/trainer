#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; cin>>n;
    vector<string> v(n);
    for(auto&s:v)cin>>s;
    auto ph=[](int d)->string{
        if(d==0)return "New";
        if(d<=4)return "Crescent";
        if(d<=8)return "Quarter";
        if(d<=13)return "Gibbous";
        if(d==14)return "Full";
        if(d<=19)return "Gibbous";
        if(d<=22)return "Quarter";
        return "Crescent";
    };
    for(int d=1;d<=28;d++){
        bool ok=true;
        for(int i=0;i<n&&ok;i++) if(ph((d*(i+1))%28)!=v[i]) ok=false;
        if(ok){printf("%d\n",d);return 0;}
    }
}
