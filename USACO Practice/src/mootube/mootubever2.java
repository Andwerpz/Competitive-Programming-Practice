/*
ID: andwerp1
LANG: JAVA
TASK: mootube
*/

package mootube;

import java.io.*;
import java.util.*;

public class mootubever2 {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new FileReader("mootube.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("mootube.out")));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    int q = Integer.parseInt(st.nextToken());
    
    ArrayList<Node> nodes = new ArrayList<Node>();
    
    for(int i = 0; i < n; i++) {
    	nodes.add(new Node());
    }
    
    for(int i = 0; i < n - 1; i++) {
    	st = new StringTokenizer(fin.readLine());
    	int a = Integer.parseInt(st.nextToken()) - 1;
    	int b = Integer.parseInt(st.nextToken()) - 1;
    	int str = Integer.parseInt(st.nextToken());
    	
    	nodes.get(a).addEdge(new Edge(str, b));
    	nodes.get(b).addEdge(new Edge(str, a));
    }
    
    for(int i = 0; i < q; i++) {
    	
    	st = new StringTokenizer(fin.readLine());
    	
    	int k = Integer.parseInt(st.nextToken());
    	int c = Integer.parseInt(st.nextToken()) - 1;
    	
    	Stack<Integer> toProcess = new Stack<Integer>();
    	toProcess.add(c);
    	
    	HashSet<Integer> v = new HashSet<Integer>();
    	v.add(c);
    	
    	while(toProcess.size() != 0) {
    		
    		int cur = toProcess.pop();
    		
    		ArrayList<Edge> con = nodes.get(cur).edges;
    		
    		for(int j = 0; j < con.size(); j++) {
    			if(!v.contains(con.get(j).destination) && con.get(j).str >= k) {
    				toProcess.add(con.get(j).destination);
    				v.add(con.get(j).destination);
    			}
    		}
    		
    	}
    	
    	fout.println(v.size() - 1);
    	
    }
    
    fin.close();
    fout.close();
    
	}
}

class Node{
	
	public ArrayList<Edge> edges;
	
	public Node() {
		
		edges = new ArrayList<Edge>();
		
	}
	
	public void addEdge(Edge e) {
		this.edges.add(e);
	}
	
}

class Edge{
	
	public int str;
	public int destination;
	
	public Edge(int str, int destination) {
		this.str = str;
		this.destination = destination;
	}
	
}