
package birthdayparty;

import java.io.*;
import java.util.*;

public class birthdaypartyver1 {
	public static void main (String [] args) throws IOException {
		
	//in order to solve, we need to find whether a cut edge exists within the graph; the graph is guaranteed connected (i think)
	//if one does exist, then if we lose that connection, then we split the graph into two
		
	//in order for a graph to not contain a cut edge, there needs to be a way to visit all the vertices and return to the original vertice 
	//without backtracking along an edge; travelling salesman like
	
	//we start from vertex 0, and then we do a dfs travelling along the graph. As we travel along the graph, we assign a visiting time to each node,
	//the first node will get 0, the second node visited will get 1 and so on. When we hit a dead end, we backtrack to the previous node and see if the node with the dead end has a neighbor
	//that has a visiting time less than the parent node. If yes, then the connection is not a bridge and we assign that new lower time to the child node, but if no, then that edge
	//is a bridge and we can conclude that there is a bridge in the graph. 
		
	//as soon as we hit the original node, node 0, we see if there are any new nodes. If no, and we managed to get back without detecting a bridge, we can say that there are no bridges in the graph
    
    Scanner fin = new Scanner(System.in);
    
    while(true) {
    	
    	
    	
    	StringTokenizer st = new StringTokenizer(fin.nextLine());
    	
    	int p = Integer.parseInt(st.nextToken());
    	int c = Integer.parseInt(st.nextToken());
    	
    	if(p == 0 && c == 0) {
    		
    		break;
    		
    	}
    	System.out.println("\n\nnew test");
    	ArrayList<Node> nodes = new ArrayList<Node>();
    	
    	for(int i = 0; i < p; i++) {
    		nodes.add(new Node(i));
    	}
    	
    	for(int i = 0; i < c; i++) {
    		
    		st = new StringTokenizer(fin.nextLine());
    		
    		int a = Integer.parseInt(st.nextToken());
    		int b = Integer.parseInt(st.nextToken());
    		
    		nodes.get(a).addConnection(b);
    		nodes.get(b).addConnection(a);
    		
    		System.out.println(a + " " + b);
    		
    	}
    	
    	Stack<Integer> visiting = new Stack<Integer>();
    	visiting.add(0);
    	
    	boolean doesBridgeExist = false;
    	
    	boolean done = false;
    	
    	int visitTime = 0;
    	
    	nodes.get(0).time = 0;
    	visitTime++;
    	
    	while(!done) {
    		
    		int cur = visiting.peek();
    		
    		ArrayList<Integer> con = nodes.get(cur).connections;
    		
    		boolean newNode = false;
    		
    		for(int i = 0; i < con.size(); i++) {
    			
    			if(nodes.get(con.get(i)).time == -1) {
    				
    				newNode = true;
    				visiting.add(con.get(i));
    				nodes.get(con.get(i)).time = visitTime;
    				visitTime ++;
    				
    				break;
    				
    			}
    			
    		}
    		
    		if(!newNode) {
    			
    			if(cur == 0) {
    				
    				done = true;
    				
    			}
    			
    			else {
    				
    				System.out.println("Start backtracking check");
    				
	    			Node child = nodes.get(visiting.pop());
	    			
	    			int parentTime = nodes.get(visiting.peek()).time;
	    			
	    			System.out.println("parent time: " + parentTime);
	    			
	    			for(int i = 0; i < child.connections.size(); i++) {
	    				
	    				if(child.connections.get(i) != visiting.peek()) {	//checking if the node that we are looking at is the parent node
	    					
	    					child.setTime(nodes.get(child.connections.get(i)).time);
	    					
	    				}
	    				
	    			}
	    			
	    			if(child.time > parentTime) {
	    				
	    				doesBridgeExist = true;
	    				done = true;
	    				
	    			}
    				
    			}
    			
    		}
    		
    	}
    	
    	if(doesBridgeExist) {
    		System.out.println("Yes");
    	}
    	
    	else {
    		System.out.println("No");
    	}
    	
    }
    
    fin.close();
    
	}
}

class Node {
	
	ArrayList<Integer> connections;
	public int time;
	
	public int id;
	
	public Node(int id) {
		
		connections = new ArrayList<Integer>();
		time = -1;
		this.id = id;
		
	}
	
	public void addConnection(int a) {
		
		connections.add(a);
		
	}
	
	public void setTime(int a) {
		
		if(a < time) {
			time = a;
		}
		
	}
	
}