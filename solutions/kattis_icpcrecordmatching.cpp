#include <bits/stdc++.h>
using namespace std;
struct R{string f,l,e,le,ln;};
static string low(string s){for(auto&c:s)c=tolower((unsigned char)c);return s;}
int main(){
    vector<R> A[2]; int cur=0; string line;
    while(getline(cin,line)){
        istringstream is(line); R r;
        if(!(is>>r.f>>r.l>>r.e)){ if(cur==0&&!A[0].empty()) cur=1; continue; }
        r.le=low(r.e); r.ln=low(r.l)+"\t"+low(r.f);
        A[cur].push_back(r);
    }
    bool any=false;
    for(int s=0;s<2;s++){
        set<string> em,nm;
        for(auto&r:A[1-s]){em.insert(r.le);nm.insert(r.ln);}
        vector<R> out;
        for(auto&r:A[s]) if(!em.count(r.le)&&!nm.count(r.ln)) out.push_back(r);
        stable_sort(out.begin(),out.end(),[](const R&a,const R&b){return a.le<b.le;});
        for(auto&r:out){any=true;printf("%c %s %s %s\n",s?'O':'I',r.e.c_str(),r.l.c_str(),r.f.c_str());}
    }
    if(!any) puts("No mismatches.");
}
