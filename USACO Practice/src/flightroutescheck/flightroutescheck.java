
//package flightroutescheck;

import java.io.*;
import java.util.*;

public class flightroutescheck {
	public static void main (String [] args) throws IOException {
		
	//checking for strongly connected components using kosaraju's algorithm
	//if there is more than one strongly connected component, then we can't get from every airport to every other airport.
    
    BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    int m = Integer.parseInt(st.nextToken());
    ArrayList<ArrayList<Integer>> connections = new ArrayList<ArrayList<Integer>>();
    ArrayList<ArrayList<Integer>> reverse = new ArrayList<ArrayList<Integer>>();
    for(int i = 0; i < n; i++) {
    	connections.add(new ArrayList<Integer>());
    	reverse.add(new ArrayList<Integer>());
    }
    for(int i = 0; i < m; i++) {
    	st = new StringTokenizer(fin.readLine());
    	int a = Integer.parseInt(st.nextToken()) - 1;
    	int b = Integer.parseInt(st.nextToken()) - 1;
    	connections.get(a).add(b);
    	reverse.get(b).add(a);
    }
    
    Stack<Integer> s = new Stack<Integer>();
    s.push(0);
    
    boolean[] visited = new boolean[n];
    visited[0] = true;
    
    Stack<Integer> finished = new Stack<Integer>();
    
    while(s.size() != 0) {
    	int cur = s.peek();
    	ArrayList<Integer> con = connections.get(cur);
    	boolean visitedAllChildren = true;
    	for(int i = 0; i < con.size(); i++) {
    		if(!visited[con.get(i)]) {
    			s.push(con.get(i));
    			visited[con.get(i)] = true;
    			visitedAllChildren = false;
    			break;
    		}
    	}
    	if(visitedAllChildren) {
    		finished.add(cur);
    		s.pop();
    	}
    }
    
    s = new Stack<Integer>();
    s.push(finished.pop());
    
    visited = new boolean[n];
    visited[s.peek()] = true;
    
    while(s.size() != 0) {
    	int cur = s.peek();
    	ArrayList<Integer> con = reverse.get(cur);
    	boolean visitedAllChildren = true;
    	for(int i = 0; i < con.size(); i++) {
    		if(!visited[con.get(i)]) {
    			s.push(con.get(i));
    			visited[con.get(i)] = true;
    			visitedAllChildren = false;
    			break;
    		}
    	}
    	if(visitedAllChildren) {
    		finished.add(cur);
    		s.pop();
    	}
    }
    
    boolean ans = true;
    
    for(int i = 0; i < visited.length; i++) {
    	if(visited[i] == false) {
    		ans = false;
    		break;
    	}
    }
    
    System.out.println(ans? "YES" : "NO");
    
    if(!ans) {	// need to fix the thing that prints which flight is impossible: this iteration checks all possible flight paths, very slow
    	int a = 1;
	    int b = 0;
	    while(b == 0) {
	    	
	    	s = new Stack<Integer>();
	    	s.push(a - 1);
	    	visited = new boolean[n];
	    	visited[s.peek()] = true;
	    	while(s.size() != 0) {
	    		int cur = s.pop();
	    		ArrayList<Integer> con = connections.get(cur);
	    		for(int i = 0; i < con.size(); i++) {
	    			int next = con.get(i);
	    			if(!visited[next]) {
	    				s.push(next);
	    				visited[next] = true;
	    			}
	    		}
	    	}
	    	
	    	for(int i = 0; i < visited.length; i++) {
	    		if(!visited[i]) {
	    			b = i + 1;
	    			//System.out.println("set b to " + i);
	    			break;
	    		}
	    	}
	    	
	    	//System.out.println(a + " " + b);
	    	
	    	if(b == 0) {
	    		a++;
	    	}
    	}
	    
	    System.out.println(a + " " + b);
    	
    }
    
    
    
    StringBuilder fout = new StringBuilder();
    
    System.out.print(fout);
    fin.close();
    
	}
}