#include <bits/stdc++.h>
using namespace std;
int main(){
    vector<string> d={"N","NE","E","SE","S","SW","W","NW"};
    string a,b;cin>>a>>b;
    int i=find(d.begin(),d.end(),a)-d.begin(),j=find(d.begin(),d.end(),b)-d.begin();
    int k=((j-i)%8+8)%8;
    if(k==0)puts("Keep going straight");
    else if(k==4)puts("U-turn");
    else if(k<4)printf("Turn %d degrees starboard\n",k*45);
    else printf("Turn %d degrees port\n",(8-k)*45);
}
