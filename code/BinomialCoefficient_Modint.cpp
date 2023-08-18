template<class M>
class binomial{
public:
    vector<M> fac, caf;
    binomial(int64_t MAX = 20030224) : fac(MAX), caf(MAX){
        fac[0] = 1;
        for(int64_t i = 1; i < MAX; i++) fac[i] = fac[i-1] * i;
        caf[MAX-1] = M(1) / fac[MAX-1];
        for(int64_t i = MAX-2; i >= 0; i--) caf[i] = caf[i+1] * (i+1);
    }
    M nCk(int64_t n, int64_t k){
        if (k < 0 or n < 0 or n < k) return 0;
        return fac[n] * caf[k] * caf[n-k];
    }
};
