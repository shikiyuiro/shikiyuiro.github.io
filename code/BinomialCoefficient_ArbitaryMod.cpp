//二項係数のすごいやつ
class binomial_arbitrary_mod{
public:
    binomial_arbitrary_mod(int64_t mod) : MOD(mod){
        int64_t mod_tmp = mod;
        for(int64_t i = 2; i * i <= mod_tmp; i++){
            while(mod_tmp % i == 0){
                mod_tmp /= i;
                primes[i]++;
            }
        }
        if(mod_tmp != 1) primes[mod_tmp] = 1;
        for(auto [p, q] : primes){
            bpp.push_back(binomial_primepower(p, q));
            int64_t pp = 1;
            while(q--) pp *= p;
            primepowers.push_back(pp);
        }
        
    }
    int64_t nCk(int64_t n, int64_t k){
        vector<int64_t> b, m;
        for(int64_t i = 0; i < bpp.size(); i++){
            b.push_back(bpp[i].nCk(n, k));
            m.push_back(primepowers[i]);
        }
        CRT crt(MOD);
        return crt.Garner(b, m);
    }
private:
    int64_t MOD;
    vector<int64_t> primepowers;
    map<int64_t,int64_t> primes;
    struct binomial_primepower{
        int64_t p, q;
        int64_t mod = 1;//p^q
        vector<int64_t> fact_no_p, tcaf_no_p;
        binomial_primepower(int64_t p, int64_t q) : p(p), q(q){
            for(int64_t i = 0; i < q; i++) mod *= p;
            fact_no_p.resize(mod);
            tcaf_no_p.resize(mod);
            fact_no_p[0] = 1;
            for(int64_t i = 1; i < mod; i++) fact_no_p[i] = (i % p) ? fact_no_p[i-1] * i % mod : fact_no_p[i-1];
            tcaf_no_p[mod-1] = 1;
            int64_t rhs = fact_no_p[mod-1];
            int64_t exp = mod - 2;
            while (exp) {
                if(exp % 2) tcaf_no_p[mod-1] = tcaf_no_p[mod-1] * rhs % mod;
                rhs = rhs * rhs % mod;
                exp /= 2;
            }
            for(int64_t i = mod-2; i >= 0; i--) tcaf_no_p[i] = ((i+1) % p) ? tcaf_no_p[i+1] * (i+1) % mod : tcaf_no_p[i+1];
        }
        int64_t nCk(int64_t n, int64_t k){
            int64_t res = 1;
            int64_t r = n - k;
            int64_t Lg0 = 0, Lgm = 0;
            for(int64_t u = n/p; u > 0; u /= p) Lg0 += u;
            for(int64_t u = k/p; u > 0; u /= p) Lg0 -= u;
            for(int64_t u = r/p; u > 0; u /= p) Lg0 -= u;
            for(int64_t u = n/mod; u > 0; u /= p) Lgm += u;
            for(int64_t u = k/mod; u > 0; u /= p) Lgm -= u;
            for(int64_t u = r/mod; u > 0; u /= p) Lgm -= u;
            while(n > 0){
                res = res * fact_no_p[n % mod] % mod * tcaf_no_p[k % mod] % mod * tcaf_no_p[r % mod] % mod;
                n /= p; k /= p; r /= p;
            }
            while(Lg0--) res = res * p % mod;
            if((not (p == 2 and q >= 3)) and (Lgm & 1) and res) res = mod - res;
            return res;
        }
    };
    struct CRT{
        int64_t MOD;
        CRT(int64_t mod) : MOD(mod){}
        inline int64_t mod(int64_t a, int64_t m) {
            int64_t res = a % m;
            if (res < 0) res += m;
            return res;
        }

        int64_t extGCD(int64_t a, int64_t b, int64_t &p, int64_t &q) {
            if (b == 0) { p = 1; q = 0; return a; }
            int64_t d = extGCD(b, a%b, q, p);
            q -= a/b * p;
            return d;
        }

        int64_t modinv(int64_t a, int64_t m) {
            int64_t x, y;
            extGCD(a, m, x, y);
            return mod(x, m);
        }

        int64_t Garner(vector<int64_t> b, vector<int64_t> m) {
            m.push_back(MOD); // banpei
            vector<int64_t> coeffs((int)m.size(), 1);
            vector<int64_t> constants((int)m.size(), 0);
            for (int k = 0; k < (int)b.size(); ++k) {
                int64_t t = mod((b[k] - constants[k]) * modinv(coeffs[k], m[k]), m[k]);
                for (int i = k+1; i < (int)m.size(); ++i) {
                    (constants[i] += t * coeffs[i]) %= m[i];
                    (coeffs[i] *= m[k]) %= m[i];
                }
            }
            return constants.back();
        }
    };
    vector<binomial_primepower> bpp;
};
