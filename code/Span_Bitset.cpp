template<int64_t Siz>
class Span_bitset{
public:
    vector<bitset<Siz>> st;
    bitset<Siz>pan_xor(){}
    bool push(bitset<Siz> x){
        for(auto e : st) x = min(x, x^e);
        if(x.none()) return false;
        else st.push_back(x);
        return true;
    }
    bool contain(bitset<Siz> x){
        for(auto e : st) x = min(x, x^e);
        return x.none();
    }
    void sweep(){
        sort(st.begin(), st.end(), [&](auto a, auto b){return a == min(a, b);});
        bitset<Siz> broom = 0; broom = ~broom;
        for(auto &e : st){
            e &= broom;
            broom &= ~e;
        }
    }
private:
    bitset<Siz> min(bitset<Siz> a, bitset<Siz> b){
        bitset<Siz> x = a ^ b;
        if(x.none()) return a;
        int64_t pass = 0, fail = Siz;
        while(fail - pass > 1) (((x >> (pass + (fail - pass) / 2)).any())?pass:fail) = (pass + (fail - pass) / 2);
        return a[pass] ? b : a;
    }
};
