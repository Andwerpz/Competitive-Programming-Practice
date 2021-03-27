/*
ID: andwerp1
LANG: JAVA
TASK: maximummedian
*/

package maximummedian;

import java.io.*;
import java.util.*;

public class maximummedianver1 {
	public static void main (String [] args) throws IOException {
    
    Scanner fin = new Scanner(System.in);
    StringTokenizer st = new StringTokenizer(fin.nextLine());
    
    int n = Integer.parseInt(st.nextToken());
    int k = Integer.parseInt(st.nextToken());
    
    int[] nums = new int[n];
    
    st = new StringTokenizer(fin.nextLine());
    
    for(int i = 0; i < n; i++) {
    	
    	nums[i] = Integer.parseInt(st.nextToken());
    	
    }
    
    Arrays.sort(nums);
    
    boolean done = false;
    
    int offset = 0;
    int pointer = n / 2;
    
    
    
    while(!done) {
    	
    	
    	
    	 while(pointer < nums.length && nums[pointer] == nums[n / 2] + offset) {
	    	pointer++;
	    }
    	 
    	if(pointer < nums.length) {
    		
	    	int addAmount = nums[pointer] - (nums[n / 2] + offset);
	    	
	    	if(k >= (long)addAmount * (pointer - (n / 2) - 1)) {
	    		k -= addAmount;
	    		offset += addAmount;
	    	}
	    	
	    	else {
	    		done = true;
	    	}
    		
    	}
    	
    	else {
    		done = true;
    	}
    	System.out.println(pointer + " " + k);
    }
    
    System.out.println(nums[n / 2] + offset + k / (pointer - (n / 2)));
    
    fin.close();
    
	}
}