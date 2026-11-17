#include <iostream>
#include <fstream>
using namespace std;
ifstream fein("ferestre.in");
ofstream g("ferestre.out");
#define NMAX 2000000
#define pii pair<int,int>

int n, m, v[NMAX];


void read_data() {
    cin>>n>>m;
    n=1<<n;
    for(int i=0;i<n;i++) {
        cin>>v[i+n];
    }
}
void build_tree() {
    bool is_or=1;
    for(int i=n-1;i>=0;i--) {
        v[i]= (is_or ? v[2*i]|v[2*i+1] : v[2*i]^v[2*i+1]);
        if((i&(i-1))==0) {
            is_or=!is_or;
        }
    }
}

void set_val(int val, int pos) {
    pos+=n-1;
    v[pos]=val;
    bool is_or=1;
    for(pos>>=1;pos;pos>>=1) {
        // cout<<v[2*pos]<<(is_or? "|" : "^")<<v[2*pos+1]<<endl;
        v[pos]= (is_or ? v[2*pos]|v[2*pos+1] : v[2*pos]^v[2*pos+1]);
        is_or=!is_or;
    }
}

void handle_querries() {
    int pos, val;
    for(int i=1;i<=m;i++) {
        cin>>pos>>val;
        set_val(val, pos);
        cout<<v[1]<<'\n';
    }
}

int main()
{
    read_data();
    build_tree();
    handle_querries();

    return 0;
}
