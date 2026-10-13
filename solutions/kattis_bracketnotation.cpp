#include <bits/stdc++.h>
using namespace std;
static int dg(long long x){int d=1;while(x>=10){x/=10;d++;}return d;}
int main(){
    string s;cin>>s;
    int n=s.size()/2;
    vector<int> sz(n,1),st;int id=0;
    for(char ch:s){
        if(ch=='(')st.push_back(id++);
        else{int v=st.back();st.pop_back();if(!st.empty())sz[st.back()]+=sz[v];}
    }
    vector<int> len(n,4);vector<long long> pos(n+1);
    while(true){
        pos[0]=0;for(int i=0;i<n;i++)pos[i+1]=pos[i]+len[i];
        bool ch=false;
        for(int i=0;i<n;i++){int l=dg(pos[i+1])+dg(pos[i+sz[i]])+2;if(l!=len[i]){len[i]=l;ch=true;}}
        if(!ch)break;
    }
    string out;
    for(int i=0;i<n;i++){out+=to_string(pos[i+1]);out+=',';out+=to_string(pos[i+sz[i]]);out+=':';}
    puts(out.c_str());
}
