/*
ID: andwerp1
LANG: JAVA
TASK: revegetate
*/

//package revegetate;

import java.io.*;
import java.util.*;

class revegetate {
	public static void main (String [] args) throws IOException {
		
	//the problem wants us to print out how many different ways fj can plant his seeds in the pasture
	//since the pasture can be represented with a bipartite tree, if it is a bipartite graph, then he will be able to plant only 2 different ways
	//but if it is not a bipartite graph, then he can't plant at all, since there is no way to satisfy all of his cows.
		
	//there might also be separated graphs, where different parts of the pasture aren't connected through one cow. 
	//for each separate part of the pasture, we just multiply the amount of different configurations by 2; 1 connected graph -> 2 configurations, 2 -> 4, 3 -> 8 and so on.
    
    BufferedReader fin = new BufferedReader(new FileReader("revegetate.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("revegetate.out")));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    int m = Integer.parseInt(st.nextToken());
    
    int[] pasture = new int[n];
    ArrayList<ArrayList<int[]>> connections = new ArrayList<ArrayList<int[]>>();
    ArrayList<ArrayList<Integer>> groups = new ArrayList<ArrayList<Integer>>();
    
    for(int i = 0; i < n; i++) {
    	
    	connections.add(new ArrayList<int[]>());
    	
    }
    
    for(int i = 0; i < m; i++) {
    	
    	st = new StringTokenizer(fin.readLine());
    	
    	String type = st.nextToken();	//0 for different grass, 1 for same grass
    	
    	int a = Integer.parseInt(st.nextToken()) - 1;
    	int b = Integer.parseInt(st.nextToken()) - 1;
    	
    	if(type.equals("D")) {
    		
    		connections.get(a).add(new int[] {b, 0});
    		connections.get(b).add(new int[] {a, 0});
    		
    	}
    	
    	else {
    		
    		connections.get(a).add(new int[] {b, 1});
    		connections.get(b).add(new int[] {a, 1});
    		
    	}
    	
    }
    
    //putting the cow preferences into groups so we can check for bipartiteness.
    //if all groups are valid, then the answer is just 2 to the power of the number of groups
    //if one or more groups are invalid, then the answer is 0
    
    HashSet<Integer> partOfGroup = new HashSet<Integer>();
    
    for(int i = 0; i < connections.size(); i++) {
    	
    	if(!partOfGroup.contains(i)) {
    		
    		Stack<Integer> toProcess = new Stack<Integer>();
    		toProcess.add(i);
    		partOfGroup.add(i);
    		
    		ArrayList<Integer> curGroup = new ArrayList<Integer>();
    		curGroup.add(i);
    		
    		while(toProcess.size() != 0) {
    			
    			int cur = toProcess.pop();
    			
    			for(int j = 0; j < connections.get(cur).size(); j++) {
    				
    				if(!partOfGroup.contains(connections.get(cur).get(j)[0])) {
    					
    					toProcess.add(connections.get(cur).get(j)[0]);
    					partOfGroup.add(connections.get(cur).get(j)[0]);
    					curGroup.add(connections.get(cur).get(j)[0]);
    					
    				}
    				
    			}
    			
    		}
    		
    		groups.add(curGroup);
    		
    	}
    	
    }
    
    for(ArrayList<Integer> i : groups) {
    	
    	for(int j : i) {
    		//System.out.print(j + " ");
    	}
    	//System.out.println();
    }
    
    boolean isBipartite = true;
    
    for(int i = 0; i < groups.size(); i++) {
    	
    	Stack<Integer> toProcess = new Stack<Integer>();
    	toProcess.add(groups.get(i).get(0));
    	
    	HashSet<Integer> visited = new HashSet<Integer>();
    	visited.add(groups.get(i).get(0));
    	
    	pasture[groups.get(i).get(0)] = 1;
    	
    	while(toProcess.size() != 0 && isBipartite) {
    		
    		int cur = toProcess.pop();
    		
    		int curNodeColor = pasture[cur];
    		
    		for(int j = 0; j < connections.get(cur).size(); j++) {
    			
    			if(!visited.contains(connections.get(cur).get(j)[0])) {
    				
    				toProcess.add(connections.get(cur).get(j)[0]);
    				visited.add(connections.get(cur).get(j)[0]);
    				
    				int connectionType = pasture[connections.get(cur).get(j)[1]];
    				
    				if(connectionType == 0) {
    					
    					if(curNodeColor == 1) {
    						pasture[connections.get(cur).get(j)[0]] = 2;
    					}
    					
    					else {
    						pasture[connections.get(cur).get(j)[0]] = 1;
    					}
    					
    				}
    				
    				else {
    					
    					if(curNodeColor == 1) {
    						pasture[connections.get(cur).get(j)[0]] = 1;
    					}
    					
    					else {
    						pasture[connections.get(cur).get(j)[0]] = 2;
    					}
    					
    				}
    				
    			}
    			
    			else if(pasture[connections.get(cur).get(j)[0]] != 0) {
    				
    				//System.out.println("repeat detected comparing: " + cur + " " + connections.get(cur).get(j)[0]);
    					
					int nextNodeColor = pasture[connections.get(cur).get(j)[0]];
					int connectionType = pasture[connections.get(cur).get(j)[1]];
					
					if(nextNodeColor == curNodeColor && connectionType == 0) {
						
						//System.out.println("is not bipartite, case same, supposed to be different");
						
						isBipartite = false;
						break;
						
					}
					
					else if(nextNodeColor != curNodeColor && connectionType == 1) {
						
						//System.out.println("is not bipartite, case different, supposed to be same");
						
						isBipartite = false;
						break;
						
					}
					
				}
    		
    		}
    		
    	}
    	
    	if(!isBipartite) {
    		
    		break;
    		
    	}
    	
    }
    
    if(!isBipartite) {
    	fout.println("0");
    }
    
    else {
    	
    	String output = "";
    	
    	for(int i = 0; i < groups.size(); i++) {
    		
    		output += "0";
    		
    	}
    	
    	fout.println("1" + output);
    	
    }
    
    fin.close();
    fout.close();
    
	}
}