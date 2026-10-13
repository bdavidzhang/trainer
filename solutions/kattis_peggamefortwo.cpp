#include <bits/stdc++.h>
using namespace std;
int v[15];
vector<array<int,3>> mv;
int id(int r,int c){return r*(r+1)/2+c;}
int go(){
    int best=INT_MIN;
    for(auto&m:mv){
        int a=m[0],b=m[1],c=m[2];
        if(v[a]&&v[b]&&!v[c]){
            int va=v[a],vb=v[b];
            v[c]=va;v[a]=0;v[b]=0;
            best=max(best,va*vb-go());
            v[a]=va;v[b]=vb;v[c]=0;
        }
    }
    return best==INT_MIN?0:best;
}
int main(){
    for(int i=0;i<15;i++)cin>>v[i];
    int dr[6]={0,0,1,-1,1,-1},dc[6]={1,-1,0,0,1,-1};
    for(int r=0;r<5;r++)for(int c=0;c<=r;c++)for(int d=0;d<6;d++){
        int r1=r+dr[d],c1=c+dc[d],r2=r+2*dr[d],c2=c+2*dc[d];
        if(r2<0||r2>=5||c2<0||c2>r2)continue;
        mv.push_back({id(r,c),id(r1,c1),id(r2,c2)});
    }
    cout<<go()<<"\n";
}
