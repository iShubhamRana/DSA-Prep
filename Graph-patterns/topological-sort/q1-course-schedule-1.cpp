// Cycle Detection Problem
// Method 1 : DFS DIRECTED CYCLE DETECTION
class Solution
{
    bool dfs(int node, vector<int> adj[], bool vis[], bool curr[])
    {
        vis[node] = true;
        curr[node] = true;

        for (auto &i : adj[node])
        {
            if (vis[i] == false)
            {
                if (dfs(i, adj, vis, curr) == true)
                    return true;
            }
            else if (curr[i] == true)
                return true;
        }

        curr[node] = false;
        return false;
    }

public:
    bool canFinish(int n, vector<vector<int>> &prerequisites)
    {
        bool vis[n], curr[n];
        memset(vis, 0, sizeof(vis));
        memset(curr, 0, sizeof(curr));

        vector<int> adj[n];

        // generate adj list
        for (auto &r : prerequisites)
            adj[r[1]].push_back(r[0]);

        for (int i = 0; i < n; ++i)
            if (vis[i] == false && dfs(i, adj, vis, curr) == true)
                return false;

        return true;
    }
};

// Method 2 : KAHN'S ALGORITHM
class Solution
{
public:
    bool canFinish(int n, vector<vector<int>> &pre)
    {
        int in[n];
        memset(in, 0, sizeof(in));

        // create adj
        vector<int> adj[n];
        for (auto &r : pre)
            adj[r[1]].push_back(r[0]);

        // indegrees
        for (auto &r : pre)
            ++in[r[0]];

        int cnt = 0; // courses that can be done
        queue<int> q;

        for (int i = 0; i < n; ++i)
            if (in[i] == 0)
                q.push(i), ++cnt;

        while (q.size())
        {
            int node = q.front();
            q.pop();

            for (auto &i : adj[node])
                if (--in[i] == 0)
                    q.push(i), ++cnt;
        }

        return cnt == n;
    }
};
