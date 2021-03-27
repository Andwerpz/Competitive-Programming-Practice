/*
ID: andwerp1
LANG: JAVA
TASK: reststops
*/

//package reststops;

import java.io.*;
import java.util.*;

public class reststops {
	public static void main (String [] args) throws IOException {
		
	//we try to maximize the amount of tastiness points that bessie can get while keeping bessie not behind farmer john
	//it would be best to not rest until we get to the rest stop with the maximum tastiness units per second, this allows us to save our seconds to get the most tastiness units.
	//once fj catches up, we leave and then we consider which rest stop that is remaining has the most tastiness per second, and we go there.
	//repeat until we reach the last rest stop.
    
    BufferedReader fin = new BufferedReader(new FileReader("reststops.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("reststops.out")));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int l = Integer.parseInt(st.nextToken());
    int n = Integer.parseInt(st.nextToken());
    int fTime = Integer.parseInt(st.nextToken());
    int bTime = Integer.parseInt(st.nextToken());
    
    int[][] restStops = new int[n][2];
    
    for(int i = 0; i < n; i++) {
    	
    	st = new StringTokenizer(fin.readLine());
    	
    	int distance = Integer.parseInt(st.nextToken());
    	int amount = Integer.parseInt(st.nextToken());
    	
    	restStops[i] = new int[] {amount, distance};
    	
    }
    
    //System.out.println();
    
    Arrays.sort(restStops, (a, b) -> a[1] - b[1]);
    
    for(int[] i : restStops) {
    	
    	//System.out.println(i[0] + " " + i[1]);
    	
    } 
    
    int distTravelled = 0;
    
    int pointer = 0;
    
    long total = 0;
    
    boolean done = false;
    
    while(!done) {
    	
    	int max = 0;
    	int maxIndex = 0;
    	int dist = 0;
    	
    	for(int i = pointer; i < restStops.length; i++) {
    		
    		if(restStops[i][0] > max || (restStops[i][0] == max && i > maxIndex)) {
    			max = restStops[i][0];
    			maxIndex = i;
    		}
    		
    	}
    	
    	pointer = maxIndex + 1;
    	dist = restStops[maxIndex][1] - distTravelled;
    	
    	distTravelled = restStops[maxIndex][1];
    	
    	total += max * (long) (fTime - bTime) * (long) dist;
    	
    	//System.out.println(total + " " + distTravelled + " " + (fTime - bTime) * dist);
    	
    	
    	
    	if(pointer == restStops.length) {
    		done = true;
    	}
    	
    }
    
    fout.println(total);
    
    fin.close();
    fout.close();
    
	}
}