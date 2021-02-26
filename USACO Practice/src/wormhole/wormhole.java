/*
ID: andwerp1
LANG: JAVA
TASK: wormhole
*/

//package wormhole;

import java.io.*;
import java.util.*;

class wormhole {
	
	// TODO need to fix the wormhole combination generation
	
	static int[][] wormholes;
	static int loopCounter = 0;
	static ArrayList<int[]> checkedCombinations = new ArrayList<int[]>();
	
	public static void permuteWrapper(int[] combination, int k) {
		
		int[] values = new int[combination.length];
		for(int i = 0; i < combination.length; i++) {
			values[i] = combination[i];
		}
		
		permute(values, k);
		
	}
	
	public static void permute(int[] combination, int k) {
		
		int[] originalCombination = new int[combination.length];
		
		for(int i = 0; i < combination.length; i++) {
			originalCombination[i] = combination[i];
		}
		
		boolean counting = false;
		int counter = 0;
		int gap = 0;
		
		for(int l = 0; l < combination.length - (k * 2) - 1; l++) {
			
			gap = l + 1;
			
			for(int i = 0; i < combination.length; i++) {
				combination[i] = originalCombination[i];
			}
			counting = false;
			counter = 0;
			
			for(int i = 0; i < combination.length; i++) {
				
				if(counting && combination[i] == -1) {
					counter++;
				}
				
				if(counter == gap || i == combination.length - 1) {
					
					if(counter == gap) {
						combination[i] = k;
						permuteWrapper(combination, k + 1);
						break;
					}
					
				}
				
				if(combination[i] == -1 && !counting) {
					combination[i] = k;
					counting = true;
				}
				
			}
		}
		
		if(k == combination.length / 2) {
			for(int i : combination) {
				//System.out.print(i + " ");
			}
			//System.out.println();
			if(isSystemInfinite(combination)) {
				loopCounter++;
			}
		}
		
	}
	
	public static boolean isSystemInfinite(int[] connections) {
		
		for(int i = 0; i < wormholes.length; i++) {
			
			int[] cow = new int[2];
			
			cow[0] = wormholes[i][0] - 1;
			cow[1] = wormholes[i][1];
			
			//System.out.println("new cow -------- " + cow[0] + " " + cow[1]);
			
			if(isInfiniteLoop(connections, cow)) {
				return true;
			}
			
		}
		
		return false;
		
	}
	
	public static boolean isInfiniteLoop(int[] connections, int[] cow) {
		
		boolean wormholesAhead = true;
		int[] visitedWormholes = new int[wormholes.length];
		
		while(wormholesAhead) {
			
			wormholesAhead = false;
			
			int wormholeIndex = -1;
			int minDistance = -1;
			
			for(int i = 0; i < wormholes.length; i++) {
				 if(wormholes[i][0] - cow[0] >= 1 && 
						 wormholes[i][1] == cow[1] && 
						 (wormholes[i][0] - cow[0] < minDistance || minDistance == -1)) {
					 
//					 if(visitedWormholes[i] == 1) {
//						 return true;
//					 }
//					 visitedWormholes[i] = 1;
						
					 
					 wormholesAhead = true;
					 wormholeIndex = i;
					 minDistance = wormholes[i][0] - cow[0];
					 ////System.out.println("next wormhole: " + wormholeIndex);
					 
					 
					 for(int j = 0; j < visitedWormholes.length; j++) {
						 ////System.out.print(visitedWormholes[j] + " ");
					 }
					 
					 ////System.out.println();
				 }
			}
			
			if(wormholeIndex != -1) {
				if(visitedWormholes[wormholeIndex] == 1) {
				return true;
			}
			visitedWormholes[wormholeIndex] = 1;
			}
			
			if(wormholeIndex == -1) {
				return false;
			}
			
			
			//System.out.println("next wormhole: " + wormholeIndex);
			
			if(wormholesAhead) {
				
				////System.out.println("wormhole check " + wormholeIndex);
				
				int nextWormholeIndex = -1;
				int nextWormholeConnection = connections[wormholeIndex];
				
				for(int i = 0; i < connections.length; i++) {
					if(connections[i] == nextWormholeConnection && i != wormholeIndex) {
						nextWormholeIndex = i;
					}
				}
				
				cow[0] = wormholes[nextWormholeIndex][0];
				cow[1] = wormholes[nextWormholeIndex][1];
				
			}
			
			
			
		}
		
		return false;
		
	}
	
	public static void main (String [] args) throws IOException {
    
	    BufferedReader fin = new BufferedReader(new FileReader("wormhole.in"));
	    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("wormhole.out")));
	    
	    int n = Integer.parseInt(fin.readLine());
	    wormholes = new int[n][2];
	    
	    for(int i = 0; i < n; i++) {
	    	StringTokenizer st = new StringTokenizer(fin.readLine());
	    	wormholes[i][0] = Integer.parseInt(st.nextToken());
	    	wormholes[i][1] = Integer.parseInt(st.nextToken());
	    }
	    
	    int[] connections = new int[n];
	    
	    for(int i = 0; i < connections.length; i++) {
	    	connections[i] = -1;
	    }
	    
	    for(int i = 0; i < 100; i++) {
	    	for(int j = 0; j < 100; j++) {
	    		
	    		boolean printed = false;
	    		
	    		for(int k = 0; k < wormholes.length; k++) {
	    			if(i == wormholes[k][1] && j == wormholes[k][0]) {
	    				//System.out.print(k + " ");
	    				printed = true;
	    			}
	    		}
	    		
	    		if(!printed) {
	    			//System.out.print(". ");
	    		}
	    		
	    	}
	    	
	    	//System.out.println();
	    }
	    
//	    for(int i = 1; i < connections.length; i++) {
//	    	//System.out.println("base 1");
//	    	permuteWrapper(connections, i, 0);
//	    }
	    
	    permuteWrapper(connections, 0);
	    
	    //System.out.println(loopCounter);
	    
	    fout.println(loopCounter);
	    
	    int[] temp1 = {1, 2, 3};
	    int[] temp2 = {1, 2, 3};
	    
	    if(Arrays.equals(temp1, temp2)) {
	    	//System.out.println("equal");
	    }
	    
	    fin.close();
	    fout.close();
    
	}
}