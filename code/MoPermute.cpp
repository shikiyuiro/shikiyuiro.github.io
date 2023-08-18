vector<tuple<int64_t,int64_t,int64_t>> Mo_Permute(vector<pair<int64_t,int64_t>> &query){
    vector<tuple<int64_t,int64_t,int64_t>> res;
    int64_t Rmax = 1;
    for(auto &[L, R] : query) {res.push_back({L, R, res.size()}); Rmax = max(Rmax, R);}
    int64_t sq = 1; while(sq * sq < Rmax) sq++;
    vector<int64_t> block; for(auto &[L, R] : query) block.push_back(double(L) / sq);
    sort(res.begin(), res.end(), [&](auto &a, auto &b){
        auto [La, Ra, ia] = a;
        auto [Lb, Rb, ib] = b;
        if(block[ia] != block[ib]) return block[ia] < block[ib];
        if(block[ia] & 1) return Ra > Rb; else return Ra < Rb;
    });
    return res;
}
