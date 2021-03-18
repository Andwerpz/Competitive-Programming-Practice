/*
ID: andwerp1
LANG: JAVA
TASK: moocast
*/

package moocastgold;

import java.io.*;
import java.util.*;

class moocastver1 {
	
	public static boolean isGraphComplete(int moneySpent, double[][][] connections) {
		
		Stack<Integer> toProcess = new Stack<Integer>();
		toProcess.add(0);
		
		HashSet<Integer> visited = new HashSet<Integer>();
		visited.add(0);
		
		double talkRadius = Math.sqrt(moneySpent);
		
		while(toProcess.size() != 0) {
			
			int curCow = toProcess.pop();
			
			for(int i = 0; i < connections[curCow].length; i++) {
				
				if(!visited.contains((int)connections[curCow][i][1]) && connections[curCow][i][0] < talkRadius) {
					
					toProcess.add((int)connections[curCow][i][1]);
					visited.add((int)connections[curCow][i][1]);
					
				}
				
				else if(connections[curCow][i][0] > talkRadius) {
					break;	//we can do this since we sorted the connections array
				}
			
			}
			
		}
		
		if(visited.size() == connections.length) {
			
			return true;
			
		}
		
		return false;
		
	}
	
	public static void main (String [] args) throws IOException {
		
	
	//what we do is test various powers of walkie talkie. Since all cows recieve the same power of walkie talkie,
	//we can do a dfs with the assigned power. 
		
	//in order to find the lowest power, we can do a binary search of walkie talkie powers, ending when the power we test is good, but the one right below it is not.
		
	//to reduce computing time, we can precompute the distances between the cows, and for each cow, we sort the connections from lowest distance to highest distance.
	//that way, when looking through connections, we can stop when we hit the first not valid connection, and not have to look through them all.
		
    
    BufferedReader fin = new BufferedReader(new FileReader("moocast.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("moocast.out")));
    
    
    int n = Integer.parseInt(fin.readLine());
    
    int[][] cows = new int[n][2];
    double[][][] connections = new double[n][n][2];
    
    double maxConnection = 0;
    
    for(int i = 0; i < cows.length; i++) {
    	
    	StringTokenizer st = new StringTokenizer(fin.readLine());
    	
    	cows[i] = new int[] {Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken())};
    	
    }
    
    for(int i = 0; i < cows.length; i++) {
    	
    	for(int j = 0; j < cows.length; j++) {
    		
    		connections[i][j] = new double[] {Math.sqrt(Math.pow(cows[i][0] - cows[j][0], 2) + Math.pow(cows[i][1] - cows[j][1], 2)), j};
    		
    		if(connections[i][j][0] > maxConnection) {
    			maxConnection = connections[i][j][0];
    		}
    		
    	}
    	
    	Arrays.sort(connections[i], (a, b) -> Double.compare(a[0], b[0]));
    	
    }
    
    for(int i = 0; i < connections.length; i++) {
    	
    	System.out.println("cow " + i);
    	
    	for(int j = 0; j < connections.length; j++) {
    		
    		System.out.println(connections[i][j][1] + " " + connections[i][j][0]);
    		
    	}
    	
    	System.out.println();
    	
    }
    
    
    int high = (int) Math.ceil(Math.pow(maxConnection, 2));
    int low = 0;
    
    int pointer = (high + low) / 2;
    
    boolean success = false;
    
    while(!success) {
    	
    	boolean doesWork = isGraphComplete(pointer, connections);
    	
    	if(doesWork) {
    		
    		if(!isGraphComplete(pointer - 1, connections)) {
    			
    			success = true;
    			
    			break;
    			
    		}
    		
    		high = pointer;
    		
    	}
    	
    	else if(!doesWork) {
    		
    		low = pointer;
    		
    	}
    	
    	pointer = (low + high) / 2;
    	
    }
    
    fout.println(pointer - 1);
    
    
    fin.close();
    fout.close();
    
	}
}