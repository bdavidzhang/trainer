#include <bits/stdc++.h>
using namespace std;
// rings: 0=top(o), 1=left(g), 2=right(r). Positions 0..2 of each ring lie on the centre circle.
string s[3];
vector<pair<char,int>> mv;
const char NAME[3]={'o','g','r'};
void rot(int ring,int k){ // clockwise by k: bead at i -> i+k
    k%=10;if(k<0)k+=10;if(!k)return;
    string t=s[ring];for(int i=0;i<10;i++)t[(i+k)%10]=s[ring][i];s[ring]=t;
    mv.push_back({NAME[ring],k});
}
void cen(int k){ // c1: top->right, right->left, left->top (index preserving)
    for(int it=0;it<k;it++)for(int i=0;i<3;i++){char a=s[0][i],b=s[2][i],c=s[1][i];s[2][i]=a;s[1][i]=b;s[0][i]=c;}
    mv.push_back({'c',k});
}
// swap one bead: ring A (kept on its own track) with ring B. Needs bad bead at A[9], good bead at B[2].
// pre = centre rotation bringing B's triple into A's slot.
void exch(int A,int pre){cen(pre);rot(A,1);cen(3-pre);}
void bring(int ring,int from,int to){rot(ring,to-from);}
int main(){
    cin>>s[0]>>s[1]>>s[2];
    // stage 1: fill top with 'o'
    while(true){
        int bad=-1;for(int i=0;i<10;i++)if(s[0][i]!='o'){bad=i;break;}
        if(bad<0)break;
        bring(0,bad,9);
        int B=1,pos=-1;
        for(int b=1;b<=2&&pos<0;b++)for(int i=0;i<10;i++)if(s[b][i]=='o'){B=b;pos=i;break;}
        bring(B,pos,2);
        exch(0,B==1?1:2); // c1 brings left triple to top; c2 brings right triple to top
    }
    // stage 2: left gets 'g', right gets 'r', without disturbing top: c1 puts right's triple in left's slot
    while(true){
        int bad=-1;for(int i=0;i<10;i++)if(s[1][i]!='g'){bad=i;break;}
        if(bad<0)break;
        bring(1,bad,9);
        int pos=-1;for(int i=0;i<10;i++)if(s[2][i]=='g'){pos=i;break;}
        bring(2,pos,2);
        exch(1,1);
    }
    printf("%d\n",(int)mv.size());
    for(auto&m:mv)printf("%c%d\n",m.first,m.second);
}
