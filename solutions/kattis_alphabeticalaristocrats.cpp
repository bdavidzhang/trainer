#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; string line; getline(cin,line); n=stoi(line);
    vector<pair<string,string>> v;
    for(int i=0;i<n;i++){
        getline(cin,line);
        while(!line.empty() && (line.back()=='\r'||line.back()=='\n')) line.pop_back();
        size_t p=0; while(p<line.size() && !(line[p]>='A'&&line[p]<='Z')) p++;
        v.push_back({line.substr(p), line});
    }
    stable_sort(v.begin(),v.end(),[](const pair<string,string>&a,const pair<string,string>&b){return a.first<b.first;});
    for(auto&x:v) cout<<x.second<<"\n";
}
