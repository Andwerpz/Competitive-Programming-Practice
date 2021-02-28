/*
ID: andwerp2
LANG: JAVA
TASK: wormsort
*/

//package wormsort;

import java.io.*;
import java.util.*;

class wormsort {
	
	static boolean isCompleteGraph(ArrayList<Integer> misplacedCows, int[][] wormholes, int pointer) {
		
		//TODO make stack and do bfs; make a stack and put the first element in, iterating through elements.
		
//		int[][] filteredWormholes = new int[wormholes.length - (wormholes.length - pointer)][3];
//		
//		for(int i = pointer; i < wormholes.length; i++) {
//			
//			filteredWormholes[i - pointer][0] = wormholes[i][0];
//			filteredWormholes[i - pointer][1] = wormholes[i][1];
//			filteredWormholes[i - pointer][2] = wormholes[i][2];
//			
//		}
		
		//Graph g = new Graph(filteredWormholes);
		
		ArrayList<Integer> inGraph = new ArrayList<Integer>();
	    HashSet<Integer> visited = new HashSet<Integer>();
	    
	    boolean noConnection = false;
	    
	    int[] firstConnection = wormholes[pointer];
	    
	    inGraph.add(firstConnection[0]);
	    inGraph.add(firstConnection[1]);
	    
	    visited.add(firstConnection[0]);
	    visited.add(firstConnection[1]);
	    
	    while(!noConnection) {
	    	
	    	noConnection = true;
	    	
	    	
	    	
	    	for(int i = 0; i < inGraph.size(); i++) {
	    		
	    		////System.out.println(i);
	    		
	    		for(int j = pointer; j < wormholes.length; j++) {
	    			
	    			if(wormholes[j][0] == inGraph.get(i) && !visited.contains(wormholes[j][1])) {
	    				
	    				inGraph.add(wormholes[j][1]);
	    				visited.add(wormholes[j][1]);
	    				noConnection = false;
	    				
	    			}
	    			
	    			else if(wormholes[j][1] == inGraph.get(i) && !visited.contains(wormholes[j][0])) {
	    				
	    				inGraph.add(wormholes[j][0]);
	    				visited.add(wormholes[j][0]);
	    				noConnection = false;
	    				
	    			}
	    			
	    		}
	    		
	    	}	
	    	
	    }
	    
	    boolean isCompleteGraph = true;
	    
	    for(int i : inGraph) {
	    	//System.out.println(i + " in graph");
	    }
	    
	    for(int i = 0; i < misplacedCows.size(); i++) {
	    	if(!visited.contains(misplacedCows.get(i))) {
	    		isCompleteGraph = false;
	    		break;
	    	}
	    }
	    
	    ////System.out.println(isCompleteGraph);
	    
	    return isCompleteGraph;
		
	}
	
	
	
	
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new FileReader("wormsort.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("wormsort.out")));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    int m = Integer.parseInt(st.nextToken());
    
    int[] cows = new int[n];
    int[][] wormholes = new int[m][3];
    
    int numMisplacedCows = 0;
    
    ArrayList<Integer> misplacedCows = new ArrayList<Integer>();
    
    st = new StringTokenizer(fin.readLine());
    
    for(int i = 0; i < n; i++) {
    	
    	cows[i] = Integer.parseInt(st.nextToken()) - 1;
    	
    	if(cows[i] != i) {
    		
    		numMisplacedCows ++;
    		misplacedCows.add(i);
    		
    	}
    	
    }
    
    if(misplacedCows.size() == 0) {
    	
    	fout.println(-1);
    }
    
    else {
    	
	    for(int i : misplacedCows) {
	    	
	    	//System.out.println(i + " is misplaced");
	    }
	    
	    for(int i = 0; i < m; i++) {
	    	
	    	st = new StringTokenizer(fin.readLine());
	    	
	    	wormholes[i] = new int[] {Integer.parseInt(st.nextToken()) - 1, Integer.parseInt(st.nextToken()) - 1, Integer.parseInt(st.nextToken()),};
	    	
	    }
	    
	    Arrays.sort(wormholes, (a, b) -> a[2] - b[2]);
	    
	    for(int[] i : wormholes) {
	    	
	    	//System.out.println(i[0] + " " + i[1] + " " + i[2]);
	    	
	    }
	    
	    boolean isMaxSize = false;
	    
	    int high = m - 1;
	    int low = 0;
	    
	    int pointer = (high + low) / 2;
	    
	    int maxSize = 0;
	    
	    Graph g = new Graph(wormholes, n, misplacedCows);
	    
	    while(!isMaxSize) {
	    	
		    int threshold = wormholes[pointer][2];
		    
		    int nextThreshold = wormholes[pointer + 1][2];
		    
		    if(g.isCompleteGraph(threshold)) {
		    	
		    	if(!g.isCompleteGraph(nextThreshold)) {
		    		
		    		maxSize = wormholes[pointer][2];
		    		isMaxSize = true;
		    		break;
		    		
		    	}
		    	
		    	else {
		    		
		    		low = pointer;
		    		pointer = (high + low) / 2;
		    		
		    	}
		    	
		    }
		    
		    else {
		    	
		    	high = pointer;
		    	pointer = (high + low) / 2;
		    	
		    }
	    	
	    }
	    
	    fout.println(maxSize);
    }
    
    
    
    fin.close();
    fout.close();
    
	}
}

class Graph {
	
	public ArrayList<ArrayList<int[]>> connections;
	public ArrayList<Integer> misplacedCows;
	
	public Graph(int[][] wormholes, int numNodes, ArrayList<Integer> misplacedCows) {
		
		//System.out.println(numNodes + " num Nodes");
		
		this.connections = new ArrayList<ArrayList<int[]>>();
		
		this.misplacedCows = misplacedCows;
		
		for(int i = 0; i < numNodes; i++) {
			this.connections.add(new ArrayList<int[]>());
		}
		
		for(int i = 0; i < wormholes.length; i++) {
			
			this.connections.get(wormholes[i][0]).add(new int[] {wormholes[i][1], wormholes[i][2]});
			this.connections.get(wormholes[i][1]).add(new int[] {wormholes[i][0], wormholes[i][2]});
			
		}
		
	}
	
	public boolean isCompleteGraph(int threshold) {
		
		//System.out.println("Start new check with threshold: " + threshold);
		
		HashSet<Integer> visited = new HashSet<Integer>();
		
		ArrayList<Integer> toProcess = new ArrayList<Integer>();
		
		toProcess.add(misplacedCows.get(0));
		visited.add(misplacedCows.get(0));
		
		while(toProcess.size() != 0) {
			
			ArrayList<Integer> nextToProcess = new ArrayList<Integer>();
			
			for(int i = 0; i < toProcess.size(); i++) {
				
				ArrayList<int[]> curNode = this.connections.get(toProcess.get(i));
				
				for(int j = 0; j < curNode.size(); j++) {
					
					int nextNode = curNode.get(j)[0];
					
					if(!visited.contains(nextNode) && curNode.get(j)[1] >= threshold) {
						nextToProcess.add(nextNode);
						visited.add(nextNode);
					}
					
				}
				
			}
			
			toProcess = nextToProcess;
			
		}
		
		for(int i = 0; i < misplacedCows.size(); i++) {
			
			if(!visited.contains(misplacedCows.get(i))){
				//System.out.println(false);
				return false;
			}
			
		}
		
		//System.out.println(true);
		
		return true;
		
	}
	
}