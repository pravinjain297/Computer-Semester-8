/*
Title:-Design and implement Parallel Breadth First Search and Depth First Search based on existing algorithms using OpenMP. Use a Tree or an undirected graph for BFS and DFS .
Name:-Pravin Jain
Roll NO:-72
Subject:-LP-V
*/

#include<iostream>
#include<omp.h>
#include<bits/stdc++.h>

using namespace std;


class Graph{
    public:
        int vertices = 6;
        int edges = 5;
        vector<vector<int>> graph = {{1},{0,2,3},{1,4,5},{1,4},{2,3},{2}};
        vector<bool> visited;

       
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
    Graph g;
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
hduser@ubuntu-OptiPlex-390:~$ g++ -o bfs -fopenmp bfs.cpp
hduser@ubuntu-OptiPlex-390:~$ ./bfs
Adjacency List:
0 -> 1 
1 -> 0 2 3 
2 -> 1 4 5 
3 -> 1 4 
4 -> 2 3 
5 -> 2 
Parallel Depth First Search: 
0 1 3 4 2 5 

Parallel Breadth First Search: 
0 1 3 2 4 5 
hduser@ubuntu-OptiPlex-390:~$ 
*/
