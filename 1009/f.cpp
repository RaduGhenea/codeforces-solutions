#include <stdio.h>
#include <vector>
#include <assert.h>

using namespace std;
#define NMAX 1000010

int n, k, ans[NMAX], mx[NMAX];
vector<int> l[NMAX];

void read_Data() {
    scanf("%d", &n);
    for(int i=1;i<n;i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        l[x].push_back(y);
        l[y].push_back(x);
    }
}

struct family {
    vector<int> v;
    int mx_pos;

    family(int n, int val) {
        v.assign(n, val);
        mx_pos=0;
    }
    int size() {
        return v.size();
    }
    int reverse_pos(int pos) {
        return size()-pos-1;
    }

    void increment_and_compute_mx(int pos, int val) {
        v[pos]+=val;
        if(v[mx_pos]<v[pos] || (v[mx_pos]==v[pos] && pos>mx_pos)) {
            mx_pos=pos;
        }
    }
};

void merge_into(family &dest, family &src) {
    if(src.size()>dest.size()) {
        swap(dest, src);
    }
    for(int i=0;i<src.size();i++) {
        dest.increment_and_compute_mx(dest.size()-i-1, src.v[src.size()-i-1]);
    }
}

family dfs(int node, int parent) {
    family res(1, 1);
    mx[node]=1;
    for(int vc : l[node]) {
        if(vc!=parent) {
            family d = dfs(vc, node);
            d.v.push_back(0);
            merge_into(res, d);
        }
    }
    ans[node]=res.reverse_pos(res.mx_pos);
    return res;
}

void print_ans() {
    for(int i=1;i<=n;i++) {
        printf("%d\n", ans[i]);
    }
}

int main() {
    read_Data();
    dfs(1, 0);
    print_ans();
    return 0;
}
