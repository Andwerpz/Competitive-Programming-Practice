#include <bits/stdc++.h>
using namespace std;

//select as many edges as possible in a bipartite graph such that no selected edge shares a vertex
//with any other edge

//Konig's Theorem: The amount of vertices in a minimum vertex cover of a bipartite graph is exactly the same as 
//the amount of edges in a maximum bipartite matching. 
//minimum vertex cover is selecting the minimum amount of vertices such that each edge is indicent on at least 1 
//selected vertex. 