#include<bits/stdc++.h>
#define NMAX 2001
#define MOD 123457
using namespace std;

ifstream fein("date.in");
ofstream g("date.out");

int n;

struct querry {
    int a, t, x;
    querry(int _a, int _t, int _x) : a(_a), t(_t), x(_x) {};
};
vector<querry> q;


struct fenwick {
    vector<unordered_map<int, int> > v;

    void init(int n) {
        v=vector<unordered_map<int, int> >(n+1);
    }

    void increment(int pos, int val, int delta) {
        while(pos <=n ) {
            v[pos][val]+=delta;
            pos += (pos & -pos);
        }
    }
    int prefix_sum(int pos, int val) {
        int s=0;
        while(pos) {
            s+=v[pos][val];
            pos &= pos-1;
        }
        return s;
    }

    void insert(int pos, int val) {
        increment(pos, val, 1);
    }
    void remove(int pos, int val) {
        increment(pos, val, -1);
    }
    int ask(int pos, int val) {
        return prefix_sum(pos, val);
    }

} aib;


int compress_time() {
    vector<int> times;
    for(int i=0;i<n;i++) {
        times.push_back(q[i].t);
    }
    sort(times.begin(), times.end());
    int cnt=2;
    map<int, int> m;
    m[times[0]]=1;
    for(int i=1;i<n;i++) {
        if(times[i]!=times[i-1]) {
            m[times[i]]=cnt;
            cnt++;
        }
    }
    for(int i=0;i<n;i++) {
        q[i].t=m[q[i].t];
    }
    return cnt;
}

void solve() {
    for(int i=0;i<q.size();i++) {
        if(q[i].a==1) aib.insert(q[i].t, q[i].x);
        if(q[i].a==2) aib.remove(q[i].t, q[i].x);
        if(q[i].a==3) cout<<aib.ask(q[i].t, q[i].x)<<'\n';
    }
}

void read_data() {
    cin>>n;
    int a, x, t;
    for(int i=0;i<n;i++) {
        cin>>a>>t>>x;
        q.push_back(querry(a, t, x));
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    read_data();
    int nr_vals = compress_time();
    aib.init(nr_vals);
    solve();

    return 0;
}
