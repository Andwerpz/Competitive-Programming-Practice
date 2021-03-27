/*
ID: andwerp1
LANG: JAVA
TASK: angry
*/

//package angry;

import java.io.*;
import java.util.*;

public class angry {
	
	static boolean isValid(int power, int k, int[] haybales) {
		
		int pointer = 0;
		
		for(int i = 0; i < k; i++) {
			
			//System.out.println(haybales[pointer]);
			
			long range = (long)haybales[pointer] + (long)(power * 2);
			
			while(pointer < haybales.length && haybales[pointer] <= range) {
				pointer++;
			}
			
			if(pointer == haybales.length) {
				return true;
			}
			
		}
		
		return false;
		
	}
	
	public static void main (String [] args) throws IOException {
		
	//to solve this one, we will use a greedy algorithm to determine whether or not a certain power level will be able to destroy all the haybales
	//and we will binary search the power levels until we find the lowest one that works
    
    BufferedReader fin = new BufferedReader(new FileReader("angry.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("angry.out")));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    int k = Integer.parseInt(st.nextToken());
    
    int[] haybales = new int[n];
    
    for(int i = 0; i < n; i++) {
    	haybales[i] = Integer.parseInt(fin.readLine());
    }
    
    Arrays.sort(haybales);
    
    int high = 1000000000;	//1 billion
    int low = 0;
    
    int mid = low + (high - low) / 2;
    
    int ans = high;
    
    while(low <= high) {
    	
    	//System.out.println(low + " " + high);
    	
    	if(isValid(mid, k, haybales)) {
    		
    		high = mid - 1;
    		
    		if(ans > mid) {
    			//System.out.println("new ans");
    			ans = mid;
    		}
    		
    	}
    	
    	else {
    		low = mid + 1;
    	}
    	
    	mid = low + (high - low) / 2;
    	
    }
    
    fout.println(ans);
    
    fin.close();
    fout.close();
    
	}
}