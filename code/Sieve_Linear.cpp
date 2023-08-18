class LinearSieve{
public:
    LinearSieve(int64_t Siz) : p1(Siz+1, -1){
        for(int64_t i = 2; i <= Siz; i++){
            if(p1[i] == -1) {
                p1[i] = i;
                prime.push_back(i);
            }
            for(auto p : prime){
                if(p * i > Siz or p > p1[i]) break;
                p1[p * i] = p;
            }
        }
    }
    int64_t get_p1(int64_t A){
        return p1[A];
    }
    map<int64_t,int64_t> osa_k(int64_t A){
        map<int64_t,int64_t> mp;
        while(A != 1){
            mp[p1[A]]++;
            A /= p1[A];
        }
        return mp;
    }
    bool is_prime(int64_t A){
        return A == p1[A];
    }
    vector<int64_t> get_prime_table(){
        return prime;
    }
private:
    vector<int64_t> p1, prime;
};
