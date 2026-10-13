#include <bits/stdc++.h>
using namespace std;
string s;
bool rec(size_t p,int foot){
    if(foot==5){ string r=s.substr(p); return r=="-u"||r=="--"; }
    if(s.compare(p,3,"-uu")==0 && p+3<=s.size() && rec(p+3,foot+1)) return true;
    if(s.compare(p,2,"--")==0 && p+2<=s.size() && rec(p+2,foot+1)) return true;
    return false;
}
int main(){cin>>s;cout<<(rec(0,0)?"yes":"no")<<"\n";}
