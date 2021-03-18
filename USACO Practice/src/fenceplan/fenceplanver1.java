/*
ID: andwerp1
LANG: JAVA
TASK: fenceplan
*/

package fenceplan;

import java.io.*;
import java.util.*;

class fenceplanver1 {
	public static void main (String [] args) throws IOException {
		
		
	//to solve this problem, we need to first find out the members of each moo-group. 
	//once the members of each moo group is determined, then we can simply find the moo group that
	//requires the fence of the least perimeter
		
	//to find the members of each moo-group, we just use a dfs and iterate through all the cows.
	//we can have a uncategorized arraylist, and as we iterate through them, we can put them into groups. 
		
    
    BufferedReader fin = new BufferedReader(new FileReader("fenceplan.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("fenceplan.out")));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    int m = Integer.parseInt(st.nextToken());
    
    int[][] cows = new int[n][2];
    ArrayList<ArrayList<Integer>> connections = new ArrayList<ArrayList<Integer>>();
    ArrayList<ArrayList<Integer>> cowGroups = new ArrayList<ArrayList<Integer>>();
    
    boolean[] partOfGroup = new boolean[n];
    
    for(int i = 0; i < n; i++) {
    	
    	st = new StringTokenizer(fin.readLine());
    	
    	cows[i] = new int[] {Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken())};
    	connections.add(new ArrayList<Integer>());
    	
    }
    
    for(int i = 0; i < m; i++) {
    	
    	st = new StringTokenizer(fin.readLine());
    	
    	int a = Integer.parseInt(st.nextToken()) - 1;
    	int b = Integer.parseInt(st.nextToken()) - 1;
    	
    	connections.get(a).add(b);
    	connections.get(b).add(a);
    	
    }
    
    
    for(int i = 0; i < n; i++) {
    	
    	if(!partOfGroup[i]) {
    		
    		Stack<Integer> toProcess = new Stack<Integer>();
    		toProcess.add(i);
    		partOfGroup[i] = true;
    		
    		ArrayList<Integer> curGroup = new ArrayList<Integer>();
    		curGroup.add(i);
    		
    		while(toProcess.size() != 0) {
    			
    			int pointer = toProcess.pop();
    			
    			for(int j = 0; j < connections.get(pointer).size(); j++) {
    				
    				if(!partOfGroup[connections.get(pointer).get(j)]) {
	    				toProcess.add(connections.get(pointer).get(j));
	    				partOfGroup[connections.get(pointer).get(j)] = true;
	    				curGroup.add(connections.get(pointer).get(j));
	    				
	    				//System.out.println("cow " + (connections.get(pointer).get(j)) + " is now part of a group");
    				}

    			}
    			
    		}
    		
    		cowGroups.add(curGroup);
    		
    		//System.out.println("adding cow group " + cowGroups.size());
    		
    	}
    	
    }
    
    for(ArrayList<Integer> i : cowGroups) {
    	for(int j : i) {
    		System.out.print(j + " ");
    	}
    	System.out.println();
    }
    
    int minPerimeter = Integer.MAX_VALUE;
    
    for(int i = 0; i < cowGroups.size(); i++) {
    	
    	int[][] curGroup = new int[cowGroups.get(i).size()][2];
    	
    	for(int j = 0; j < curGroup.length; j++) {
    		
    		curGroup[j] = new int[] {cows[cowGroups.get(i).get(j)][0], cows[cowGroups.get(i).get(j)][1]};
    		
    	}
    	
    	Arrays.sort(curGroup, (a, b) -> a[0] - b[0]);
    	
    	int minX = curGroup[0][0];
    	int maxX = curGroup[curGroup.length - 1][0];
    	
    	Arrays.sort(curGroup, (a, b) -> a[1] - b[1]);
    	
    	int minY = curGroup[0][1];
    	int maxY = curGroup[curGroup.length - 1][1];
    	
    	int curPerimeter = (maxX - minX) * 2 + (maxY - minY) * 2;
    	
    	if(curPerimeter < minPerimeter) {
    		minPerimeter = curPerimeter;
    	}
    	
    }
    
    fout.println(minPerimeter);
    
    fin.close();
    fout.close();
    
	}
}