template<class S, S (*op)(S, S), S (*e)()>
class SegmentTree{
public:
    vector<S> table;
    int64_t size = 1;
    SegmentTree(vector<S> vec){
        while(size < vec.size()) size <<= 1;
        table.resize(size << 1, e());
        for(int64_t i = 0; i < (int64_t)vec.size(); i++) table[i + size] = vec[i];
        for(int64_t i = size - 1; i >= 1; i--) table[i] = op(table[i<<1|0],table[i<<1|1]);
    }
    SegmentTree(int64_t siz){
        while(size < siz) size <<= 1;
        table.resize(size << 1, e());
        for(int64_t i = 0; i < siz; i++) table[i + size] = e();
        for(int64_t i = size - 1; i >= 1; i--) table[i] = op(table[i<<1|0],table[i<<1|1]);
    }
    S fold(int64_t l, int64_t r){
        l += size; r += size;
        S Lres = e(), Rres = e();
        while(l < r){
            if(l & 1) Lres = op(Lres, table[l++]);
            if(r & 1) Rres = op(table[--r], Rres);
            l >>= 1; r >>= 1;
        }
        return op(Lres, Rres);
    }
    void set(int64_t p, S x){
        p += size;
        table[p] = x;
        while(p >>= 1) table[p] = op(table[p<<1|0],table[p<<1|1]);
    }
};
