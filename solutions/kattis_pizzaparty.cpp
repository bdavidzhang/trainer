#include <bits/stdc++.h>
using namespace std;
int main(){
    int c; string line; getline(cin,line); c=atoi(line.c_str());
    unordered_map<string,int> id; 
    auto get=[&](const string&s){auto it=id.find(s);if(it!=id.end())return it->second;int k=id.size();id[s]=k;return k;};
    vector<vector<int>> occ; // topping -> clauses where it is a premise
    vector<int> need, head; vector<char> on; vector<int> st;
    auto ens=[&](int t){if((int)occ.size()<=t){occ.resize(t+1);on.resize(t+1,0);}};
    auto turn=[&](int t){if(!on[t]){on[t]=1;st.push_back(t);}};
    for(int i=0;i<c;i++){
        getline(cin,line); istringstream ss(line); vector<string> w; string x; while(ss>>x)w.push_back(x);
        if(w.empty())continue;
        if(w[0]!="if"){int t=get(w[0]);ens(t);turn(t);continue;}
        bool isor=false; vector<int> pre; size_t j=1;
        for(;j<w.size()&&w[j]!="then";j++){ if(w[j]=="or")isor=true; else if(w[j]=="and"){} else {int t=get(w[j]);ens(t);pre.push_back(t);} }
        int h=get(w[j+1]);ens(h);
        int cl=need.size(); head.push_back(h); need.push_back(isor?1:(int)pre.size());
        for(int t:pre)occ[t].push_back(cl);
    }
    int cnt=0;
    while(!st.empty()){int t=st.back();st.pop_back();cnt++;
        for(int cl:occ[t]){ if(--need[cl]==0) turn(head[cl]); }
    }
    printf("%d\n",cnt);
}
