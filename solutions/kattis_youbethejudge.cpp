#include <bits/stdc++.h>
using namespace std;
bool prime(long long x){
    if(x<2)return false;
    for(long long d=2;d*d<=x;d++)if(x%d==0)return false;
    return true;
}
int main(){
    string all((istreambuf_iterator<char>(cin)),istreambuf_iterator<char>());
    vector<string> tok;string cur;
    for(char c:all){
        if(c==' '||c=='\t'||c=='\n'||c=='\r'){if(!cur.empty()){tok.push_back(cur);cur.clear();}}
        else cur+=c;
        if(tok.size()>3)break;
    }
    if(!cur.empty())tok.push_back(cur);
    bool ok=tok.size()==3;
    long long v[3]={0,0,0};
    if(ok)for(int i=0;i<3;i++){
        const string&t=tok[i];
        if(t.size()>10||(t.size()>1&&t[0]=='0')){ok=false;break;}
        for(char c:t)if(c<'0'||c>'9')ok=false;
        if(!ok)break;
        v[i]=stoll(t);
    }
    if(ok){
        if(v[0]<=3||v[0]>1000000000LL||v[0]%2)ok=false;
        else if(v[1]+v[2]!=v[0])ok=false;
        else if(!prime(v[1])||!prime(v[2]))ok=false;
    }
    cout<<(ok?1:0)<<"\n";
}
