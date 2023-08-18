template<class S, S (*op)(S, S), S (*e)(), class F, S (*Fx)(F, S), F (*GoF)(F, F), F (*id)()>
class LazySegmentTree{
public:
    vector<S> table;
    vector<F> lazy;
    int64_t size = 1;
    int64_t log = 0;
    LazySegmentTree(vector<S> vec){
        while((size << log) < vec.size()) log++;
        size <<= log;
        table.resize(size << 1, e());
        lazy.resize(size, id());
        for(int64_t i = 0; i < (int64_t)vec.size(); i++) table[i + size] = vec[i];
        for(int64_t i = size - 1; i >= 1; i--) update(i);
    }
    S fold(int64_t l, int64_t r){
        l += size; r += size;
        S Lres = e(), Rres = e();
        for(int64_t i = log; i >= 1; i--){
            if(((l >> i) << i) != l) push(l >> i);
            if(((r >> i) << i) != r) push(r >> i);
        }
        while(l < r){
            if(l & 1) Lres = op(Lres, table[l++]);
            if(r & 1) Rres = op(table[--r], Rres);
            l >>= 1; r >>= 1;
        }
        return op(Lres, Rres);
    }
    void apply(int64_t l, int64_t r, F f){
        l += size; r += size;
        int64_t lcopy = l, rcopy = r;
        for(int64_t i = log; i >= 1; i--){
            if(((l >> i) << i) != l) push(l >> i);
            if(((r >> i) << i) != r) push(r >> i);
        }
        while(l < r){
            if(l & 1) part_apply(f, l++);
            if(r & 1) part_apply(f, --r);
            l >>= 1; r >>= 1;
        }
        l = lcopy; r = rcopy;
        for(int64_t i = 1; i <= log; i++){
            if(((l >> i) << i) != l) update(l >> i);
            if(((r >> i) << i) != r) update(r >> i);
        }
    }
    void set(int64_t p, S x){
        p += size;
        for(int64_t i = log; i >= 1; i--) push(p >> i);
        table[p] = x;
        while(p >>= 1) update(p);
    }
private:
    void update(int64_t p){
        table[p] = op(table[p<<1|0],table[p<<1|1]);
    }
    void part_apply(F f, int64_t p){
        table[p] = Fx(f, table[p]);
        if(p < size) lazy[p] = GoF(f, lazy[p]);
    }
    void push(int64_t p){
        part_apply(lazy[p], p<<1|0);
        part_apply(lazy[p], p<<1|1);
        lazy[p] = id();
    }
};
