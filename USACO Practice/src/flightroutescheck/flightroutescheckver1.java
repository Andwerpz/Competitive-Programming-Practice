
package flightroutescheck;

import java.io.*;
import java.util.*;

public class flightroutescheckver1 {
	public static void main (String [] args) throws IOException {
		
	//since all the connections in the graph are one directional, we need to check for the number of strongly connected components
	//a strongly connected component is a part of a directional graph where you can visit each node from every other node.
	//if there is more than one strongly connected component in the graph, then you can't reach all the nodes from every other node and you return "NO"
	//else, it is all one component, and return "YES"
    
    BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    int m = Integer.parseInt(st.nextToken());
    ArrayList<ArrayList<Integer>> connections = new ArrayList<ArrayList<Integer>>();
    
    for(int i = 0; i < n; i++) {
    	connections.add(new ArrayList<Integer>());
    }
    
    for(int i = 0; i < m; i++) {
    	st = new StringTokenizer(fin.readLine());
    	int a = Integer.parseInt(st.nextToken());
    	int b = Integer.parseInt(st.nextToken());
    }
    
    StringBuilder fout = new StringBuilder();
    
    System.out.print(fout);
    fin.close();
    
	}
}