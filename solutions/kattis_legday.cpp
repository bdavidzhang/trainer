#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; cin>>n; vector<int> t(n);
    for(int i=0;i<n;i++){ string s; cin>>s;
        if(s.find("rest")!=string::npos) t[i]=0; else if(s.find("leg")!=string::npos) t[i]=1; else t[i]=2; }
    // U+1F634 SLEEPING FACE, U+1F9B5 LEG, U+1F4AA FLEXED BICEPS
    const char* g[3]={"\xF0\x9F\x98\xB4","\xF0\x9F\xA6\xB5","\xF0\x9F\x92\xAA"};
    for(int w=0;w<5;w++){
        string line=to_string(w+1)+" ";
        for(int d=w*7;d<min(31,w*7+7);d++) line+=g[t[d%n]];
        cout<<line<<"\n";
    }
}
