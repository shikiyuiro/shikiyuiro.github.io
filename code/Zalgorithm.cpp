//ACLから窃盗
template <class T>
vector<int64_t> zalgo(vector<T>& s) {
    int64_t N = s.size();
    vector<int64_t> res(N);
    res[0] = 0;
    for (int64_t i = 1, j = 0; i < N; i++) {
        int64_t& k = res[i];
        k = (i < j + res[j]) ? min(j + res[j] - i, res[i - j]) : 0;
        while (i + k < N and s[k] == s[i + k]) k++;
        if (j + res[j] < i + res[i]) j = i;
    }
    res[0] = N;
    return res;
}

vector<int64_t> zalgo(string S){
    int64_t N = S.size();
    vector<int64_t> res(N);
    for(int64_t i = 0; i < N; i++) res[i] = S[i];
    res = zalgo<int64_t>(res);
    return res;
}
