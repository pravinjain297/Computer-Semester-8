#include<iostream>
#include<omp.h>
#include<bits/stdc++.h>

using namespace std;


class Graph{
    public:
        int vertices;
        int edges;
        vector<vector<int>> graph;
        vector<bool> visited;

        Graph(int v, int e) {
            vertices = v;
            edges = e;
            graph.resize(vertices);
            visited.resize(vertices, false);
        }

        void addEdge(int a, int b){
            graph[a].push_back(b);
            graph[b].push_back(a);
        }

        void printGraph(){
            for(int i = 0; i < vertices; i++){
                cout << i << " -> ";
                for(auto j = graph[i].begin(); j != graph[i].end();j++){
                    cout << *j << " ";
                }
                cout << endl;
            }
        }

        void initialize_visited(){
            visited.assign(vertices,false);
        }

        void parallel_dfs(int i){
            stack<int> s;
            s.push(i);
            visited[i] = true;

            while(s.empty() != true){
                int current = s.top();
                cout << current << " ";
                #pragma omp critical
                    s.pop();
                #pragma omp parallel for
                    for(auto j = graph[current].begin(); j != graph[current].end();j++){
                        if(visited[*j] == false){
                            #pragma omp critical
                            {
                                s.push(*j);
                                visited[*j] = true;
                            }
                        }
                    }
               
            }
        }

        void parallel_bfs(int i){
            queue<int> q;
            q.push(i);
            visited[i] = true;

            while(q.empty() != true){
               
                    int current = q.front();
                    cout << current << " ";
                    #pragma omp critical
                        q.pop();
                   
                #pragma omp parallel for
                    for(auto j = graph[current].begin(); j != graph[current].end();j++){
                        if(visited[*j] == false){
                            #pragma omp critical
                                q.push(*j);
                                visited[*j] = true;
                        }
                    }
               
            }
        }
};

int main(int argc, char const *argv[])
{
    int vertices, edges;
    cout << "Enter the number of vertices: ";
    cin >> vertices;
    cout << "Enter the number of edges: ";
    cin >> edges;

    Graph g(vertices, edges);

    cout << "Enter the edges (a b) - representing an edge between vertex a and b:\n";
    for (int i = 0; i < edges; i++) {
        int a, b;
        cin >> a >> b;
        g.addEdge(a, b);
    }

    cout << "Adjacency List:\n";
    g.printGraph();
    g.initialize_visited();
   
    cout << "Parallel Depth First Search: \n";
    g.initialize_visited();
    g.parallel_dfs(0);
    cout << endl;
   
    cout << endl;
    cout << "Parallel Breadth First Search: \n";
    g.initialize_visited();
    g.parallel_bfs(0);

    return 0;
}

/*
Enter the number of vertices: 6
Enter the number of edges: 5
Enter the edges (a b) - representing an edge between vertex a and b:
0 1
1 2
1 3
2 4
2 5

Adjacency List:
0 -> 1 
1 -> 0 2 3 
2 -> 1 4 5 
3 -> 1 
4 -> 2 
5 -> 2 
Parallel Depth First Search: 
0 1 3 2 5 4 

Parallel Breadth First Search: 
0 1 2 3 4 5 


*/