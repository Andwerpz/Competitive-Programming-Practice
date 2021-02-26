/*
ID: andwerp2
LANG: JAVA
TASK: div7
*/

package div7;

import java.io.*;
import java.util.*;

class div7ver1 {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new FileReader("div7.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("div7.out")));
    
    
    int n = Integer.parseInt(fin.readLine());
    
    int[] cows = new int[n];
    int[] prefixSum = new int[n];
    
    int[] firstOccurence = new int[7];
    int[] lastOccurence = new int[7];
    
    Arrays.fill(firstOccurence, -1);
    Arrays.fill(lastOccurence, -1);
    
    for(int i = 0; i < n; i++) {
    	
    	cows[i] = Integer.parseInt(fin.readLine()) % 7;
    	
    	if(i == 0) {
    		prefixSum[i] = cows[i];
    	}
    	
    	else {
    		prefixSum[i] = (prefixSum[i - 1] + cows[i]) % 7;
    	}
    	
    	System.out.println(prefixSum[i]);
    	
    	if(firstOccurence[prefixSum[i]] == -1) {
    		
    		firstOccurence[prefixSum[i]] = i;
    		
    	}
    	
    	lastOccurence[prefixSum[i]] = i;
    	
    }
    
    int max = 0;
    
    
    for(int i = 0; i < 7; i++) {
    	
    	if(lastOccurence[i] - firstOccurence[i] > max) {
    		
    		max = lastOccurence[i] - firstOccurence[i];
    		
    	}
    	
    }
    
    fout.println(max);
    
    fin.close();
    fout.close();
    
	}
}