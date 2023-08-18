vector<pair<int64_t,int64_t>> CartesianTree(vector<int64_t> &A){
    // the root is min_element(A.begin(), A.end()) - A.begin();
    int64_t N = A.size();
    vector<pair<int64_t,int64_t>> res(N, {-1, -1});
    stack<int64_t> stk;
    stack<int64_t> poped;
    A.push_back(INT64_MIN);
    stk.push(N);
    for(int64_t i = 0; i <= N; i++){
        while(A[stk.top()] > A[i]){
            poped.push(stk.top()); stk.pop();
        }
        stk.push(i);
        int64_t parent = i;
        while(not poped.empty()){
            if(parent < N){
                (poped.top() < parent ? res[parent].first : res[parent].second) = poped.top();
            }
            parent = poped.top();
            poped.pop();
        }
    }
    A.pop_back();
    return res;
}