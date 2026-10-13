#include <bits/stdc++.h>
using namespace std;
int main(){int c;scanf("%d",&c);
    int L[8][3]={{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    while(c--){char s[64];scanf("%s",s);long v=strtol(s,nullptr,8);
        int played=v&511, xs=(v>>9)&511; int X=played&xs, O=played&~xs;
        bool xw=false,ow=false;
        for(auto&l:L){int m=(1<<l[0])|(1<<l[1])|(1<<l[2]);if((X&m)==m)xw=true;if((O&m)==m)ow=true;}
        if(xw)puts("X wins");else if(ow)puts("O wins");else if(played==511)puts("Cat's");else puts("In progress");}
}
