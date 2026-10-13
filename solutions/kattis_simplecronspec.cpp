#include <bits/stdc++.h>
using namespace std;
vector<int> parse(const string&s,int lim){
    vector<int> r;
    if(s=="*"){for(int i=0;i<lim;i++)r.push_back(i);return r;}
    stringstream ss(s);string part;
    while(getline(ss,part,',')){
        size_t p=part.find('-');
        if(p==string::npos)r.push_back(stoi(part));
        else{int a=stoi(part.substr(0,p)),b=stoi(part.substr(p+1));for(int i=a;i<=b;i++)r.push_back(i);}
    }
    return r;
}
int main(){
    int n;cin>>n;vector<char> mark(86400,0);long long tot=0;
    while(n--){
        string h,m,s;cin>>h>>m>>s;
        auto H=parse(h,24),M=parse(m,60),S=parse(s,60);
        tot+=(long long)H.size()*M.size()*S.size();
        for(int a:H)for(int b:M)for(int c:S)mark[a*3600+b*60+c]=1;
    }
    int cnt=0;for(char c:mark)cnt+=c;
    cout<<cnt<<" "<<tot<<"\n";
}
