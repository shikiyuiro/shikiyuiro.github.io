int64_t inversion(vector<int64_t> &v){
    vector<int64_t> st = v;
    sort(st.begin(), st.end());
    st.erase(unique(st.begin(), st.end()), st.end());
    vector<int64_t> table(st.size()+1);
    for(auto e : v){
        int64_t a = st.size() + (st.begin() - lower_bound(st.begin(), st.end(), e)), b = a - 1;
        for(;a < table.size(); a += (a & -a)) ++table[a];
        for(;b > 0; b -= (b & -b)) table[0] += table[b];
    }
    return table[0];
}
