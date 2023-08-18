class PPUF{
public:
    explicit PPUF() = default;
    PPUF(int64_t size){
        Parent.resize(size); iota(Parent.begin(), Parent.end(), 0);
        Size.resize(size, 1);
        history.resize(size); for(auto &s : history) s.push_back({INT64_MIN, 1});
        United.resize(size, INT64_MAX);
    }
    int64_t find(int64_t u, int64_t t){ return (United[u] > t) ? u: find(Parent[u], t); }//時刻t直後のuの根を求める。
    bool unite(int64_t u, int64_t v, int64_t t){
        //tはuniteクエリごとに広義単調増加でなければならないが、連続する値である必要はない。
        int64_t fu = find(u), fv = find(v);
        if(fu == fv) return false;
        if(Size[fu] < Size[fv]) swap(fu, fv);
        Parent[fv] = fu;
        Size[fu] += Size[fv];
        history[fu].push_back({t, Size[fu]});
        United[fv] = t;
        return true;
    }
    bool same(int64_t u, int64_t v, int64_t t){//時刻t直後にuとvが連結であるか判定する。
        return find(u, t) == find(v, t);
    }
    int64_t size(int64_t u, int64_t t){//時刻t直後のuの連結成分の個数を取得する。
        int64_t fu = find(u, t);
        return prev(upper_bound(history[fu].begin(), history[fu].end(), pair<int64_t,int64_t>({t, INT64_MAX})))->second;
    }
private:
    vector<int64_t> Parent;
    vector<int64_t> Size;
    vector<vector<pair<int64_t,int64_t>>> history;//unite直後の連結成分のサイズを保存する
    vector<int64_t> United;//何回目の結合で根ではなくなるか　ー＞ その値以下の時刻であればその頂点は根、そうでなかったらParentをたどればよい。
    int64_t find(int64_t u){ return (Parent[u] == u) ? u: find(Parent[u]); }
};
