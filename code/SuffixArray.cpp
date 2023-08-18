vector<int64_t> SuffixArray(vector<int64_t> &s){
    s.push_back(-1);
    vector<int64_t> rank = s;
    vector<int64_t> res(s.size()); iota(res.begin(), res.end(), 0);
    stable_sort(res.begin(), res.end(), [&](auto a, auto b){return rank[a] < rank[b];});
    int64_t siz = 1;
    while(siz < s.size()){
        stable_sort(res.begin(), res.end(), [&](auto a, auto b){return rank[a] == rank[b] ? rank[min((int64_t)res.size()-1, a+siz)] <= rank[min((int64_t)res.size()-1, b+siz)] : rank[a] <= rank[b];});
        auto tmp = rank;
        for(int64_t i = 1; i < s.size(); i++){
            rank[res[i]] = rank[res[i-1]];
            if(tmp[res[i-1]] < tmp[res[i]] or tmp[min((int64_t)res.size()-1, res[i-1]+siz)] < tmp[min((int64_t)res.size()-1, res[i]+siz)]){
                rank[res[i]]++;
            }
        }
        siz <<= 1;
    }
    res.erase(res.begin());
    return res;
}
 
vector<int64_t> SuffixArray(string &S){
    int64_t N = S.size();
    vector<int64_t> res(N);
    for(int64_t i = 0; i < N; i++) res[i] = S[i];
    return SuffixArray(res);
}
