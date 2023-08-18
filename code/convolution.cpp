#include<bits/stdc++.h>
using namespace std;

/*
 mod998244353の畳み込み
 両方の配列のサイズが2^19 = 524288以下であれば安全である。
 (テストしていないが、配列のサイズの和がNが2^23-1 = 8388606以下であれば大丈夫だと思う。)
 Verified with:https://judge.yosupo.jp/submission/148581
*/

struct FFT998{
    vector<int64_t> root;
    vector<int64_t> invroot;
    vector<int64_t> invpow2;
    FFT998(){
        root.push_back(15311432);
        invroot.push_back(469870224);
        invpow2.push_back(1);
        for(int64_t i = 0; i < 23; i++){
            root.push_back(root.back()*root.back()%998244353);
            invroot.push_back(invroot.back()*invroot.back()%998244353);
            invpow2.push_back(invpow2.back()*499122177%998244353);
        }
        reverse(root.begin(), root.end());
        reverse(invroot.begin(), invroot.end());
    }

    vector<int64_t> NTT(vector<int64_t> A, bool inversed, int64_t log2_siz){
        const int N = A.size();
        assert(1LL<<log2_siz == N);
        if(N == 1) return A;
        vector<int64_t> even(N / 2), odd(N / 2);
        for(int i = 0; i < N / 2; i++){
            even[i] = A[i * 2];
            odd[i] = A[i * 2 + 1];
        }
        even = NTT(even, inversed, log2_siz-1);
        odd = NTT(odd, inversed, log2_siz-1);
        int64_t rootprod = 1;
        for(int i = 0; i < N / 2; i++){
            odd[i] *= rootprod;
            odd[i] %= 998244353;
            A[i] = (even[i] + odd[i]) % 998244353;
            A[N / 2 + i] = (even[i] - odd[i] + 998244353) % 998244353;
            rootprod *= (inversed ? invroot[log2_siz] : root[log2_siz]);
            rootprod %= 998244353;
        }
        return A;
    }

    vector<int64_t> FPSmultiple(vector<int64_t> A, vector<int64_t> B){
        int64_t rsiz = A.size()+B.size()-1;
        int64_t psiz = 1;
        int64_t logp = 0;
        while(psiz < rsiz){
            psiz *= 2;
            logp++;
        }
        A.resize(psiz, 0);
        B.resize(psiz, 0);
        auto fa = NTT(A, false, logp);
        auto fb = NTT(B, false, logp);
        vector<int64_t> fab;
        for(int64_t i = 0; i < psiz; i++) fab.push_back(fa[i]*fb[i]%998244353);
        auto ab = NTT(fab, true, logp);
        vector<int64_t> res;
        for(auto e : ab) res.push_back(e * invpow2[logp] % 998244353);
        res.resize(rsiz);
        return res;
    }
};

int main(){
    //sample
    cin.tie(nullptr)->ios::sync_with_stdio(false);
    vector<int64_t> A = {3, 1, 4};
    vector<int64_t> B = {1, 5, 9, 2, 6};
    FFT998 FFT;
    auto C = FFT.FPSmultiple(A, B);
    for(auto c : C) cout << c << " ";
    cout << '\n';
    //3 16 36 35 56 14 24 
}