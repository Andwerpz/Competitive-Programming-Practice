
package legacy;

import java.io.*;
import java.util.*;

public class legacyver1 {
	public static void main (String [] args) throws IOException {
		
	//using dijkstra's algorithm
    
    BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    int q = Integer.parseInt(st.nextToken());
    int s = Integer.parseInt(st.nextToken()) - 1;
    
    int[][] connections = new int[n][n];	//might need to fix edge representation: reached mem limit
    int[] dist = new int[n];
    for(int i = 0; i < n; i++) {
    	dist[i] = -1;
    }
    dist[s] = 0;
    
    
    
    for(int i = 0; i < q; i++) {
    	st = new StringTokenizer(fin.readLine());
    	int t = Integer.parseInt(st.nextToken());
    	if(t == 1) {
    		int v = Integer.parseInt(st.nextToken()) - 1;
    		int u = Integer.parseInt(st.nextToken()) - 1;
    		int w = Integer.parseInt(st.nextToken());
    		if(connections[v][u] > w || connections[v][u] == 0) {
    			connections[v][u] = w;
    		}
    	}
    	else if(t == 2) {
    		int v = Integer.parseInt(st.nextToken()) - 1;
    		int l = Integer.parseInt(st.nextToken()) - 1;
    		int r = Integer.parseInt(st.nextToken()) - 1;
    		int w = Integer.parseInt(st.nextToken());
    		for(int j = l; j <= r; j++) {
    			if(connections[v][j] > w || connections[v][j] == 0) {
    				connections[v][j] = w;
    			}
    		}
    	}
    	else {
    		int v = Integer.parseInt(st.nextToken()) - 1;
    		int l = Integer.parseInt(st.nextToken()) - 1;
    		int r = Integer.parseInt(st.nextToken()) - 1;
    		int w = Integer.parseInt(st.nextToken());
    		for(int j = l; j <= r; j++) {
    			if(connections[j][v] > w || connections[j][v] == 0) {
    				connections[j][v] = w;
    			}
    		}
    	}
    }
    
    
    
    Stack<Integer> stack = new Stack<Integer>();
    stack.add(s);
    
    boolean[] v = new boolean[n];
    v[s] = true;
    boolean done = false;
    
    while(!done) {
    	Stack<Integer> newStack = new Stack<Integer>();
	    while(stack.size() != 0) {	//dijkstra's algo bfs
	    	int cur = stack.pop();
	    	//System.out.println("now processing " + cur);
	    	int[] con = connections[cur];
	    	for(int i = 0; i < con.length; i++) {
	    		if(con[i] != 0) {
	    			if(!v[i]) {
	    				newStack.add(i);
	    				v[i] = true;
	    			}
	    			int cost = con[i] + dist[cur];
	    			//System.out.println("to planet " + i + " cost " + cost);
	    			if(cost < dist[i] || dist[i] == -1) {
	    				dist[i] = cost;
	    			}
	    		}
	    	}
	    }
	    stack = newStack;
	    if(newStack.size() == 0) {
	    	done = true;
	    }
    }
    
    
    StringBuilder fout = new StringBuilder();
    for(int i = 0; i < dist.length; i++) {
    	fout.append(dist[i] + " ");
    }
    
    System.out.print(fout);
    fin.close();
    
	}
}