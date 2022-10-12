class Span_xor{
public:
    vector<int64_t> st;
    Span_xor(){}
    bool push(int64_t x){
        for(auto e : st) x = min(x, x^e);
        if(x == 0) return false;
        else st.push_back(x);
        return true;
    }
    bool contain(int64_t x){
        for(auto e : st) x = min(x, x^e);
        return x == 0;
    }
    void sweep(){
        sort(st.begin(), st.end());
        int64_t broom = ~(int64_t)0;
        for(auto &e : st){
            e &= broom;
            broom &= ~e;
        }
    }
};
