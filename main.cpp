#include <bits/stdc++.h>
#include <windows.h>
#define ll long long
#define ull unsigned long long
#define ld long double
#define print_lst_1x(lst) for (auto el: lst){cout << el << ' ';} cout << endl;
#define print_lst_2x(lst) for (auto el: lst){for (auto zn: el) {cout << zn << ' ';} cout << '\n';} cout << endl;
using namespace std;


bool bfs(int s, int t, vector <vector <int>> graf, vector <int> &parent){
    vector <bool> was (graf.size(), false);

    queue<int> q;
    q.push(s);
    was[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < graf.size(); v++) {
            if (!was[v] && graf[u][v] > 0) {
                if (v == t) {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                was[v] = true;
            }
        }
    }
    return false;
}


int ford_fulkerson_algorithm(int s, int t, vector <vector <int>> graf){
    int max_flow = 0;
    vector <int> parent(graf.size());

    while(bfs(s, t, graf, parent)){
        int path_flow = INT_MAX;

        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            path_flow = min(path_flow, graf[u][v]);
        }

        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            graf[u][v] -= path_flow;
            graf[v][u] += path_flow;
        }

        max_flow += path_flow;
    }
    return max_flow;
}




int main(){
    int n, m;
    cin >> n >> m;

    vector <vector <int>> graf (n, vector<int> (n, 0));
    int st, fn, val;
    for (int i = 0; i < m; i++){
        cin >> st >> fn >> val;
        graf[st][fn] = val;
    }

    cout << ford_fulkerson_algorithm(0, 5, graf) << endl;
}


/**
Примеры входных данных (графы):

6 8
0 1 11
0 2 12
1 3 12
2 1 1
2 4 11
3 5 19
4 3 7
4 5 4


 */
