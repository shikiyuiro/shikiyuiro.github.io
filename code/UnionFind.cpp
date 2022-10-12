class UnionFind{
public:
    UnionFind(int64_t size){ Root.resize(size); iota(Root.begin(), Root.end(), 0); Size.resize(size, 1);}
    int64_t find(int64_t x){ return (Root[x] == x) ? x: Root[x] = find(Root[x]); }
    bool unite(int64_t x, int64_t y){
        if(find(x) == find(y)) return false;
        if(Size[find(x)] < Size[find(y)]) swap(x, y);
        Size[find(x)] += Size[find(y)];
        Root[find(y)] = find(x);
        return true;
    }
    bool same(int64_t x, int64_t y){ return find(x) == find(y);}
    int64_t size(int64_t x){ return Size[find(x)];}
private:
    vector<int64_t> Root;
    vector<int64_t> Size;
};
