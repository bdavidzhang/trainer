#include <bits/stdc++.h>
using namespace std;
set<vector<string>> seen;
string best; bool have=false;
void go(vector<string> v){
    sort(v.begin(),v.end());
    if(!seen.insert(v).second) return;
    if(v.size()==1){
        const string&w=v[0];
        if(!have||w.size()<best.size()||(w.size()==best.size()&&w<best)){best=w;have=true;}
        return;
    }
    int n=v.size();
    for(int i=0;i<n;i++)for(int j=0;j<n;j++){
        if(i==j)continue;
        const string&s=v[i];const string&t=v[j];
        int mk=min(s.size(),t.size());
        for(int k=1;k<=mk;k++){
            if(s.compare(s.size()-k,k,t,0,k)==0){
                string c=s+t.substr(k);
                vector<string> w;
                for(int x=0;x<n;x++)if(x!=i&&x!=j)w.push_back(v[x]);
                w.push_back(c);
                go(w);
            }
        }
    }
}
int main(){
    int n;cin>>n;vector<string>v(n);for(auto&s:v)cin>>s;
    go(v);
    if(have)cout<<best<<"\n";else cout<<-1<<"\n";
}
