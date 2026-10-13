#include <bits/stdc++.h>
using namespace std;

// angle of a wind direction: start from the 2-letter (or 1-letter) suffix, then each
// extra leading letter moves halfway toward that letter's axis: steps 22.5, 11.25, ...
static double ang(const string&s){
    int k=s.size();
    if(k==1){ return s=="N"?0:s=="E"?90:s=="S"?180:270; }
    string t=s.substr(k-2);
    double lo,hi; char cl,ch; // quadrant [lo,hi], letter at lo end, letter at hi end
    if(t=="NE"){lo=0;hi=90;cl='N';ch='E';}
    else if(t=="SE"){lo=90;hi=180;cl='E';ch='S';}
    else if(t=="SW"){lo=180;hi=270;cl='S';ch='W';}
    else {lo=270;hi=360;cl='W';ch='N';}
    double a=(lo+hi)/2, step=22.5;
    for(int i=k-3;i>=0&&step>1e-13;i--){
        if(s[i]==cl)a-=step; else a+=step;
        step/=2;
    }
    (void)ch;
    return a;
}
int main(){
    string x,y; cin>>x>>y;
    double d=fabs(ang(x)-ang(y));
    d=fmod(d,360.0); if(d>180)d=360-d;
    printf("%.10f\n",d);
}
