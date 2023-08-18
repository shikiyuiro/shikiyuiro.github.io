template<class S, S (*op)(S, S), S (*e)()>
class SWAG{
public:
    void push(S x){
        push_st.push_back({x, op(push_st.empty() ? e() : push_st.back().second, x)});
    }
    void pop(){
        if(refill()) return;
        pop_st.pop_back();
    }
    S fold(){
        return op(pop_st.empty() ? e() : pop_st.back().second, push_st.empty() ? e() : push_st.back().second);
    }
    size_t size(){
        return push_st.size() + pop_st.size();
    }
    S operator[](int64_t pos){
        return (pos < pop_st.size() ? pop_st[pop_st.size() - pos - 1].first : push_st[pos - pop_st.size()].first);
    }
private:
    vector<pair<S,S>> push_st, pop_st;
    bool refill(){
        if(pop_st.empty()) while(not push_st.empty()){
            pop_st.push_back({push_st.back().first, op(push_st.back().first, pop_st.empty() ? e() : pop_st.back().second)});
            push_st.pop_back();
        }
        return SWAG::size() == 0;
    }
};
