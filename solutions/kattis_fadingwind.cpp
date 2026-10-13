#include <bits/stdc++.h>
using namespace std;
int main(){
    long long h,k,v,s; cin>>h>>k>>v>>s;
    long long dist=0;
    while(h>0){
        v+=s; v-=max(1LL,v/10);
        if(v>=k) h++;
        if(v>0&&v<k){ h--; if(h==0) v=0; }
        if(v<=0){h=0;v=0;}
        dist+=v;
        if(s>0) s--;
    }
    cout<<dist<<endl;
}
