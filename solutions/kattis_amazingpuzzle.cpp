#include <bits/stdc++.h>
using namespace std;
int C,R,E;
bool hw[52][52], vw[52][52]; // hw[c][r]: wall between (c,r),(c,r+1); vw[c][r]: between (c,r),(c+1,r)
int OUTP;
int dc[4]={0,1,0,-1}, dr[4]={1,0,-1,0}; // N,E,S,W
int nxt[2505][4]; char bmp[2505][4];
int main(){
    scanf("%d %d %d",&C,&R,&E);
    int c1,r1,c2,r2; char a1,a2;
    scanf("%d %d %c %d %d %c",&c1,&r1,&a1,&c2,&r2,&a2);
    int n; scanf("%d",&n);
    for(int i=0;i<n;i++){int c,r; scanf("%d %d",&c,&r); hw[c][r]=true;}
    scanf("%d",&n);
    for(int i=0;i<n;i++){int c,r; scanf("%d %d",&c,&r); vw[c][r]=true;}
    string D="NESW";
    int d1=D.find(a1), d2=D.find(a2);
    int off=((d2-d1)%4+4)%4;
    OUTP=C*R;
    auto id=[&](int c,int r){return (r-1)*C+(c-1);};
    for(int c=1;c<=C;c++) for(int r=1;r<=R;r++) for(int d=0;d<4;d++){
        int p=id(c,r);
        if(d==2 && r==1 && c==E){ nxt[p][d]=OUTP; bmp[p][d]=0; continue; }
        int nc=c+dc[d], nr=r+dr[d];
        bool blocked = nc<1||nc>C||nr<1||nr>R;
        if(!blocked){
            if(d==0) blocked=hw[c][r];
            else if(d==2) blocked=hw[c][r-1];
            else if(d==1) blocked=vw[c][r];
            else blocked=vw[c-1][r];
        }
        if(blocked){ nxt[p][d]=p; bmp[p][d]=1; }
        else { nxt[p][d]=id(nc,nr); bmp[p][d]=0; }
    }
    for(int d=0;d<4;d++){ nxt[OUTP][d]=OUTP; bmp[OUTP][d]=0; }
    int S=OUTP+1;
    vector<int> dist((size_t)S*S,-1), bm((size_t)S*S,INT_MAX);
    int st=id(c1,r1)*S+id(c2,r2);
    dist[st]=0; bm[st]=0;
    vector<int> cur{st}, nx;
    int goal=OUTP*S+OUTP;
    int L=0;
    while(!cur.empty() && dist[goal]<0){
        nx.clear();
        for(int s: cur){
            int p=s/S, q=s%S, b=bm[s];
            for(int d=0;d<4;d++){
                int e=(d+off)%4;
                int np=nxt[p][d], nq=nxt[q][e];
                if(np==nq && np!=OUTP) continue;
                int t=np*S+nq;
                int nb=b+bmp[p][d]+bmp[q][e];
                if(dist[t]<0){ dist[t]=L+1; bm[t]=nb; nx.push_back(t); }
                else if(dist[t]==L+1 && nb<bm[t]) bm[t]=nb;
            }
        }
        swap(cur,nx); L++;
    }
    printf("%d %d\n",dist[goal],bm[goal]);
}
