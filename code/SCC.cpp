class LowLink{
public:
    LowLink(vector<vector<int64_t>> &graph){
        int64_t N = graph.size(), ord_num = 0, root_count = 0;
        ord.resize(N, -1); low.resize(N, N); is_ART.resize(N, false);
        auto dfs = [&](auto &&self, int64_t vis, int64_t prv) -> void {
            low[vis] = ord[vis] = ord_num++;
            for(auto nxt : graph[vis]){
                if(ord[nxt] == -1){
                    if(prv == -1) root_count++;
                    self(self, nxt, vis);
                    if(ord[vis] <= low[nxt]) is_ART[vis] = true;
                    low[vis] = min(low[vis], low[nxt]);
                }else if(nxt != prv){
                    low[vis] = min(low[vis], ord[nxt]);
                }
            }
            if(prv == -1){
                is_ART[vis] = (root_count >= 2);
                root_count = 0;
            }
        };
        for(int64_t i = 0; i < N; i++) if(ord[i] == -1) dfs(dfs, i, -1);
    }
    bool is_articulation(int64_t with){
        return is_ART[with];
    }
    bool is_bridge(int64_t from, int64_t to){
        if(ord[from] > ord[to]) swap(from, to);
        return ord[from] < low[to];
    }
private:
    vector<int64_t> ord, low;
    vector<bool> is_ART;
};

vector<vector<int64_t>> SCC(vector<vector<int64_t>> &graph){
    vector<vector<int64_t>> res;
    int64_t N = graph.size(), ord_num = 0;
    vector<int64_t> ord(N, -1), low(N, N), vstack;
    auto dfs = [&](auto &&self, int64_t vis) -> void {
        vstack.push_back(vis);
        low[vis] = ord[vis] = ord_num++;
        for(auto nxt : graph[vis]){
            if(ord[nxt] == -1){
                self(self, nxt);
                low[vis] = min(low[vis], low[nxt]);
            }else{
                low[vis] = min(low[vis], ord[nxt]);
            }
        }
        if(low[vis] == ord[vis]){
            res.push_back({});
            while(vstack.back() != vis){
                ord[vstack.back()] = N;
                res.back().push_back(vstack.back());
                vstack.pop_back();
            }
            ord[vstack.back()] = N;
            res.back().push_back(vstack.back());
            vstack.pop_back();
        }
    };
    for(int64_t i = 0; i < N; i++) if(ord[i] == -1) dfs(dfs, i);
    reverse(res.begin(), res.end());
    return res;
}