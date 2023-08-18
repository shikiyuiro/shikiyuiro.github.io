vector<vector<pair<int,int>>> enumomino(int N){
    //Redelmeier's Algorithm
    vector<vector<pair<int,int>>> res;
    vector<pair<int,int>> now;
    vector<pair<int,int>> que;
    vector<vector<bool>> queued(N, vector<bool>(2*N-1, false));
    now.push_back({0, 0});
    que.push_back({0, 0});
    queued[0][N-1] = true;
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    auto dfs = [&](auto &&self, int quepos) -> void {
        if(now.size() == N){
            res.push_back(now);
            return;
        }
        auto [x, y] = now.back();
        int q = 0;
        for(int d = 0; d < 4; d++){
            if(x+dx[d] < 0) continue;
            if(x+dx[d] == 0 and y+dy[d] < 0) continue;
            if(queued[x+dx[d]][y+dy[d]+N-1]) continue;
            q++;
            que.push_back({x+dx[d], y+dy[d]});
            queued[x+dx[d]][y+dy[d]+N-1] = true;
        }
        for(int i = quepos+1; i < que.size(); i++){
            auto [qx, qy] = que[i];
            now.push_back({qx, qy});
            self(self, i);
            now.pop_back();
        }
        while(q--){
            queued[que.back().first][que.back().second+N-1] = false;
            que.pop_back();
        }
    };
    dfs(dfs, 0);
    return res;
}
