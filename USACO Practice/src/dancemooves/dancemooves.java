/*
ID: andwerp1
LANG: JAVA
TASK: dancemooves
*/

//package dancemooves;

import java.io.*;
import java.util.*;

public class dancemooves {
	public static void main (String [] args) throws IOException {
		
	//in this problem, cows will occupy different positions based on their starting positions through swapping moves. 
	//since two cows cannot be in one position, all the cows are going to be part of a loop from cycle to cycle. We can check for this using a directed graph, and all the cows in one loop
	//will visit the same positions as every other cow in the same loop. No cow will be in two loops at once, and all cows will be in a loop.
		
	//first we need to simulate the dance moves to find the end locations of each cow after one cycle. 
	//once we have to end locations, we know which start position goes to which end position, and then we can find the cycles from there. Since each start position goes to one end position
	//there won't be two cows in one position.
		
	//IMPORTANT: remember to output all of your output in one string, repeated calls of System.out.print is very slow
    
	BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    int k = Integer.parseInt(st.nextToken());
    
    ArrayList<HashSet<Integer>> cowLocations = new ArrayList<HashSet<Integer>>();
    int[] connections = new int[n];
    boolean[] visited = new boolean[n];
    ArrayList<ArrayList<Integer>> groups = new ArrayList<ArrayList<Integer>>();
    ArrayList<HashSet<Integer>> groupLocations = new ArrayList<HashSet<Integer>>();
    
    for(int i = 0; i < n; i++) {
    	
    	connections[i] = i;
    	cowLocations.add(new HashSet<Integer>());
    	
    	cowLocations.get(i).add(i);
    	
    }
    
    for(int i = 0; i < k; i++) {
    	
    	st = new StringTokenizer(fin.readLine());
    	
    	int a = Integer.parseInt(st.nextToken()) - 1;
    	int b = Integer.parseInt(st.nextToken()) - 1;
    	
    	cowLocations.get(connections[a]).add(b);
    	cowLocations.get(connections[b]).add(a);
    	
    	int temp = connections[a];
    	connections[a] = connections[b];
    	connections[b] = temp;
    	
    }
    
    int[] ans = new int[n];
    
    for(int i = 0; i < n; i++) {
    	
    	//System.out.println("search started");
    	
    	if(!visited[i]) {
    		
    		Stack<Integer> toProcess = new Stack<Integer>();
    		toProcess.add(i);
    		
    		ArrayList<Integer> curGroup = new ArrayList<Integer>();
    		curGroup.add(i);
    		
    		visited[i] = true;
    		
    		HashSet<Integer> locations = new HashSet<Integer>();
    		
    		while(toProcess.size() != 0) {
    			
    			int cur = toProcess.pop();
    			locations.addAll(cowLocations.get(cur));
    			
    			if(!visited[connections[cur]]) {
    				
    				toProcess.add(connections[cur]);
    				curGroup.add(connections[cur]);
    				visited[connections[cur]] = true;
    				
    			}
    			
    		}
    		
    		groups.add(curGroup);
    		
    		for(int j = 0; j < curGroup.size(); j++) {
    			
    			//System.out.println(curGroup.get(j));
    			
    			ans[curGroup.get(j)] = locations.size();
    			
    		}
    		
    	}
    
    }
    
    StringBuilder out = new StringBuilder();
    
    for(int i : ans) {
    	out.append(i).append("\n");
    }
    
    System.out.print(out);
    
    fin.close();
    
	}
}