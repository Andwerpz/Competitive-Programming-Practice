
package subarraysums2;

import java.io.*;
import java.util.*;

public class subarraysums2ver1 {
	public static void main (String [] args) throws IOException {
		
	//this solution too slow, we can't go through all the subarrays even with prefix sums
    
    Scanner fin = new Scanner(System.in);
    StringTokenizer st = new StringTokenizer(fin.nextLine());
    
    int n = Integer.parseInt(st.nextToken());
    int x = Integer.parseInt(st.nextToken());
    
    int[] nums = new int[n];
    int[] pfx = new int[n + 1];
    
    st = new StringTokenizer(fin.nextLine());
    
    for(int i = 0; i < n; i++) {
    	pfx[i + 1] = pfx[i] + Integer.parseInt(st.nextToken());
    }
    
    int counter = 0;
    
    for(int i = 0; i < pfx.length; i++) {
    	
    	for(int j = i + 1; j < pfx.length; j++) {
    		
    		if(pfx[j] - pfx[i] == x) {
    			counter ++;
    		}
    		
    	}
    	
    }
    
    System.out.println(counter);
    
    fin.close();
    
	}
}