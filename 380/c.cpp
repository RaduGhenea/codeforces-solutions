#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <bitset>
#include <deque>

struct segment_tree {
    struct Node {
        int unmatched_open;
        int unmatched_closed;
        int matched_pairs;
    };

    Node merge(Node l, Node r) {
        Node res = Node{};
        int new_matches = std::min(l.unmatched_open, r.unmatched_closed);
        res.matched_pairs = r.matched_pairs + l.matched_pairs + new_matches;
        res.unmatched_open = l.unmatched_open + r.unmatched_open - new_matches;
        res.unmatched_closed = l.unmatched_closed + r.unmatched_closed - new_matches;
        return res;
    }

    std::vector<Node> v;
    int p2;

    segment_tree(int n) {
        p2=1;
        while(p2<n) p2<<=1;
        v.assign(p2*2, Node{0, 0, 0});
    }

    void build(int node, int l, int r, const std::string& s) {
        if(l==r) {
            if(s[l-1]=='(') v[node]=Node{.unmatched_open=1, .unmatched_closed=0, .matched_pairs=0};
            else v[node]=Node{.unmatched_open=0, .unmatched_closed=1, .matched_pairs=0};
        }
        else {
            int mid=(l+r)/2;
            build(node*2, l, mid, s);
            build(node*2+1, mid+1, r, s);
            v[node]=merge(v[node*2], v[node*2+1]);
        }
    }

    Node querry(int node, int l, int r, int a, int b) {
        if(l>=a && r<=b) {
            return v[node];
        }
        else {
            int mid=(l+r)/2;
            Node left = Node{0, 0, 0}, right = Node{0, 0, 0};
            if(a<=mid) {
                left=querry(node*2, l, mid, a, b);
            }
            if(b>=mid+1) {
                right=querry(node*2+1, mid+1, r, a, b);
            }
            return merge(left, right);
        }
    }
};

int main() {
    std::string s; std::cin>>s;
    segment_tree st = segment_tree(s.size());
    st.build(1, 1, s.size(), s.data());

    int T; std::cin>>T;
    for(int i=1;i<=T;i++) {
        int l, r; std::cin>>l>>r;
        segment_tree::Node res = st.querry(1, 1, s.size(), l, r);
        std::cout<<res.matched_pairs*2<<'\n';
    }
    return 0;
}
