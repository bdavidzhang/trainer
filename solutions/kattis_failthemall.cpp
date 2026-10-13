#include <bits/stdc++.h>
using namespace std;
int n,k; vector<string> a;
// key[q]: -1 unknown, 0 F, 1 T
bool propagate(vector<int>& key,int q,int v){
    vector<pair<int,int>> st; st.push_back({q,v});
    if(key[q]!=-1) return key[q]==v;
    key[q]=v;
    while(!st.empty()){
        auto [x,val]=st.back(); st.pop_back();
        char c=val?'T':'F';
        for(int s=0;s<n;s++) if(a[s][x]==c){
            for(int y=0;y<k;y++) if(y!=x&&a[s][y]!='X'){
                int w=(a[s][y]=='T')?0:1; // key must differ from the student's answer
                if(key[y]==-1){ key[y]=w; st.push_back({y,w}); }
                else if(key[y]!=w) return false;
            }
        }
    }
    return true;
}
int main(){
    cin>>n>>k; a.resize(n); for(auto&s:a) cin>>s;
    vector<int> key(k,-1);
    for(int q=0;q<k;q++){
        if(key[q]!=-1) continue;
        vector<int> t=key;
        if(propagate(t,q,0)){ key=t; continue; }
        t=key;
        if(propagate(t,q,1)){ key=t; continue; }
        puts("-1"); return 0;
    }
    string r; for(int q=0;q<k;q++) r+=key[q]?'T':'F';
    cout<<r<<"\n";
}
