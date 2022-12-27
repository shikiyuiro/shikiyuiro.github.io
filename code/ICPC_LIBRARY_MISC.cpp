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
//こおりのぬけみち
class skate{
public:
skate(int64_t H, int64_t W, vector<pair<int64_t,int64_t>> &wall) : H(H), W(W), wall_xy(wall), wall_yx(wall){
    sort(wall_xy.begin(), wall_xy.end());
    for(auto &[x, y] : wall_yx) swap(x, y);
    sort(wall_yx.begin(), wall_yx.end());
}
pair<int64_t,int64_t> leftward(int64_t x, int64_t y){
    int64_t pass = y, fail = -1;
    while(pass - fail > 1){
        int64_t mid = fail + (pass - fail) / 2;
        (upper_bound(wall_xy.begin(), wall_xy.end(), pair<int64_t,int64_t>{x, y}) - lower_bound(wall_xy.begin(), wall_xy.end(), pair<int64_t,int64_t>{x, mid}) == 0 ? pass : fail) = mid;
    }
    return {x, pass};
}
pair<int64_t,int64_t> rightward(int64_t x, int64_t y){
    int64_t pass = y, fail = W;
    while(fail - pass > 1){
        int64_t mid = pass + (fail - pass) / 2;
        (upper_bound(wall_xy.begin(), wall_xy.end(), pair<int64_t,int64_t>{x, mid}) - lower_bound(wall_xy.begin(), wall_xy.end(), pair<int64_t,int64_t>{x, y}) == 0 ? pass : fail) = mid;
    }
    return {x, pass};
}
pair<int64_t,int64_t> upward(int64_t x, int64_t y){
    int64_t pass = x, fail = -1;
    while(pass - fail > 1){
        int64_t mid = fail + (pass - fail) / 2;
        (upper_bound(wall_yx.begin(), wall_yx.end(), pair<int64_t,int64_t>{y, x}) - lower_bound(wall_yx.begin(), wall_yx.end(), pair<int64_t,int64_t>{y, mid}) == 0 ? pass : fail) = mid;
    }
    return {pass, y};
}
pair<int64_t,int64_t> downward(int64_t x, int64_t y){
    int64_t pass = x, fail = H;
    while(fail - pass > 1){
        int64_t mid = pass + (fail - pass) / 2;
        (upper_bound(wall_yx.begin(), wall_yx.end(), pair<int64_t,int64_t>{y, mid}) - lower_bound(wall_yx.begin(), wall_yx.end(), pair<int64_t,int64_t>{y, x}) == 0 ? pass : fail) = mid;
    }
    return {pass, y};
}
private:
int64_t H, W;
vector<pair<int64_t,int64_t>> wall_xy, wall_yx;
};
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
//幾何
using real_t = long double;
const real_t EPS = 1e-9;
bool EPSeq(real_t a, real_t b){return abs(a - b) < EPS;}
struct Point{
    real_t x, y;
    constexpr Point(const real_t x = 0, const real_t y = 0) noexcept : x(x), y(y) {}
    constexpr Point operator+(const Point rhs) const noexcept {
        return Point(*this) += rhs;
    }
    constexpr Point operator-(const Point rhs) const noexcept {
        return Point(*this) -= rhs;
    }
    constexpr Point operator*(const real_t r) const noexcept {
        return Point(*this) *= r;
    }
    constexpr Point operator/(const real_t r) const noexcept {
        return Point(*this) /= r;
    }
    constexpr Point &operator+=(const Point rhs) noexcept {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
    constexpr Point &operator-=(const Point rhs) noexcept {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }
    constexpr Point &operator*=(const real_t r) noexcept {
        x *= r;
        y *= r;
        return *this;
    }
    constexpr Point &operator/=(const real_t r) noexcept {
        assert(r != 0);
        x /= r;
        y /= r;
        return *this;
    }
    friend istream &operator>>(istream &is, Point &p) {
        real_t a, b;
        is >> a >> b;
        p = Point(a, b);
        return is;
    }
    friend ostream &operator<<(ostream &os, Point &p) {
        return os << p.x << " " << p.y;
    }
    friend bool operator<(const Point &a, const Point &b) {
        //辞書順
        return a.x != b.x ? a.x < b.x : a.y < b.y;
    }
    real_t dot(Point P){
        auto [xp, yp] = P;
        return x*xp + y*yp;
    }
    real_t cross(Point P){
        auto [xp, yp] = P;
        return x*yp - y*xp;
    }
};

struct Line{
    real_t A, B, C;//Ax+By+C=0
    Line(){}
    Line(Point Pa, Point Pb){
        A = (Pa.y - Pb.y);
        B = -(Pa.x - Pb.x);
        C = Pa.x * Pb.y - Pa.y * Pb.x;
        if(EPSeq(C, 0)) C = 0;
    }
    Line(Point P, real_t slope){
        tie(A, B, C) = tuple{slope, -1, -slope*P.x+P.y};
    }
    Line(real_t a, real_t b, real_t c) : A(a), B(b), C(c){}
};
struct Circle{
    Point O;
    real_t r;
    Circle(Point center, real_t radius) : O(center), r(radius){}
};
vector<Point> arg_sort(vector<Point> &V){
    sort(V.begin(), V.end(), [&](Point a, Point b){
        if(EPSeq(a.x, 0) and EPSeq(a.y, 0)) return false;
        if(EPSeq(b.x, 0) and EPSeq(b.y, 0)) return true;
        pair<real_t,real_t> ainv = {a.y, a.x}, binv = {b.y, b.x};
        pair<real_t,real_t> zero = {0, 0};
        if(ainv > zero and zero > binv) return false;
        if(binv > zero and zero > ainv) return true;
        return a.x * b.y > a.y * b.x;
    });
    return V;
}
Point projection(Line L, Point P){
    real_t L_D = L.B * P.x - L.A * P.y;
    return {(L.B*L_D-L.A*L.C)/(L.A*L.A+L.B*L.B), -(L.A*L_D+L.B*L.C)/(L.A*L.A+L.B*L.B)};
}
Point reflection(Line L, Point P){
    Point prj = projection(L, P);
    return prj+prj-P;
}
pair<pair<Point,Point>,bool> intersection(Line L, Circle C){
    auto [a, b, c] = L;
    auto [o, r] = C;
    c += a*o.x + b*o.y;
    real_t D = (a*a + b*b) * r*r - c*c;
    if(D < 0 and (not EPSeq(D, 0))) return {{o, o}, false};
    real_t sqD = sqrtl(abs(D));
    Point prj = {-a*c/(a*a+b*b), -b*c/(a*a+b*b)};
    Point k = {b * sqD / (b*b+a*a), -a * sqD / (b*b+a*a)};
    return {{prj+k, prj-k}, true};
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
