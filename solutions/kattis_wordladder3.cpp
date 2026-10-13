#include <bits/stdc++.h>
using namespace std;
// grid snake: rows are even indices of B, traversed along A alternately; odd index of B used as connector
static vector<string> grid(const vector<string>& A,const vector<string>& B,size_t need){
    vector<string> res;
    for(size_t j=0;2*j<B.size() && res.size()<need;j++){
        const string& b=B[2*j];
        if(j%2==0) for(size_t i=0;i<A.size();i++) res.push_back(A[i]+b);
        else for(size_t i=A.size();i-->0;) res.push_back(A[i]+b);
        if(2*j+1<B.size()){
            const string& a=(j%2==0)?A.back():A.front();
            res.push_back(a+B[2*j+1]);
        }
    }
    return res;
}
int main(){
    int n; scanf("%d",&n);
    vector<string> P2;
    for(int i=0;i<26;i++){
        string w; w+=char('a'+i); w+=char('a'+i); P2.push_back(w);
        if(i<25){ string v; v+=char('a'+i); v+=char('a'+i+1); P2.push_back(v);}    
    }
    vector<string> P4=grid(P2,P2,100000);
    vector<string> P6=grid(P4,P2,n);
    for(int i=0;i<n;i++) puts(P6[i].c_str());
}
