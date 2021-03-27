
//package birthdayparty;

import java.io.*;
import java.util.*;

public class birthdayparty {
	public static void main (String [] args) throws IOException {
	
	//for this solution, we're just going to do a dfs for each edge, seeing if we remove that edge, will the graph remain connected.
		
	//working solution but kinda slow O(n^2);
    
    Scanner fin = new Scanner(System.in);
    
    while(true) {
    	
    	
    	
    	StringTokenizer st = new StringTokenizer(fin.nextLine());
    	
    	int p = Integer.parseInt(st.nextToken());
    	int c = Integer.parseInt(st.nextToken());
    	
    	if(p == 0 && c == 0) {
    		break;
    	}
    	//System.out.println("\n\n");
    	int[][] conList = new int[c][2];
    	ArrayList<ArrayList<Integer>> connections = new ArrayList<ArrayList<Integer>>();
    	
    	for(int i = 0; i < p; i++) {
    		connections.add(new ArrayList<Integer>());
    	}
    	
    	for(int i = 0; i < c; i++) {
    		
    		st = new StringTokenizer(fin.nextLine());
    		
    		conList[i][0] = Integer.parseInt(st.nextToken());
    		conList[i][1] = Integer.parseInt(st.nextToken());
    		
    		connections.get(conList[i][0]).add(conList[i][1]);
    		connections.get(conList[i][1]).add(conList[i][0]);
    		
    	}
    	
    	boolean isCompleteGraph = true;
    	
    	for(int i = 0; i < c; i++) {	//for each connection, we'll run a dfs to see whether or not the graph is connected without it
    		
    		Stack<Integer> toProcess = new Stack<Integer>();
    		toProcess.add(0);
    		
    		HashSet<Integer> visited = new HashSet<Integer>();
    		visited.add(0);
    		
    		int a = conList[i][0];
    		int b = conList[i][1];
    		
    		//System.out.println("connection " + a + " " + b + " is restricted");
    		
    		while(toProcess.size() != 0) {
    			
    			int cur = toProcess.pop();
    			
    			for(int j = 0; j < connections.get(cur).size(); j++) {
    				
    				int nextNode = connections.get(cur).get(j);
    				
    				//System.out.println("checking connection " + cur + " " + nextNode);
    				//System.out.println(visited.contains(nextNode));
    				
    				if(!visited.contains(nextNode) && !((cur == a && nextNode == b) || (cur == b && nextNode == a))) {
    					
    					//System.out.println("valid connection");
    					
    					toProcess.add(nextNode);
    					visited.add(nextNode);
    					
    				}
    				
    			}
    			
    		}
    		
    		if(visited.size() < p) {
    			
    			isCompleteGraph = false;
    			
    		}
    		
    	}
    	
    	if(isCompleteGraph) {
    		System.out.println("No");
    	}
    	
    	else {
    		System.out.println("Yes");
    	}
    	
    }
    
    fin.close();
    
	}
}