//modint
template <std::uint_fast64_t Modulus> class modint {
  using u64 = std::uint_fast64_t;

public:
  u64 a;

  constexpr modint(const u64 x = 0) noexcept : a(x % Modulus) {}
  constexpr u64 &value() noexcept { return a; }
  constexpr const u64 &value() const noexcept { return a; }
  constexpr modint operator+(const modint rhs) const noexcept {
    return modint(*this) += rhs;
  }
  constexpr modint operator-(const modint rhs) const noexcept {
    return modint(*this) -= rhs;
  }
  constexpr modint operator*(const modint rhs) const noexcept {
    return modint(*this) *= rhs;
  }
  constexpr modint operator/(const modint rhs) const noexcept {
    return modint(*this) /= rhs;
  }
  constexpr modint &operator+=(const modint rhs) noexcept {
    a += rhs.a;
    if (a >= Modulus) {
      a -= Modulus;
    }
    return *this;
  }
  constexpr modint &operator-=(const modint rhs) noexcept {
    if (a < rhs.a) {
      a += Modulus;
    }
    a -= rhs.a;
    return *this;
  }
  constexpr modint &operator*=(const modint rhs) noexcept {
    a = a * rhs.a % Modulus;
    return *this;
  }
  constexpr modint &operator/=(modint rhs) noexcept {
    u64 exp = Modulus - 2;
    while (exp) {
      if (exp % 2) {
        *this *= rhs;
      }
      rhs *= rhs;
      exp /= 2;
    }
    return *this;
  }
};
//ベルマンフォード
vector<int64_t> BellmanFord(vector<vector<pair<int64_t,int64_t>>> edge, int64_t s){
    int64_t V = edge.size();
    vector<int64_t> res(V, INT64_MAX);
    res[s] = 0;
    if(V == 1) return res;
    int64_t T = V - 1;
    while(T--){
        for(int64_t i = 0; i < V; i++){
            for(auto &[nxt, c] : edge[i]){
                if(res[i] == INT64_MAX) continue;
                res[nxt] = min(res[nxt], res[i] + c);
            }
        }
    }
    for(int64_t i = 0; i < V; i++){
        for(auto &[nxt, c] : edge[i]){
            if(res[i] == INT64_MAX) continue;
            if(res[nxt] > res[i] + c){
                //NEGATIVE CYCLE DETECTED
                return {};
            }
        }
    }
    return res;
}
//ワーシャルフロイド
for(long k = 0; k < N; k++)
for(long i = 0; i < N; i++)
for(long j = 0; j < N; j++)
APSP[i][j] = min(APSP[i][j], APSP[i][k] + APSP[k][j]);
//乱数
random_device engine;
mt19937 rand19937(engine());
cout << rand19937() << '\n';
//下側凸包
vector<pair<int64_t,int64_t>> lower_convex(vector<pair<int64_t,int64_t>> A){
    vector<pair<int64_t,int64_t>> res;
    sort(A.begin(), A.end());
    A.erase(unique(A.begin(), A.end(), [&](auto a, auto b){return a.first == b.first;}), A.end());
    for(auto a : A){
        auto [x, y] = a;
        while(res.size() >= 2){
            auto [x0, y0] = res[res.size()-2];
            auto [x1, y1] = res[res.size()-1];
            if((x-x0)*(y1-y0) - (x1-x0)*(y-y0) > 0) res.pop_back();
            else break;
        }
        res.push_back(a);
    }
    return res;
}
//ラムダ再帰
auto dfs = [&](auto &&self/*, long vis, long parent, ...*/) -> void {

};
//平方根
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
//偏角ソート
sort(E.begin(), E.end(), [&](pair<int64_t,int64_t> a, pair<int64_t,int64_t> b){
    pair<int64_t,int64_t> zero = {0, 0};
    if(a == zero) return false;
    if(b == zero) return true;
    auto [x1, y1] = a;
    auto [x2, y2] = b;
    pair<int64_t,int64_t> ainv = {y1, x1}, binv = {y2, x2};
    if(ainv > zero and zero > binv) return false;
    if(binv > zero and zero > ainv) return true;
    return x1 * y2 > x2 * y1;
});
//ccw
int64_t ccw(pair<int64_t,int64_t> a, pair<int64_t,int64_t> b, pair<int64_t,int64_t> c) {
  b.first -= a.first; b.second -= a.second; 
  c.first -= a.first; c.second -= a.second;
  if(a == b or b == c or c == a) return 0;
  if (b.first*c.second-b.second*c.first > 0) return +1;                                       // counter clockwise
  if (b.first*c.second-b.second*c.first < 0) return -1;                                       // clockwise
  if (b.first*c.first+b.second*c.second < 0) return 100;                                      // c--a--b on line
  if (b.first*b.first+b.second*b.second - c.first*c.first-c.second*c.second > 0) return 101;  // a--c--b on line
  return 102;                                                                                 // a--b--c on line
}
