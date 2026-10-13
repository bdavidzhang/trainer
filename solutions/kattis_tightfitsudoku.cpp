#include <bits/stdc++.h>
using namespace std;
// cell: two slots (a above, b below) if split, else one slot.
bool sp[6][6]; int va[6][6], vb[6][6]; // 0 = unknown
int rowm[6], colm[6], boxm[6];
bool done_[6][6];
static inline int bx(int r,int c){ return (r/2)*2 + c/3; }
bool solve(){
    int br=-1,bc=-1,best=1000;
    for(int r=0;r<6;r++)for(int c=0;c<6;c++) if(!done_[r][c]){
        int used=rowm[r]|colm[c]|boxm[bx(r,c)];
        int cnt=0;
        if(!sp[r][c]){
            for(int d=1;d<=9;d++) if(!(used>>d&1)) cnt++;
        } else {
            int a=va[r][c], b=vb[r][c];
            if(a&&!b){ for(int d=a+1;d<=9;d++) if(!(used>>d&1)) cnt++; }
            else if(b&&!a){ for(int d=1;d<b;d++) if(!(used>>d&1)) cnt++; }
            else { int f=0; for(int d=1;d<=9;d++) if(!(used>>d&1)) f++; cnt=f*(f-1)/2; }
        }
        if(cnt<best){best=cnt;br=r;bc=c;}
        if(cnt==0) return false;
    }
    if(br<0) return true;
    int r=br,c=bc,b_=bx(r,c);
    int used=rowm[r]|colm[c]|boxm[b_];
    done_[r][c]=true;
    if(!sp[r][c]){
        for(int d=1;d<=9;d++) if(!(used>>d&1)){
            int m=1<<d; rowm[r]|=m;colm[c]|=m;boxm[b_]|=m; va[r][c]=d;
            if(solve()) return true;
            rowm[r]^=m;colm[c]^=m;boxm[b_]^=m; va[r][c]=0;
        }
    } else {
        int oa=va[r][c], ob=vb[r][c];
        for(int a=1;a<=9;a++){
            if(oa&&a!=oa) continue;
            if(!oa&&(used>>a&1)) continue;
            for(int b=a+1;b<=9;b++){
                if(ob&&b!=ob) continue;
                if(!ob&&(used>>b&1)) continue;
                int m=0; if(!oa) m|=1<<a; if(!ob) m|=1<<b;
                rowm[r]|=m;colm[c]|=m;boxm[b_]|=m; va[r][c]=a; vb[r][c]=b;
                if(solve()) return true;
                rowm[r]^=m;colm[c]^=m;boxm[b_]^=m; va[r][c]=oa; vb[r][c]=ob;
            }
        }
    }
    done_[r][c]=false;
    return false;
}
int main(){
    for(int r=0;r<6;r++)for(int c=0;c<6;c++){
        string s; cin>>s;
        auto val=[&](char ch){return ch=='-'?0:ch-'0';};
        if(s.size()==3){ sp[r][c]=true; va[r][c]=val(s[0]); vb[r][c]=val(s[2]); }
        else { sp[r][c]=false; va[r][c]=val(s[0]); }
        int m=0; if(va[r][c]) m|=1<<va[r][c]; if(sp[r][c]&&vb[r][c]) m|=1<<vb[r][c];
        rowm[r]|=m;colm[c]|=m;boxm[bx(r,c)]|=m;
        done_[r][c] = sp[r][c] ? (va[r][c]&&vb[r][c]) : va[r][c]!=0;
    }
    solve();
    for(int r=0;r<6;r++){
        for(int c=0;c<6;c++){
            if(c) printf(" ");
            if(sp[r][c]) printf("%d/%d",va[r][c],vb[r][c]); else printf("%d",va[r][c]);
        }
        printf("\n");
    }
}
