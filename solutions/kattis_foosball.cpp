#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;cin>>n;
    vector<string> nm(n);
    for(auto&s:nm)cin>>s;
    string pts;cin>>pts;
    // team t: 0 white, 1 black. off[t], def[t], first[t] (earlier arrival), second[t]
    int off[2]={0,1},def[2]={2,3};
    int fst[2]={0,1},snd[2]={2,3};
    deque<int> q;
    for(int i=4;i<n;i++)q.push_back(i);
    int best=0;
    vector<pair<int,int>> res;
    int cur=0,curTeam=-1;
    pair<int,int> curNames;
    auto flush=[&](){
        if(cur==0)return;
        if(cur>best){best=cur;res.clear();}
        if(cur==best)res.push_back(curNames);
    };
    for(char ch:pts){
        int w=(ch=='W')?0:1,l=1-w;
        if(w==curTeam)cur++;
        else{
            flush();
            curTeam=w;cur=1;curNames={fst[w],snd[w]};
        }
        swap(off[w],def[w]);
        int out=def[l];
        def[l]=off[l];
        q.push_back(out);
        int in=q.front();q.pop_front();
        off[l]=in;
        fst[l]=def[l];snd[l]=in;
    }
    flush();
    for(auto&p:res)cout<<nm[p.first]<<" "<<nm[p.second]<<"\n";
}
