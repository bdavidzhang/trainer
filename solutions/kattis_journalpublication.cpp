#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n; cin>>n;
    vector<string> res; string prev="";
    bool ok=true;
    for(int i=0;i<n;i++){
        int p; cin>>p; string best; bool has=false;
        for(int j=0;j<p;j++){
            string w; cin>>w;
            if(w>=prev&&(!has||w<best)){best=w;has=true;}
        }
        if(!has) ok=false;
        else { prev=best; res.push_back(best); }
    }
    if(!ok){ cout<<"impossible\n"; return 0; }
    for(auto&w:res) cout<<w<<"\n";
}
