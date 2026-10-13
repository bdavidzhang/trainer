#include <bits/stdc++.h>
using namespace std;
static char buf[1<<25];size_t bl=0,bp=0;
inline int gc(){if(bp==bl){bl=fread(buf,1,sizeof(buf),stdin);bp=0;if(!bl)return -1;}return buf[bp++];}
inline long long rd(){int c=gc();while(c!='-'&&(c<'0'||c>'9'))c=gc();long long x=0;while(c>='0'&&c<='9'){x=x*10+c-'0';c=gc();}return x;}
inline int rc(){int c=gc();while(c!='P'&&c!='Q')c=gc();return c;}
struct H{ // open addressing, key>0, cleared via touched list
  int cap,mask;vector<int> k,v,used;
  H(int c){cap=c;mask=c-1;k.assign(c,0);v.assign(c,0);}
  inline int& get(int key){unsigned h=((unsigned long long)key*0x9E3779B97F4A7C15ULL)>>40;h&=mask;while(k[h]&&k[h]!=key)h=(h+1)&mask;if(!k[h]){k[h]=key;v[h]=0;used.push_back(h);}return v[h];}
  void clear(){for(int h:used)k[h]=0;used.clear();}
};
int main(){
  int t=rd();H person(1<<22),genre(1<<22);string out;
  while(t--){rd();int q=rd();rd();
    while(q--){int c=rc();int s=rd();
      if(c=='P'){int a=rd();int &gs=genre.get(s);int add=0;
        // careful: gs reference stays valid (no rehash, fixed arrays)
        for(int i=0;i<a;i++){int x=rd();int &pg=person.get(x);if(pg==s)continue;if(pg){genre.get(pg)--;}pg=s;add++;}
        genre.get(s)+=add;(void)gs;
      }else{out+=to_string(genre.get(s));out+='\n';}
    }
    person.clear();genre.clear();
  }
  fwrite(out.data(),1,out.size(),stdout);
}
