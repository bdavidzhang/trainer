#include <bits/stdc++.h>
using namespace std;
int main(){
    map<string,int> pw={{"Shadow",6},{"Gale",5},{"Ranger",4},{"Anvil",7},{"Vexia",3},{"Guardian",8},
        {"Thunderheart",6},{"Frostwhisper",2},{"Voidclaw",3},{"Ironwood",3},{"Zenith",4},{"Seraphina",1}};
    int wins[2]={0,0}; long long tot[2]={0,0};
    for(int loc=0;loc<3;loc++){
        long long p[2];
        for(int pl=0;pl<2;pl++){
            int c; cin>>c; long long s=0;
            for(int i=0;i<c;i++){
                string t; cin>>t; s+=pw[t];
                if(t=="Thunderheart"&&c==4) s+=6;
                if(t=="Zenith"&&loc==1) s+=5;
                if(t=="Seraphina") s+=c-1;
            }
            p[pl]=s; tot[pl]+=s;
        }
        if(p[0]>p[1]) wins[0]++; else if(p[1]>p[0]) wins[1]++;
    }
    int r=0;
    if(wins[0]!=wins[1]) r=wins[0]>wins[1]?1:2;
    else if(tot[0]!=tot[1]) r=tot[0]>tot[1]?1:2;
    puts(r==0?"Tie":r==1?"Player 1":"Player 2");
}
