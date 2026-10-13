#include <bits/stdc++.h>
using namespace std;
int main(){ int h,w; scanf("%d %d",&h,&w); vector<int> best(w+1,0), suf(w+2,0); static char buf[2005]; int ans=0;
    for(int r=0;r<h;r++){ scanf("%s",buf); suf[w]=0; for(int c=w-1;c>=0;c--) suf[c]=max(suf[c+1],best[c]);
        for(int c=0;c<w;c++) if(buf[c]=='C'){ best[c]=max(best[c],suf[c+1]+1); ans=max(ans,best[c]); } }
    printf("%d\n",ans); }
