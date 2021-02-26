/*
ID: andwerp2
LANG: JAVA
TASK: pairup
*/

//package pairup;

import java.io.*;
import java.util.*;

class pairup {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new FileReader("pairup.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("pairup.out")));
    
    
    int n = Integer.parseInt(fin.readLine());
    
    int[][] cows = new int[n][2];
    
    for(int i = 0; i < n; i++) {
    	
    	StringTokenizer st = new StringTokenizer(fin.readLine());
    	
    	cows[i][0] = Integer.parseInt(st.nextToken());
    	cows[i][1] = Integer.parseInt(st.nextToken());
    	
    }
    
    Arrays.sort(cows, (a, b) -> a[1] - b[1]);
    
    int max = 0;
    
    int low = 0;
    int high = cows.length - 1;
    
    while(low != high) {
    	
    	if(cows[low][1] + cows[high][1] > max) {
    		max = cows[low][1] + cows[high][1];
    	}
    	
    	if(cows[low][0] > cows[high][0]) {
    		
    		cows[low][0] -= cows[high][0];
    		high--;
    		
    	}
    	
    	else if(cows[low][0] < cows[high][0]) {
    		
    		cows[high][0] -= cows[low][0];
    		low++;
    		
    	}
    	
    	else if(cows[low][0] == cows[high][0]) {
    		
    		low++;
    		high--;
    		
    	}
    	
    }
    
    if(cows[low][1] + cows[high][1] > max) {
    	max = cows[low][1] + cows[high][1];
    }
    
    fout.println(max);
    
    fin.close();
    fout.close();
    
	}
}