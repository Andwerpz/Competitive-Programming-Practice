
//package subarraysums2;

import java.io.*;
import java.util.*;

public class subarraysums2 {
	public static void main (String [] args) throws IOException {
		
	//this solution uses a dictionary. In order for a subarray to add up to x, the two prefix sums have to be pfx[i] - pfx[j] with pfx[j] = pfx[i] - x.
	//thus, for every prefix sum, we can see whether or not that entry, minus x exists within the prefix sum array, if it does, 
	//then we increment the counter and the
    
    Scanner fin = new Scanner(System.in);
    StringTokenizer st = new StringTokenizer(fin.nextLine());
    
    int n = Integer.parseInt(st.nextToken());
    int x = Integer.parseInt(st.nextToken());
    
    int[] nums = new int[n];
    long[] pfx = new long[n + 1];
    
    st = new StringTokenizer(fin.nextLine());
    
    HashMap<Long, Long> dict = new HashMap<Long, Long>();
    
    long counter = 0;
    
    for(int i = 0; i < n + 1; i++) {
    	
    	if(i != 0) {
    		pfx[i] = pfx[i - 1] + Integer.parseInt(st.nextToken());
    	}
    	
    	
    	
    	//System.out.println(pfx[i]);
    	
    	if(dict.containsKey(pfx[i] - x)) {
    		
    		counter += dict.get(pfx[i] - x);
    		
    	}
    	
    	if(dict.containsKey(pfx[i])) {
    		
    		dict.put(pfx[i], dict.get(pfx[i]) + 1);
    		
    	}
    	
    	else {
    		
    		dict.put(pfx[i], (long) 1);
    		
    	}
    	
    }
    
    System.out.println(counter);
    
    fin.close();
    
	}
}