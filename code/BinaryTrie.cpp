class BinaryTrie{
    struct Node{
        shared_ptr<Node> par, c0, c1;
        bool exist = false;
        int64_t weight = 0;
        Node(shared_ptr<Node> par = nullptr) : par(par){};
    };
    shared_ptr<Node> Root;
    shared_ptr<Node> Pos;
public:
    BinaryTrie(){
        Root = shared_ptr<Node>(new Node());
        Pos = Root;
    }
    void insert(int64_t val){ __insert(val, true);}
    void erase(int64_t val){ __insert(val, false);}
    int64_t freq(int64_t lower, int64_t upper){ return __freq(upper) - __freq(lower);} //[lower, upper)
    int64_t successor(int64_t value){ int64_t F = __freq(value + 1); return F == Root->weight ? -1 : __Kth_min_assignXor(F, 0);}
    int64_t predecessor(int64_t value){ int64_t F = __freq(value); return F == 0 ? -1 : __Kth_min_assignXor(F - 1, 0);}
    int64_t min_assignXor(int64_t rev){ return __Kth_min_assignXor(0, rev);}
    int64_t max_assignXor(int64_t rev){ return __Kth_min_assignXor(Root->weight - 1, rev);}
    int64_t Kth_min(int64_t k){ return __Kth_min_assignXor(k, 0);}
    int64_t Kth_max(int64_t k){ return __Kth_min_assignXor(Root->weight - k - 1, 0);}
    int64_t Kth_min_assignXor(int64_t k, int64_t rev){ return __Kth_min_assignXor(k, rev);}
    int64_t Kth_max_assignXor(int64_t k, int64_t rev){ return __Kth_min_assignXor(Root->weight - k - 1, rev);}
private:
    void go_0(){
        if(Pos->c0 == nullptr){
            Pos->c0 = shared_ptr<Node>(new Node(Pos));
        }
        Pos = Pos->c0;
    }
    void go_1(){
        if(Pos->c1 == nullptr){
            Pos->c1 = shared_ptr<Node>(new Node(Pos));
        }
        Pos = Pos->c1;
    }
    void go_back(){
        if(Pos != Root) Pos = Pos->par;
    }
    void go_root(){
        Pos = Root;
    }
    void __insert(int64_t val, bool existence){
        assert(val >= 0);
        for(int64_t b = 62; b >= 0; b--){
            if(val&((int64_t)1<<b)) go_1();
            else go_0();
        }
        if(Pos->exist == existence){
            go_root();
            return;
        }
        Pos->exist = existence;
        Pos->weight += (existence ? 1 : -1);
        do{
            go_back();
            Pos->weight += (existence ? 1 : -1);
        }while(Pos != Root);
    }
    int64_t __freq(int64_t upper){
        if(Root->weight <= 0) return 0;
        int64_t res = 0;
        for(int64_t b = 62; b >= 0; b--){
            if(upper&((int64_t)1<<b)){
                if(Pos->c0) res += Pos->c0->weight;
                if(Pos->c1) go_1();
                else break;
            }
            else{
                if(Pos->c0) go_0();
                else break;
            }
        }
        go_root();
        return res;
    }
    int64_t __Kth_min_assignXor(int64_t k, int64_t rev){
        if(Root->weight <= k) return -1;
        int64_t res = 0;
        for(int64_t b = 62; b >= 0; b--){
            if(rev&((int64_t)1<<b)){
                if(Pos->c1){
                    if(Pos->c1->weight > k){
                        go_1();
                        continue;
                    }else{
                        k -= Pos->c1->weight;
                    }
                }
                go_0();
            }
            else{
                if(Pos->c0){
                    if(Pos->c0->weight > k){
                        go_0();
                        continue;
                    }else{
                        k -= Pos->c0->weight;
                    }
                }
                go_1();
            }
            res |= ((int64_t)1<<b);
        }
        go_root();
        return res;
    }
};
