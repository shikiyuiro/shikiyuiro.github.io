class LevelAncestor{
public:
    vector<int64_t> depth;
    vector<vector<int64_t>> dict;
    vector<int64_t> tour_order;
    LevelAncestor(vector<vector<int64_t>> &tree, int64_t root = 0){
        depth.resize(tree.size());
        dict.resize(tree.size());
        tour_order.resize(tree.size());
        int64_t order = 0;
        auto dfs = [&](auto &&self, int64_t vis, int64_t prv, int64_t dep) -> void {
            depth[vis] = dep;
            tour_order[vis] = order++;
            dict[dep].push_back(vis);
            for(auto nxt : tree[vis]){
                if(nxt == prv) continue;
                self(self, nxt, vis, dep+1);
            }
        };
        dfs(dfs, root, -1, 0);
    }
    int64_t query(int64_t from, int64_t to_depth){
        assert(depth[from] >= to_depth);
        int64_t pass = 0, fail = dict[to_depth].size();
        while(fail - pass > 1){
            int64_t mid = pass + (fail - pass) / 2;
            (tour_order[dict[to_depth][mid]] <= tour_order[from] ? pass : fail) = mid;
        }
        return dict[to_depth][pass];
    }
    int64_t LCA(int64_t A, int64_t B){
        if(depth[A] > depth[B]) swap(A, B);
        B = query(B, depth[A]);
        if(A == B) return A;
        else{
            int64_t pass = 0;
            int64_t fail = depth[A];
            while(fail - pass > 1){
                int64_t mid = pass + (fail - pass) / 2;
                (query(A, mid) == query(B, mid) ? pass : fail) = mid;
            }
            return query(A, pass);
        }
    }
};
