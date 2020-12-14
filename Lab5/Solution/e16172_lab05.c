//E/16/172
#include<stdio.h> 
  
// define no of nodes in the graph
#define V 7
  
void print_mat(int reach[][V]) 
{ 
    printf ("\nTransitive closure of the given graph\n\n"); 
    for (int i = 0; i < V; i++) 
    { 
        for (int j = 0; j < V; j++) 
            printf ("%d ", reach[i][j]); 
        printf("\n"); 
    } 
    printf("\n");
} 

  
void transitiveClosure(int graph[][V]) 
{ 
    int reach[V][V], i, j, k; 
  
    for (i = 0; i < V; i++) 
        for (j = 0; j < V; j++) 
            reach[i][j] = graph[i][j]; 
  
    for (k = 0; k < V; k++)    // checking the position of all to reach 
    { 
        for (i = 0; i < V; i++)    // traval the rows 
        { 
            for (j = 0; j < V; j++)  // traval the columns
            { 
                if(i==j){
                   reach[i][j] = 1;  // the vertex its self can reach condintion 

                }else{
                    // checking the allredy is there any posible way or k th poisitional way to reach condition  
                   reach[i][j] = reach[i][j] || (reach[i][k] && reach[k][j]);    

                }
            } 
        } 
    } 
  
    print_mat(reach); // printing final reach array 
} 
  
int main() 
{ 
    // Insert adjacency matrix of the graph
    int graph[V][V] = { {0, 1, 1, 0, 0, 0, 0}, 
                        {0, 0, 0, 0, 1, 0, 0}, 
                        {0, 0, 0, 0, 0, 1, 0}, 
                        {0, 1, 0, 0, 1, 0, 1},
                        {0, 0, 0, 0, 0, 0, 1},
                        {0, 0, 0, 1, 0, 0, 0},
                        {0, 1, 0, 0, 0, 0, 0}
                      }; 
    /*int graph[V][V]={ {0,1,1,0},
                        {0,0,0,0},
                        {0,0,0,1},
                        {0,1,0,0}};*/
  
    // Print the solution 
    transitiveClosure(graph); 
    return 0; 
} 
