class WaveletMatrix{
    using i64 = int64_t;
public:
    explicit WaveletMatrix() = default;
    WaveletMatrix(vector<i64> &_v){ __WaveletMatrix(_v);};
    i64 range_freq(i64 L, i64 R, i64 lower, i64 upper){ return __range_freq(L, R, upper) - __range_freq(L, R, lower);}
    i64 range_Kthmin(i64 L, i64 R, i64 K){ return __range_Kthmin_assignXOR(L, R, K, 0);}
    i64 range_Kthmax(i64 L, i64 R, i64 K){ return __range_Kthmin_assignXOR(L, R, R - L - K - 1, 0);}
    i64 range_successor(i64 L, i64 R, i64 value){ i64 C = __range_freq(L, R, value + 1); return C == R - L ? -1 : __range_Kthmin_assignXOR(L, R, C, 0);}
    i64 range_predecessor(i64 L, i64 R, i64 value){ i64 C = __range_freq(L, R, value); return C == 0 ? -1 : __range_Kthmin_assignXOR(L, R, C - 1, 0);}
    i64 range_min_assignXOR(i64 L, i64 R, i64 value){ return __range_Kthmin_assignXOR(L, R, 0, value);}
    i64 range_max_assignXOR(i64 L, i64 R, i64 value){ return __range_Kthmin_assignXOR(L, R, R - L - 1, value);}
    i64 range_Kthmin_assignXOR(i64 L, i64 R, i64 K, i64 value){ return __range_Kthmin_assignXOR(L, R, K, value);}
    i64 range_Kthmax_assignXOR(i64 L, i64 R, i64 K, i64 value){ return __range_Kthmin_assignXOR(L, R, R - L - K - 1, value);}
private:
    vector<i64> Matrix;
    i64 bitsize;
    i64 prefixsize;
    void __WaveletMatrix(vector<i64> v){
        for(auto &e : v) assert(0 <= e and e < INT64_MAX);
        i64 v_max = *max_element(v.begin(), v.end()) + 1;
        bitsize = 64 - __builtin_clzll(v_max);
        prefixsize = v.size()+1;
        Matrix.resize(prefixsize * bitsize);
        for(i64 h = bitsize - 1; h >= 0; h--){
            for(i64 i = 0; i < v.size(); i++){
                Matrix[i+1 + prefixsize * h] = Matrix[i + prefixsize * h] + (v[i] >> h & 1);
            }
            stable_sort(v.begin(), v.end(), [&](auto a, auto b){ return (a >> h & 1) < (b >> h & 1);});
        }
    };
    i64 __range_freq(i64 L, i64 R, i64 upper){
        if((uint64_t)upper >= ((uint64_t)1 << bitsize)) return R - L;
        if(upper < 0) return 0;
        i64 res = 0;
        for(i64 h = bitsize - 1; h >= 0; h--){
            auto [L0, R0, L1, R1] = decomp(L, R, h);
            if(upper & ((i64)1 << h)){
                res += R0 - L0;
                tie(L, R) = {L1, R1};
            }else{
                tie(L, R) = {L0, R0};
            }
        }
        return res;
    };
    i64 __range_Kthmin_assignXOR(i64 L, i64 R, i64 K, i64 value){
        i64 res = 0;
        for(i64 h = bitsize - 1; h >= 0; h--){
            auto [L0, R0, L1, R1] = decomp(L, R, h);
            if(value & ((i64)1 << h)){
                swap(L0, L1); swap(R0, R1);
            }
            if(K < R0 - L0){
                tie(L, R) = {L0, R0};
            }else{
                K -= (R0 - L0);
                res |= (i64)1 << h;
                tie(L, R) = {L1, R1};
            }
        }
        return res;
    }
    tuple<i64,i64,i64,i64> decomp(i64 L, i64 R, i64 h){
        return tuple<i64,i64,i64,i64>({
            L - Matrix[L + prefixsize * h],
            R - Matrix[R + prefixsize * h],
            prefixsize - 1 - Matrix[prefixsize * (h+1) - 1] + Matrix[L + prefixsize * h],
            prefixsize - 1 - Matrix[prefixsize * (h+1) - 1] + Matrix[R + prefixsize * h]
        });
    }
};
