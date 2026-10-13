#include <bits/stdc++.h>
using namespace std;
static bool isn(char c){return isalnum((unsigned char)c)||c=='_';}
// parse all facts in a line
static vector<vector<string>> parseLine(const string&s){
    vector<vector<string>> res; size_t i=0,n=s.size();
    while(true){
        while(i<n&&!isn(s[i])) i++;
        if(i>=n) break;
        vector<string> f; size_t j=i; while(j<n&&isn(s[j])) j++;
        f.push_back(s.substr(i,j-i)); i=j;
        while(i<n&&s[i]!='(') i++;
        if(i<n) i++;
        while(i<n&&s[i]!=')'){
            if(isn(s[i])){j=i;while(j<n&&isn(s[j]))j++;f.push_back(s.substr(i,j-i));i=j;}
            else i++;
        }
        if(i<n) i++;
        res.push_back(f);
    }
    return res;
}
int main(){
    string line; map<pair<string,size_t>,vector<vector<string>>> db;
    while(getline(cin,line)){
        bool blank=true; for(char c:line) if(!isspace((unsigned char)c)) blank=false;
        if(blank) break;
        for(auto&f:parseLine(line)) db[{f[0],f.size()}].push_back(f);
    }
    while(getline(cin,line)){
        auto qs=parseLine(line);
        if(qs.empty()) continue;
        auto&q=qs[0]; int cnt=0;
        auto it=db.find({q[0],q.size()});
        if(it!=db.end()) for(auto&f:it->second){
            bool ok=true; map<string,string> bind;
            for(size_t i=1;i<q.size()&&ok;i++){
                if(q[i][0]=='_'){
                    if(q[i].size()==1) continue;
                    auto b=bind.find(q[i]);
                    if(b==bind.end()) bind[q[i]]=f[i]; else if(b->second!=f[i]) ok=false;
                } else if(q[i]!=f[i]) ok=false;
            }
            if(ok) cnt++;
        }
        printf("%d\n",cnt);
    }
}
