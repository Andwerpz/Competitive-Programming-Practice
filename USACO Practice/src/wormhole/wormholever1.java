/*
ID: andwerp1
LANG: JAVA
TASK: wormhole
*/

package wormhole;

import java.io.*;
import java.util.*;

class wormholever1 {
	
	// TODO need to fix the wormhole combination generation
	
	static int[][] wormholes;
	static int loopCounter = 0;
	static ArrayList<int[]> checkedCombinations = new ArrayList<int[]>();
	
	public static void permute(int[] scramble, int k) {
		if(k == 1) {
			
			int[] temp = new int[scramble.length];
			
			for(int i = 0; i < temp.length; i++) {
				temp[i] = -1;
			}
			
			for(int i = 0; i < scramble.length; i++) {
				if(temp[i] == -1) {
					int connectionId = scramble[i];
					for(int j = 0; j < scramble.length; j++) {
						if(scramble[j] == connectionId) {
							temp[i] = j;
							temp[j] = i;
							break;
						}
					}
				}
			}
			
//			for(int i : temp) {
//				System.out.print(i + " ");
//			}
//			System.out.println();
			
			boolean alreadyChecked = false;
			
			for(int i = checkedCombinations.size() - 1; i >= 0; i--) {
				if(Arrays.equals(checkedCombinations.get(i), temp)) {
					alreadyChecked = true;
					break;
				}
			}
			
//			if(checkedCombinations.contains(temp)) {
//				alreadyChecked = true;
//				System.out.println("heyheyhyeheyehe");
//			}
			
			if(!alreadyChecked) {
				for(int i : scramble) {
					System.out.print(i + " ");
				}
				System.out.println();
//				int[] temp3 = new int[scramble.length];
//				
//				for(int i = 0; i < scramble.length; i++) {
//					temp3[i] = scramble[i];
//				}
				
				checkedCombinations.add(temp);
				
				if(isSystemInfinite(scramble)) {
					System.out.println("infiniteLoop");
					loopCounter++;
				}
			}
			
			
			
		}
		
		else {
			permute(scramble, k - 1);
			for(int i = 0; i < k - 1; i++) {
				if(k % 2 == 0) {
					int temp = scramble[i];
					scramble[i] = scramble[k - 1];						//swapping elements i and k - 1
					scramble[k - 1] = temp;
				}
				else {
					int temp = scramble[0];
					scramble[0] = scramble[k - 1];						//swapping elements 0 and k - 1
					scramble[k - 1] = temp;
				}
				permute(scramble, k - 1);
			}
		}
	}
	
	public static boolean isSystemInfinite(int[] connections) {
		
		for(int i = 0; i < wormholes.length; i++) {
			
			int[] cow = new int[2];
			
			cow[0] = wormholes[i][0] - 1;
			cow[1] = wormholes[i][1];
			
			System.out.println("new cow -------- " + cow[0] + " " + cow[1]);
			
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
					 //System.out.println("next wormhole: " + wormholeIndex);
					 
					 
					 for(int j = 0; j < visitedWormholes.length; j++) {
						 //System.out.print(visitedWormholes[j] + " ");
					 }
					 
					 //System.out.println();
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
			
			
			System.out.println("next wormhole: " + wormholeIndex);
			
			if(wormholesAhead) {
				
				//System.out.println("wormhole check " + wormholeIndex);
				
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
	    
	    for(int i = 0; i < n; i += 2) {
	    	connections[i] = i / 2;
	    	connections[i + 1] = i / 2;
	    }
	    
	    for(int i = 0; i < 100; i++) {
	    	for(int j = 0; j < 100; j++) {
	    		
	    		boolean printed = false;
	    		
	    		for(int k = 0; k < wormholes.length; k++) {
	    			if(i == wormholes[k][1] && j == wormholes[k][0]) {
	    				System.out.print(k + " ");
	    				printed = true;
	    			}
	    		}
	    		
	    		if(!printed) {
	    			System.out.print(". ");
	    		}
	    		
	    	}
	    	
	    	System.out.println();
	    }
	    
	    permute(connections, n);
	    
	    System.out.println(loopCounter);
	    
	    fout.println(loopCounter);
	    
	    int[] temp1 = {1, 2, 3};
	    int[] temp2 = {1, 2, 3};
	    
	    if(Arrays.equals(temp1, temp2)) {
	    	System.out.println("equal");
	    }
	    
	    fin.close();
	    fout.close();
    
	}
}