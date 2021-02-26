/*
ID: andwerp2
LANG: JAVA
TASK: maxcross
*/

//package maxcross;

import java.io.*;
import java.util.*;

class maxcross {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new FileReader("maxcross.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("maxcross.out")));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    int k = Integer.parseInt(st.nextToken());
    int b = Integer.parseInt(st.nextToken());
    
    HashSet<Integer> brokenLights = new HashSet<Integer>();
    int[] prefixSum = new int[n];
    
    for(int i = 0; i < b; i++) {
    	
    	brokenLights.add(Integer.parseInt(fin.readLine()) - 1);
    	
    }
    
    if(brokenLights.contains(0)) {
    	prefixSum[0] = 1;
    }
    
    else {
    	prefixSum[0] = 0;
    }
    
    for(int i = 1; i < n; i++) {
    	
    	if(brokenLights.contains(i)) {
    		prefixSum[i] = prefixSum[i - 1] + 1;
    	}
    	
    	else {
    		prefixSum[i] = prefixSum[i - 1];
    	}
    	
    }
    
    int min = Integer.MAX_VALUE;
    
    for(int i = 0; i < prefixSum.length - k; i++) {
    	
    	if(prefixSum[i + k] - prefixSum[i] < min) {
    		min = prefixSum[i + k] - prefixSum[i];
    	}
    	
    }
    
    fout.println(min);
    
    
    fin.close();
    fout.close();
    
	}
}