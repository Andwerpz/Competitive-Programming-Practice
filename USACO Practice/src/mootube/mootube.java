/*
ID: andwerp1
LANG: JAVA
TASK: mootube
*/

//	package mootube;

import java.io.*;
import java.util.*;

public class mootube {
	
	static StreamTokenizer fin;
	static int nextInt() throws IOException{
		fin.nextToken();
		return (int)fin.nval;
	}
	
	public static void main (String [] args) throws IOException {
    
    fin = new StreamTokenizer(new BufferedReader(new FileReader("mootube.in")));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("mootube.out")));
    //StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = nextInt();
    int q = nextInt();
    
    ArrayList<Node> nodes = new ArrayList<Node>();
    
    for(int i = 0; i < n; i++) {
    	nodes.add(new Node());
    }
    
    for(int i = 0; i < n - 1; i++) {
    	//st = new StringTokenizer(fin.readLine());
    	int a = nextInt() - 1;
    	int b = nextInt() - 1;
    	int str = nextInt();
    	
    	nodes.get(a).addEdge(new Edge(str, b));
    	nodes.get(b).addEdge(new Edge(str, a));
    }
    
    for(int i = 0; i < q; i++) {
    	
    	//st = new StringTokenizer(fin.readLine());
    	
    	int k = nextInt();
    	int c = nextInt() - 1;
    	
    	Stack<Integer> toProcess = new Stack<Integer>();
    	toProcess.add(c);
    	
    	boolean[] v = new boolean[n];
    	v[c] = true;
    	int count = 0;
    	
    	while(toProcess.size() != 0) {
    		
    		int cur = toProcess.pop();
    		
    		ArrayList<Edge> con = nodes.get(cur).edges;
    		
    		for(int j = 0; j < con.size(); j++) {
    			if(!v[con.get(j).destination] && con.get(j).str >= k) {
    				toProcess.add(con.get(j).destination);
    				v[con.get(j).destination] = true;
    				count ++;
    			}
    		}
    		
    	}
    	
    	fout.println(count);
    	
    }
    
    //fin.close();
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