int64_t sqrt_floor(int64_t N){
    assert(N >= 0);
    if(N >= (int64_t)3037000499 * (int64_t)3037000499) return 3037000499;
    int64_t pass = 0;
    int64_t fail = 3037000499;
    while(fail - pass > 1){
        int64_t mid = (fail + pass) / 2;
        if(N >= mid * mid) pass = mid;
        else fail = mid;
    }
    return pass;
}

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

pair<int64_t,int64_t> Pell(int64_t N){
    //ペル方程式 x^2 - N * y^2 = 1 の 最小解を求める。 存在しない場合{-1, -1}を返す。
    if(N < 0) return {-1, -1};
    if(N <= 1) return {1, 0};
    int64_t x = 0, y = 1;
    int64_t sq = sqrt_floor(N);
    auto flac = sqrt_continue_flac(N);
    if(flac.size() == 0) return {-1, -1};
    flac.pop_back();
    for(auto &f : flac) tie(x, y) = pair<int64_t,int64_t>{y, x + y*f};
    x += y * sq;
    if(flac.size() % 2 == 0) tie(x, y) = pair<int64_t,int64_t>{x*x + N * y * y, 2 * x * y};
    return {x, y};
}

pair<int64_t,int64_t> Pell_negative(int64_t N){
    //ペル方程式 x^2 - N * y^2 = -1 の 最小解を求める。 存在しない場合{-1, -1}を返す。
    if(N < 1) return {-1, -1};
    if(N == 1) return {0, 1};
    int64_t x = 0, y = 1;
    int64_t sq = sqrt_floor(N);
    auto flac = sqrt_continue_flac(N);
    if(flac.size() % 2 == 0) return {-1, -1};
    flac.pop_back();
    for(auto &f : flac) tie(x, y) = pair<int64_t,int64_t>{y, x + y*f};
    x += y * sq;
    return {x, y};
}
