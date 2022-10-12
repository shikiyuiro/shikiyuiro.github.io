class HLD{
public:
    vector<int64_t> table;
    vector<int64_t> table_pos;
    HLD(vector<vector<int64_t>> &tree, int64_t root = 0) : root(root){
        vector<int64_t> heavynxt(tree.size());
        table_rec.resize(tree.size());
        table_pos.resize(tree.size());
        parent.resize(tree.size());
        auto calc = [&](auto &&self, int64_t vis, int64_t prv) -> int64_t {
            parent[vis] = prv;
            int64_t weight = 1;
            pair<int64_t,int64_t> nxt_chmax = {-1, -1};
            for(auto nxt : tree[vis]){
                if(nxt == prv) continue;
                int64_t weight_nxt = self(self, nxt, vis);
                if(nxt_chmax.second < weight_nxt) nxt_chmax = {nxt, weight_nxt};
                weight += weight_nxt;
            }
            heavynxt[vis] = nxt_chmax.first;
            return weight;
        };
        calc(calc, root, root);
        stack<pair<int64_t,int64_t>> make_table; make_table.push({root, root});
        while(not make_table.empty()){
            auto [vis, rec] = make_table.top(); make_table.pop();
            table_rec[vis] = rec;
            table_pos[vis] = table.size();
            table.push_back(vis);
            for(auto nxt : tree[vis]){
                if(nxt == parent[vis]) continue;
                if(nxt != heavynxt[vis]){
                    make_table.push({nxt, nxt});
                }
            }
            if(heavynxt[vis] != -1){
                make_table.push({heavynxt[vis], rec});
            }
        }
    }
    vector<pair<int64_t,int64_t>> path_decomp(int64_t L, int64_t R, bool exclude_LCA = false){
        vector<pair<int64_t,int64_t>> resL, resR;
        while(table_rec[L] != table_rec[R]){
            if(table_pos[L] > table_pos[R]){
                resL.push_back({table_pos[L], table_pos[table_rec[L]]});
                L = parent[table_rec[L]];
            }else{
                resR.push_back({table_pos[table_rec[R]], table_pos[R]});
                R = parent[table_rec[R]];
            }
        }
        resL.push_back({table_pos[L], table_pos[R]});
        if(exclude_LCA){
            if(table_pos[L] < table_pos[R]) resL.back().first++;
            else if(table_pos[L] > table_pos[R]) resL.back().second++;
            else resL.pop_back();
        }
        for_each(resR.crbegin(), resR.crend(), [&](auto r){resL.push_back(r);});
        return resL;
    }
private:
    int64_t root;
    vector<int64_t> table_rec;
    vector<int64_t> parent;
};
