
package subarraydivisibility;

import java.io.*;
import java.util.*;

public class subarraydivisibilityver1 {
	public static void main (String [] args) throws IOException {
		
	//we use a dictionary to count how many times a prefix sum has a remainder of any value < n
	//since the interval between the two prefix sums with the same remainder will be divisible by n, we can just iterate through the array once.
    
    Scanner fin = new Scanner(System.in);
    StringTokenizer st = new StringTokenizer(fin.nextLine());
    
    int n = Integer.parseInt(st.nextToken());
    
    long[] pfx = new long[n + 1];
    
    st = new StringTokenizer(fin.nextLine());
    
    for(int i = 1; i < n + 1; i++) {
    	
    	pfx[i] = pfx[i - 1] + Integer.parseInt(st.nextToken());
    	
    }
    
    long counter = 0;
    
    HashMap<Long, Long> dict = new HashMap<Long, Long>();
    
    for(int i = 0; i < pfx.length; i++) {
    	
    	//we need to compensate for negative sums
    	
    	if(pfx[i] < 0 && pfx[i] % n != 0) {
    		pfx[i] = n - Math.abs(pfx[i] % n);
    	}
    	
    	else {
    		pfx[i] = Math.abs(pfx[i] % n);
    	}
    	//pfx[i] = Math.abs(pfx[i] % n);
    	System.out.println(pfx[i]);
    	if(dict.containsKey(pfx[i])) {
    		
    		counter += dict.get(pfx[i]);
    		
    		dict.put(pfx[i], dict.get(pfx[i]) + 1);
    		
    	}
    	
    	else {
    		
    		dict.put(pfx[i], (long) 1);
    		
    	}
    	
    	
    	
    }
    

    long test = 0;
    
    for(int i = 0; i < n; i++) {
    	
    	if(dict.containsKey((long)i)) {
    		
    		test += dict.get((long)i) * (dict.get((long)i) - 1) / 2;
    		
    	}
    	
    }
    
    System.out.println(test);
    
    System.out.println(counter);
    
    fin.close();
    
	}
}