class FenwickTree{
public:
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
