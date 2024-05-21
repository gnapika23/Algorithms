#include<iostream>
#include<vector>
using namespace std;

vector<pair<int, pair<int, int>>> edges;
int parent[1000001];

int find(int x){
    if(parent[x] == x){
        return x;
    }
    return parent[x] = find(parent[x]);
}

void merge(int x, int y){
    parent[find(x)] = find(y);
}

int kruskal(int n){
    sort(edges.begin(), edges.end());
    int mst = 0;
    for(auto it: edges){
        int u = it.second.first;
        int v = it.second.second;
        int weight = it.first;
        if(find(u) != find(v)){
            mst += weight;
            merge(u, v);
        }
    }
    return mst;
}

int main(){
    int n, m;
    cin >> n >> m;
    for(int i=0;i<m;i++){
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({w, {u, v}});
    }

    for(int i=1;i<=n;i++){
        parent[i] = i;
    }

    int components = 0;
    for(int i=1;i<=n;i++){
        if(parent[i] == i){
            components++;
        }
    }

    cout << "Number of connected components: " << components << endl;

    int mst_weight = kruskal(n);
    cout << "Weight of Minimum Spanning Tree: " << mst_weight << endl;

    return 0;
}
