#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;
#define NMAX 10000
#define MOD 123457

#define fein cin
// #define g cout

int n, m;
string sir;

vector<bool> comp(vector<bool> &a, vector<bool> &b) {
    vector<bool> res(26);
    for(int i=0;i<26;i++) {
        res[i]=a[i]|b[i];
    }
    return res;
}

struct segment_tree {

    vector<vector<bool> > v;

    void build_tree(string start) {
        int size=2;
        while(size<n*2) size*=2;

        v=vector<vector<bool> >(size, vector<bool>(26, 0));
        for(int i=0;i<n;i++) {
            v[n+i][start[i]-'a']=1;
        }
        for(int i=n-1;i>0;i--) {
            v[i]=comp(v[i*2], v[i*2+1]);
        }
    }
    void set(int pos, char c) {
        pos+=n-1;
        v[pos]=vector<bool>(26, 0);
        v[pos][c-'a']=1;
        for(pos>>=1;pos;pos>>=1) {
            v[pos]=comp(v[pos*2], v[pos*2+1]);
        }
    }

    int range(int l, int r) {
        l=l+n-1;
        r=r+n-1;
        vector<bool> res(26, 0);
        while(l<=r) {
            if(l%2==1) {
                res=comp(res, v[l++]);
            }
            l>>=1;
            if(r%2==0) {
                res=comp(res, v[r--]);
            }
            r>>=1;
        }
        int cnt=0;
        for(int i=0;i<26;i++) {
            cnt+=res[i];
        }

        return cnt;
    }
};
segment_tree aint;
//love you <3
void read_data() {
    fein>>sir;
    fein>>m;
    n=sir.size();
}
void handle_querries() {
    for(int i=1;i<=m;i++) {
        int c;
        fein>>c;
        if(c==1) {
            int pos;
            char a;
            fein>>pos>>a;
            aint.set(pos, a);
        }
        else {
            int l, r;
            fein>>l>>r;
            cout<<aint.range(l, r)<<'\n';
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    read_data();
    aint.build_tree(sir);
    handle_querries();

    return 0;
}
