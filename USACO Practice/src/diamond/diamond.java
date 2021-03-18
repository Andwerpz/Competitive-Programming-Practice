/*
ID: andwerp1
LANG: JAVA
TASK: diamond
*/

//package diamond;

import java.io.*;
import java.util.*;

class diamond {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new FileReader("diamond.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("diamond.out")));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    int k = Integer.parseInt(st.nextToken());
    
    int[] diamonds = new int[n];
    int[] pfx = new int[n];
    
    for(int i = 0; i < n; i++) {
    	
    	diamonds[i] = Integer.parseInt(fin.readLine());
    	
    }
    
    Arrays.sort(diamonds);
    
    int low = 0;
    int high = 0;
    
    boolean done = false;
    
    int ansHigh = 0;
    int ansLow = 0;
    int maxInterval = 0;
    
    while(!done) {
    	
    	while(diamonds[high] - diamonds[low] <= k) {
    		
    		
    		
    		high++;
    		if(high + 1 == n) {
    			done = true;
    			break;
    		}
    	}
    	
    	high--;
    	
    	//System.out.println("testing interval " + high + " " + low);
    	
    	if(high - low + 1 > maxInterval) {
    		
    		maxInterval = high - low + 1;
    		ansHigh = high;
    		ansLow = low;
    		
    	}
    	
    	int oldLow = diamonds[low];
    	
    	while(diamonds[low] == oldLow) {
    		low++;
    	}
    	
    }
    
    //System.out.println(ansLow + " " + ansHigh + " " + maxInterval);
    
    for(int i : diamonds) {
    	//System.out.println(i + " ");
    }
    
    int ansHigh2 = 0;
    int ansLow2 = 0;
    int maxInterval2 = 0;
    
    low = 0;
    high = 0;
    
    done = false;
    
    while(!done) {
    	
    	while(diamonds[high] - diamonds[low] <= k) {
    		
    		
    		
    		high++;
    		if(high + 1 == n) {
    			done = true;
    			break;
    		}
    	}
    	
    	high--;
    	
    	
    	
    	if(high - low + 1 > maxInterval2  && ((high > ansHigh && low > ansHigh) || (high < ansLow && low < ansLow))) {
    		
    		maxInterval2 = high - low + 1;
    		ansHigh2 = high;
    		ansLow2 = low;
    		
    	}
    	
    	int oldLow = diamonds[low];
    	
    	while(diamonds[low] == oldLow) {
    		low++;
    	}
    	
    }
    
    //System.out.println(ansLow2 + " " + ansHigh2 + " " + maxInterval2);
    
    fout.println(maxInterval + maxInterval2);
    
    fin.close();
    fout.close();
    
	}
}