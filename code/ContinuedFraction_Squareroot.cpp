vector<int64_t> sqrt_continue_flac(int64_t N){
    //N - floor(sqrt(N))の正則連分数展開の係数を計算する。
    vector<int64_t> res;
    int64_t sq = sqrt_floor(N);
    if(sq*sq == N) return {};
    pair<int64_t,int64_t> calc = {1, sq};
    do{ auto [f, s] = calc;
        int64_t C = (N - s*s) / f;
        res.push_back((sq+s) / C);
        calc = {C, sq - (sq+s) % C};
    }while(calc.first != 1);
    return res;
}
