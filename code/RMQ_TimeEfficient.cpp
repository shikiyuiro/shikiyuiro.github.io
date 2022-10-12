template<class S, S (*op)(S, S), S (*e)()>
class SparseTable{
public:
    explicit SparseTable() = default;
    SparseTable(vector<S>& v){
        isiz = v.size();
        jsiz = 64 - __builtin_clzll(isiz);
        table.resize(isiz * jsiz, e());
        for(int64_t i = 0; i < isiz; i++) table[i] = v[i];
        for(int64_t j = 1; j < jsiz; j++){
            for(int64_t i = 0; i + (1 << (j - 1)) < isiz; i++){
                table[i + isiz * j] = op(table[i + isiz * (j - 1)], table[i + (1 << (j - 1)) + isiz * (j - 1)]);
            }
        }
    }
    S fold(int64_t L, int64_t R){
        if(L == R) return e();
        int64_t b = 64 - __builtin_clzll(R - L) - 1;
        return op(table[L + isiz * b], table[R - (1 << b) + isiz * b]);
    }
private:
    vector<S> table;
    int64_t isiz;
    int64_t jsiz;
};

template<class S, S (*op)(S, S), S (*e)()>
class RMQ_ON_O1{
    int64_t Bsiz = 5;
    int64_t Bcmpl = 31;
public:
    explicit RMQ_ON_O1() = default;
    RMQ_ON_O1(vector<S> &_v) : v(_v){
        v.resize((v.size() | Bcmpl) + 1, e());
        b.resize(v.size());
        for(int64_t i = 0; i < (int64_t)v.size(); i++){
            stack<int64_t> st;
            while(true){
                while(not st.empty()){
                    if(op(v[i], v[st.top()]) != v[i]) break;
                    st.pop();
                }
                b[i] = st.empty() ? 0 : b[st.top()] | (1 << (st.top() & Bcmpl));
                if((i & Bcmpl) == Bcmpl) break;
                st.push(i++);
            }
            v_mini.push_back(fold_mini(i-Bcmpl,i+1));
        }
        sp = SparseTable<S,op,e>(v_mini);
    }
    S fold(int64_t L, int64_t R){
        int64_t Lu = (L | Bcmpl) + 1;
        int64_t Rd = (R & ~Bcmpl);
        if(Lu > Rd) return fold_mini(L, R);
        S res = e();
        res = op(res, fold_mini(L, Lu));
        res = op(res, sp.fold(Lu>>Bsiz, Rd>>Bsiz));
        res = op(res, fold_mini(Rd, R));
        return res;
    }
private:
    vector<S> v;
    vector<S> v_mini;
    vector<int64_t> b;
    SparseTable<S,op,e> sp;
    S fold_mini(int64_t L, int64_t R){
        if(L == R) return e();
        int64_t masked = (b[R-1] >> (L & Bcmpl)) << (L & Bcmpl);
        int64_t lsb = __builtin_ctzll(masked);
        if(masked == 0) return v[R-1];
        else return v[lsb + (L & ~Bcmpl)];
    }
};
