#include <bits/stdc++.h>
using namespace std;
int main(){
    string s,t; cin>>s>>t;
    int h=0,v=0;
    for(char c:t){ if(c=='v')h^=1; else if(c=='h')v^=1; else {h^=1;v^=1;} }
    // here variable h = 'v' op (b<->p, d<->q in place); variable v = 'h' op (reverse, b<->d, p<->q); r = both
    auto fh=[](char c){ switch(c){case 'b':return 'p';case 'p':return 'b';case 'd':return 'q';default:return 'd';} };
    auto fv=[](char c){ switch(c){case 'b':return 'd';case 'd':return 'b';case 'p':return 'q';default:return 'p';} };
    if(h) for(char&c:s)c=fh(c);
    if(v){ reverse(s.begin(),s.end()); for(char&c:s)c=fv(c);}
    puts(s.c_str());
}
