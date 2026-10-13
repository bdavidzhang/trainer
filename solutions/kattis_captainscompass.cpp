#include <bits/stdc++.h>
using namespace std;
int main(){int xs,ys,xt,yt;cin>>xs>>ys>>xt>>yt;int dx=xt-xs,dy=yt-ys;
 int ax=abs(dx),ay=abs(dy);
 string v=dy>0?"N":"S",h=dx>0?"E":"W";
 if(ay>ax)cout<<v<<"\n"; else if(ax>ay)cout<<h<<"\n";
 if(min(ax,ay)>0)cout<<v+h<<"\n";
}
