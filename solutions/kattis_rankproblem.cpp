#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,m;cin>>n>>m;vector<int>r(n);iota(r.begin(),r.end(),1);
    while(m--){string a,b;cin>>a>>b;int x=stoi(a.substr(1)),y=stoi(b.substr(1));
        int px=find(r.begin(),r.end(),x)-r.begin(),py=find(r.begin(),r.end(),y)-r.begin();
        if(px>py){r.erase(r.begin()+py);r.insert(r.begin()+px,y);}}
    for(int i=0;i<n;i++)printf("%sT%d",i?" ":"",r[i]);puts("");
}
