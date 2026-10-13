#include <bits/stdc++.h>
int rd(){int h,m,s;scanf("%d:%d:%d",&h,&m,&s);return h*3600+m*60+s;}
int main(){int n,m;scanf("%d %d",&n,&m);std::vector<int>a(n),b(m);for(auto&x:a)x=rd();for(auto&x:b)x=rd();int s;scanf("%d",&s);
int best=-1;for(int x:a)for(int y:b)if(y-x>=s&&(best<0||y-x<best))best=y-x;printf("%d\n",best);}
