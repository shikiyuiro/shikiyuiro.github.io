//Kinetic Tournament　の実装メモ
//クエリが単調であることを条件に、実装を単純(実用上も高速になる)にした Dynamic CHT ともみなせるデータ構造。(セグ木ベースなので、範囲クエリもできる)
//完全二分木として実装する。
//データ構造はgrobalな変数TEMPをもつ。(これは「温度」とみなされる。)
//葉には温度に対する一次関数を持たせる。
//葉でない全てのノード(親ノードとする)は子孫のうちTEMPにおいて最小値をとりうる一次関数を持つ。
//一次関数の性質から、親ノードの直接の子が変化しない場合、ある温度において、最小値をとる子は高々1回だけ入れ替わる(これはCodeForcesの記事でmeltと表現されている)。
//そこで、各親ノードについて、自分を含めたすべての子孫ノードについてのmeltが起こる温度の最小値を持たせておく。これを「融点」とする。
//(直感的には融点とはすべての部分木について、「どのタイミングで再計算が必要か」を記録したものとみなせる。)
//set および fold: セグ木と同じ。ただし、setは操作後に先祖をmeltさせる必要がある。
//heaten: 温度TEMPを上昇させる(減少させることはできない)。ボトムアップに親ノードを見ていき、融点がTEMP以下であるような全ての親ノードに対して、meltを行う。

class KineticTournament{
public:
    KineticTournament(int64_t siz){
        while(size < siz) size <<= 1;
        seg.resize(size << 1, {INT32_MIN, INT64_MAX >> 1});
        melting_point.resize(size << 1, INT64_MAX);
    }
    void heaten(int64_t nxtTEMP){
        assert(TEMP <= nxtTEMP);
        TEMP = nxtTEMP;
        recalc(1);
    }
    void set(int64_t pos, int64_t A, int64_t B){
        pos += size;
        seg[pos] = {A, B};
        while(pos > 1){
            pos >>= 1;
            melting_point[pos] = INT64_MIN;
        }
        recalc(1);
    }
    int64_t fold(int64_t L, int64_t R){ //[L, R)
        int64_t res = INT64_MAX;
        L += size; R += size;
        while(L < R){
            if(L & 1){ res = min(res, seg[L].first * TEMP + seg[L].second); L++;}
            if(R & 1){ --R; res = min(seg[R].first * TEMP + seg[R].second, res);}
            L >>= 1; R >>= 1;
        }
        return res;
    }
private:
    int64_t size = 1;
    int64_t TEMP = INT32_MIN;
    vector<pair<int64_t,int64_t>> seg;
    vector<int64_t> melting_point;
    int64_t eval_melting_point(int64_t pos){
        auto [La, Lb] = seg[pos<<1|0];
        auto [Ra, Rb] = seg[pos<<1|1];
        if(La == Ra) return INT64_MAX;
        int64_t T = ceil_intdiv(Lb-Rb, Ra-La);
        return (TEMP < T ? T : INT64_MAX);
    }
    void melt(int64_t pos){ //seg[pos]を子孫のうち、TEMP以降で最小値をとるほうに入れ替える。
        int64_t Lval = seg[pos<<1|0].first * TEMP + seg[pos<<1|0].second;
        int64_t Rval = seg[pos<<1|1].first * TEMP + seg[pos<<1|1].second;
        if(Lval == Rval){
            seg[pos] = min(seg[pos<<1|0], seg[pos<<1|1]);
        }else{
            seg[pos] = (Lval < Rval ? seg[pos<<1|0] : seg[pos<<1|1]);
        }
    }
    void recalc(int64_t pos){ //pos以下の部分木の再計算
        if(melting_point[pos] > TEMP) return;
        recalc(pos<<1|0);
        recalc(pos<<1|1);
        melting_point[pos] = min(melting_point[pos<<1|0], melting_point[pos<<1|1]);
        melting_point[pos] = min(melting_point[pos], eval_melting_point(pos));
        melt(pos);
    }
    int64_t ceil_intdiv(int64_t nume, int64_t deno){
        return (nume < 0 xor deno < 0 ? -(abs(nume) / abs(deno)) : (abs(nume) + abs(deno) - 1) / abs(deno));
    }
};