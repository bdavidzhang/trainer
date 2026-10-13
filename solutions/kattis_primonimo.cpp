#include <bits/stdc++.h>
using namespace std;
int main(){int n,m,p;scanf("%d %d %d",&n,&m,&p);int K=n*m;vector<vector<int>>A(K,vector<int>(K+1,0));
 for(int i=0;i<n;i++)for(int j=0;j<m;j++){int a;scanf("%d",&a);int e=i*m+j;A[e][K]=((p-a)%p+p)%p;
  for(int k=0;k<m;k++)A[e][i*m+k]=1;for(int k=0;k<n;k++)A[e][k*m+j]=1;}
 vector<int>inv(p,0);for(int a=1;a<p;a++)for(int b=1;b<p;b++)if(a*b%p==1)inv[a]=b;
 vector<int>where(K,-1);int row=0;
 for(int c=0;c<K&&row<K;c++){int pv=-1;for(int r=row;r<K;r++)if(A[r][c]){pv=r;break;}if(pv<0)continue;swap(A[row],A[pv]);
  int iv=inv[A[row][c]];for(int k=c;k<=K;k++)A[row][k]=A[row][k]*iv%p;
  for(int r=0;r<K;r++)if(r!=row&&A[r][c]){int f=A[r][c];for(int k=c;k<=K;k++)A[r][k]=((A[r][k]-f*A[row][k])%p+p)%p;}
  where[c]=row++;}
 for(int r=row;r<K;r++)if(A[r][K]){puts("-1");return 0;}
 vector<int>out;for(int c=0;c<K;c++)if(where[c]>=0)for(int t=0;t<A[where[c]][K];t++)out.push_back(c+1);
 printf("%d\n",(int)out.size());for(size_t i=0;i<out.size();i++)printf("%d%c",out[i],i+1==out.size()?'\n':' ');if(out.empty())puts("");}
