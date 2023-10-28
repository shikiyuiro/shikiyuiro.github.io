class Kdtree{
    struct node{
        int64_t x, y, axis = -1, minidx = -1, maxidx = -1, paridx = -1;
    };
public:
    int64_t siz;
    int64_t root;
    vector<node> tree;
    Kdtree(vector<pair<int64_t,int64_t>>& points){
        siz = points.size();
        vector<tuple<int64_t,int64_t,int64_t>> seq;
        tree.resize(siz);
        for(int64_t i = 0; i < siz; i++){
            auto [xi, yi] = points[i];
            tree[i].x = xi;
            tree[i].y = yi;
        }
        vector<int64_t> s0(siz); iota(s0.begin(), s0.end(), (int64_t)0);
        auto make_tree = [&](auto &&self, vector<int64_t> &sub0, int64_t axis, int64_t prv) -> int64_t{
            int64_t len = sub0.size();
            if(len == 1){
                int64_t vis = sub0.back();
                tree[vis].axis = axis;
                tree[vis].paridx = prv;
                return vis;
            }
            vector<pair<int64_t,int64_t>> dic;
            for(auto idx : sub0) dic.push_back({(axis == 0 ? tree[idx].x : tree[idx].y), idx});
            sort(dic.begin(), dic.end());
            auto [med, argmed] = dic[dic.size()/2];
            vector<int64_t> sub1, sub2;
            for(auto idx : sub0){
                if(idx == argmed) continue;
                int64_t val = (axis == 0 ? tree[idx].x : tree[idx].y);
                if(val < med) sub1.push_back(idx);
                else sub2.push_back(idx);
            }
            tree[argmed].axis = axis;
            if(not sub1.empty()) tree[argmed].minidx = self(self, sub1, axis^1, argmed);
            if(not sub2.empty()) tree[argmed].maxidx = self(self, sub2, axis^1, argmed);
            tree[argmed].paridx = prv;
            return argmed;
        };
        root = make_tree(make_tree, s0, 0, -1);
    }
    vector<int64_t> RangeSearch(int64_t xL, int64_t xR, int64_t yL, int64_t yR){ //矩形領域[xL, xR) x [yL, yR)に含まれる点のindexを全列挙 
        vector<int64_t> res;
        queue<int64_t> que;
        que.push(root);
        while(not que.empty()){
            auto vis = que.front(); que.pop();
            if(vis == -1) continue;
            int64_t val = (tree[vis].axis == 0 ? tree[vis].x : tree[vis].y);
            int64_t aL = (tree[vis].axis == 0 ? xL : yL);
            int64_t aR = (tree[vis].axis == 0 ? xR : yR);
            if(val < aL) que.push(tree[vis].maxidx);
            else if(aR <= val) que.push(tree[vis].minidx);
            else{
                if(xL <= tree[vis].x and tree[vis].x < xR and yL <= tree[vis].y and tree[vis].y < yR) res.push_back(vis);
                que.push(tree[vis].minidx);
                que.push(tree[vis].maxidx);
            }
        }
        sort(res.begin(), res.end());
        return res;
    }
};
