//TODO:もっと簡潔に書く
class ConvexHullTrick{
public:
    ConvexHullTrick(){}
    void add_line(pair<int64_t,int64_t> Line){
        auto [a, b] = Line;
        auto itr = a2b.find(a);
        if(itr != a2b.end()){
            if(itr->second <= b) return;
            itr->second = b;
        }else{
            itr = a2b.insert({a, b}).first;
        }
        if(not check(a)){
            if(a2r.find(a) != a2r.end()){
                if(r2a.find(a2r[a]) != r2a.end()) r2a.erase(r2a.find(a2r[a]));
                a2r.erase(a2r.find(a));
            }
            a2b.erase(itr);
            return;
        };
        if(itr != a2b.begin()){
            auto pitr = prev(itr);
            while(not check(pitr->first)){
                if(a2r.find(pitr->first) != a2r.end()){
                    if(r2a.find(a2r[pitr->first]) != r2a.end()) r2a.erase(r2a.find(a2r[pitr->first]));
                    a2r.erase(a2r.find(pitr->first));
                }
                pitr = prev(pitr);
                a2b.erase(next(pitr));
            }
        }
        if(next(itr) != a2b.end()){
            auto nitr = next(itr);
            while(not check(nitr->first)){
                if(a2r.find(nitr->first) != a2r.end()){
                    if(r2a.find(a2r[nitr->first]) != r2a.end()) r2a.erase(r2a.find(a2r[nitr->first]));
                    a2r.erase(a2r.find(nitr->first));
                }
                nitr = next(nitr);
                a2b.erase(prev(nitr));
            }
        }
        if(next(itr) != a2b.end()){
            auto [La, Lb] = *next(itr);
            if(a2r.find(La) != a2r.end()) if(r2a.find(a2r[La]) != r2a.end()) r2a.erase(r2a.find(a2r[La]));
            a2r[La] = intfloor(Lb - b, a - La);
            r2a[intfloor(Lb - b, a - La)] = La;
        }
        if(itr == a2b.begin()){
            if(a2r.find(a) != a2r.end()) if(r2a.find(a2r[a]) != r2a.end()) r2a.erase(r2a.find(a2r[a]));
            a2r[a] = INT64_MAX;
            r2a[INT64_MAX] = a;
        }else{
            auto [Ra, Rb] = *prev(itr);
            if(a2r.find(a) != a2r.end()) if(r2a.find(a2r[a]) != r2a.end()) r2a.erase(r2a.find(a2r[a]));
            a2r[a] = intfloor(Rb - b, a - Ra);
            r2a[intfloor(Rb - b, a - Ra)] = a;
        }
    }
    pair<int64_t,int64_t> get_min(int64_t x){
        int64_t a = r2a.lower_bound(x)->second;
        int64_t b = a2b[a];
        return {a, b};
    }
private:
    map<int64_t,int64_t> a2b, a2r, r2a;
    bool check(int64_t a){
        auto itr = a2b.find(a);
        if(itr == a2b.begin()) return true;
        auto Litr = next(itr);
        if(Litr == a2b.end()) return true;
        auto Ritr = prev(itr);
        int64_t b = itr->second;
        auto [La, Lb] = *Litr;
        auto [Ra, Rb] = *Ritr;
        if(intfloor(Lb - b, a - La) >= intfloor(Rb - b, a - Ra)) return false;
        else return true;
    }
    int64_t intfloor(int64_t a, int64_t b){
        if(a == 0) return 0;
        if(a < 0 and b > 0) return intfloor(-a, -b);
        if(a > 0 and b > 0) return a / b;
        if(a < 0 and b < 0) return a / b;
        int64_t q = a / b;
        if(a == b * q) return q;
        else return q-1;
    }
};
