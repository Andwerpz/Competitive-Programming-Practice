
//package thanossort;

import java.io.*;
import java.util.*;

public class thanossort {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    int[] nums = new int[n];
    st = new StringTokenizer(fin.readLine());
    
    for(int i = 0; i < n; i++) {
    	nums[i] = Integer.parseInt(st.nextToken());
    }
    
    int high = n;
    int low = 0;
    int range = high - low;
    boolean done = false;
    
    while(!done && range > 2) {
    	boolean sorted = true;
    	for(int i = low; i < high - 1; i++) {
    		if(nums[i] > nums[i + 1]) {
    			sorted = false;
    			break;
    		}
    	}
    	if(sorted) {
    		done = true;
    	}
    	else {
    		int maxLow = 1;
    		int maxHigh = 1;
    		int counter = 1;
    		for(int i = low; i < low + (high - low) / 2 - 1; i++) {
    			if(nums[i] <= nums[i + 1]) {
    				counter ++;
    			}
    			else {
    				counter = 1;
    			}
    			if(maxLow < counter) {
    				maxLow = counter;
    			}
    		}
    		counter = 1;
    		for(int i = low + (high - low) / 2; i < high - 1; i++) {
    			if(nums[i] <= nums[i + 1]) {
    				counter ++;
    			}
    			else {
    				counter = 1;
    			}
    			if(maxHigh < counter) {
    				maxHigh = counter;
    			}
    		}
    		if(maxLow > maxHigh) {
    			high -= (high - low) / 2;
    		}
    		else {
    			low += (high - low) / 2;
    		}
    		range = high - low;
    		//System.out.println(maxLow + " " + maxHigh);
    	}
    	//System.out.println(low + " " + high);
    }
    
    if(range == 2) {
    	if(nums[low] <= nums[high - 1]) {
    		System.out.println(2);
    	}
    	else {
    		System.out.println(1);
    	}
    }
    else if(range == 1) {
    	System.out.println(1);
    }
    else {
    	System.out.println(range);
    }
    
//    StringBuilder fout = new StringBuilder();
//    
//    System.out.print(fout);
    fin.close();
    
	}
}