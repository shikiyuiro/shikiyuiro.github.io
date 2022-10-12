template<class S, S (*op)(S, S), S (*e)()>
class SWAG{
public:
    void push(S x){
        push_st.push({x, op(push_st.empty() ? e() : push_st.top().second, x)});
    }
    void pop(){
        if(not refill()) return;
        pop_st.pop();
    }
    S fold(){
        return op(pop_st.empty() ? e() : pop_st.top().second, push_st.empty() ? e() : push_st.top().second);
    }
    S front(){
        if(not refill()) return e();
        return pop_st.top().first;
    }
    size_t size(){
        return push_st.size() + pop_st.size();
    }
private:
    stack<pair<S,S>> push_st, pop_st;
    bool refill(){
        if(pop_st.empty()){
            if(push_st.empty()) return false;
            pop_st.push({push_st.top().first, push_st.top().first});
            push_st.pop();
            while(not push_st.empty()){
                pop_st.push({push_st.top().first, op(push_st.top().second, pop_st.top().second)});
                push_st.pop();
            }
        }
        return true;
    }
};
