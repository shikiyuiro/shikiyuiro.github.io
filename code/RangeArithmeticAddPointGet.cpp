class FenwickTree{
public:
    explicit FenwickTree() = default;
    vector<int64_t> table;
    int64_t siz;
    FenwickTree(int64_t siz) : table(siz + 1), siz(siz) {}
    int64_t sum(int64_t L, int64_t R){
        return sum(R) - sum(L);
    }
    int64_t sum(int64_t index){
        int64_t res = 0;
        while(index > 0){
            res += table[index];
            index -= (index & -index);
        }
        return res;
    }
    void add(int64_t index, int64_t value){
        index++;
        while(index < siz + 1){
            table[index] += value;
            index += (index & -index);
        }
    }
};

class RAQ_RSQ{
public:
    explicit RAQ_RSQ() = default;
    FenwickTree P, Q;
    RAQ_RSQ(int64_t siz){
        P = FenwickTree(siz);
        Q = FenwickTree(siz);
    }
    void add(int64_t L, int64_t R, int64_t x){
        P.add(L, x);
        P.add(R, -x);
        Q.add(L, L * -x);
        Q.add(R, R * x);
    }
    int64_t sum(int64_t L, int64_t R){
        return (P.sum(R) * R + Q.sum(R)) - (P.sum(L) * L + Q.sum(L));
    }
};

class Arithadd_Pointget{
public:
    explicit Arithadd_Pointget() = default;
    RAQ_RSQ D;
    Arithadd_Pointget(int64_t siz){
        D = RAQ_RSQ(siz);
    }
    void add(int64_t L, int64_t R, int64_t a, int64_t d){
        D.add(L, L+1, a);
        D.add(L+1, R, d);
        D.add(R, R+1, -(a + d * (R - L - 1)));
    }
    int64_t get(int64_t p){
        return D.sum(0, p+1);
    }
};
