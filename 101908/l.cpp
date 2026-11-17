#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

const int NMAX=1e5*5+1;
const int MOD=666013;

struct fenwick_tree {
    int v[NMAX], _size;

    void init(int n) {
        for(int i=1;i<=n;i++) {
            v[i]=0;
            _size=n;
        }
    }
    void add(int pos, int val) {
        assert(pos<=_size);
        while(pos<=_size) {
            v[pos]+=val;
            pos += pos & -pos;
        }
    }
    int prefix_sum(int pos) {
        assert(pos<=_size);
        int sum=0;
        while(pos) {
            sum+=v[pos];
            pos &= pos-1;
        }
        return sum;
    }
};

struct rurq_fenwick {
    fenwick_tree v, w;

    void init(int n) {
        v.init(n);
        w.init(n);
    }
    void range_add(int l, int r, int val) {
        v.add(l, val);
        v.add(r+1, -val);
        w.add(l, -val*(l-1));
        w.add(r+1, val*r);
    }
    int prefix_sum(int pos) {
        return v.prefix_sum(pos) * pos + w.prefix_sum(pos);
    }
    int range_sum(int l, int r) {
        return prefix_sum(r)-prefix_sum(l-1);
    }
} fen;

int n, q;

struct node_info {
    int heavy, head, time_in, parent, depth;
    vector<int> adj;
} nd[NMAX];

int heavy_dfs(int u) {
    int _size=1, max_child_size=0;

    for(int i=0;i<nd[u].adj.size();i++) {
        int v=nd[u].adj[i];
        if(v!=nd[u].parent) {
            nd[v].parent=u;
            nd[v].depth=nd[u].depth+1;

            int v_size=heavy_dfs(v);
            _size+=v_size;

            if(v_size>max_child_size) {
                max_child_size=v_size;
                nd[u].heavy=v;
            }
        }
    }
    return _size;
}

void decompose_dfs(int u, int head) {
    static int time=1;

    nd[u].head=head;
    nd[u].time_in=time++;

    if(nd[u].heavy) {
        decompose_dfs(nd[u].heavy, head);
    }

    for(int v : nd[u].adj) {
        if(v!=nd[u].parent && v!=nd[u].heavy) {
            decompose_dfs(v, v);
        }
    }
}

void add_on_path(int u, int v, int val) {
    while(nd[u].head!=nd[v].head) {
        if(nd[nd[v].head].depth > nd[nd[u].head].depth) {
            swap(u, v);
        }
        fen.range_add(nd[nd[u].head].time_in, nd[u].time_in, val);
        u=nd[nd[u].head].parent;
    }
    if(nd[u].depth > nd[v].depth) {
        swap(u, v);
    }
    fen.range_add(nd[u].time_in, nd[v].time_in, val);
}

int count_on_path(int u, int v) {
    int res=0;
    while(nd[u].head!=nd[v].head) {
        if(nd[nd[v].head].depth > nd[nd[u].head].depth) {
            swap(u, v);
        }
        res+=fen.range_sum(nd[nd[u].head].time_in, nd[u].time_in);
        u=nd[nd[u].head].parent;
    }
    if(nd[u].depth > nd[v].depth) {
        swap(u, v);
    }
    res+=fen.range_sum(nd[u].time_in, nd[v].time_in);
    return res;
}

void process_querries() {
    for(int i=1;i<=q;i++) {
        int a, b, c, d; cin>>a>>b>>c>>d;

        add_on_path(a, b, 1);
        cout<<count_on_path(c, d)<<'\n';
        add_on_path(a, b, -1);
    }
}

void read_data() {
    cin>>n>>q;
    for(int i=1;i<n;i++) {
        int u, v; cin>>u>>v;
        nd[u].adj.push_back(v);
        nd[v].adj.push_back(u);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    read_data();
    fen.init(n*2);

    heavy_dfs(1);
    decompose_dfs(1, 1);

    process_querries();

    return 0;
}
