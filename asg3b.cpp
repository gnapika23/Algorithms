#include<iostream>
#include<queue>
using namespace std;

vector<pair<int, int>> adj[1000001];
int parent[1000001];
bool visited[1000001];

void bfs(int s){
    queue<int> q;
    q.push(s);
    visited[s] = true;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(auto it: adj[u]){
            int v = it.first;
            if(!visited[v]){
                visited[v] = true;
                parent[v] = s;
                q.push(v);
            }
        }
    }
}

int prim(int n){
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> key(n+1, INT_MAX);
    vector<bool> inMST(n+1, false);

    pq.push(make_pair(0, 1));
    key[1] = 0;

    int mst = 0;
    while(!pq.empty()){
        int u = pq.top().second;
        pq.pop();
        inMST[u] = true;
        for(auto it: adj[u]){
            int v = it.first;
            int weight = it.second;
            if(!inMST[v] && key[v] > weight){
                key[v] = weight;
                pq.push(make_pair(key[v], v));
            }
        }
    }

    for(int i=1;i<=n;i++){
        mst += key[i];
    }

    return mst;
}

int main(){
    int n, m;
    cin >> n >> m;
    for(int i=0;i<m;i++){
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    int components = 0;
    for(int i=1;i<=n;i++){
        if(!visited[i]){
            bfs(i);
            components++;
        }
    }

    cout << "Number of connected components: " << components << endl;

    int mst_weight = prim(n);
    cout << "Weight of Minimum Spanning Tree: " << mst_weight << endl;

    return 0;
}