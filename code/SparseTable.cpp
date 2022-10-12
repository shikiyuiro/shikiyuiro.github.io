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
