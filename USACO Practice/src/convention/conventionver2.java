/*
ID: andwerp1
LANG: JAVA
TASK: convention
*/

package convention;

import java.io.*;
import java.util.*;

class conventionver2 {
	
	static boolean isValid(int[] cowTimes, int maxWait, int busSize, int numBusses) {
		
		System.out.println("max wait " + maxWait);
		
		int curBus = 0;
		int busCounter = 0;
		
		int curBusStart = 0;
		
		for(int i = 0; i < cowTimes.length; i++) {
			
			
			
			curBus++;
			
			if(curBus == busSize || (i + 1 < cowTimes.length && cowTimes[i + 1] - cowTimes[curBusStart] - 1 >= maxWait)) {
				
				busCounter ++;
				curBus = 0;
				curBusStart = i + 1;
				
			}
			
		}
		
		if(numBusses < busCounter) {
			return false;
		}
		
		else if(numBusses == busCounter) {
			if(curBus > 0) {
				return false;
			}
		}
		
		return true;
		
	}
	
	public static void main (String [] args) throws IOException {
		
	//in order to find the minimum wait time, instead of trying to optimize the busses and find the maximum wait time, we can just assign a maximum wait time,
	//and send the buses when the wait time is reached.
		
	//then we can binary search for the minimum wait time that results in a valid configuration of buses.
    
    BufferedReader fin = new BufferedReader(new FileReader("convention.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("convention.out")));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    int m = Integer.parseInt(st.nextToken());
    int c = Integer.parseInt(st.nextToken());
    
    int[] cowTimes = new int[n];
    
    st = new StringTokenizer(fin.readLine());
    
    for(int i = 0; i < n; i++) {
    	
    	cowTimes[i] = Integer.parseInt(st.nextToken());
    	
    }
    
    Arrays.sort(cowTimes);
    
    int high = 1000000000;
    int low = 0;
    
    int mid = low + (high - low) / 2;
    
    int ans = high;
    
    while(low <= high) {
    	
    	if(isValid(cowTimes, mid, c, m)) {
    		
    		ans = mid;
    		high = mid - 1;
    		
    	}
    	
    	else {
    		
    		low = mid + 1;
    		
    	}
    	
    	mid = low + (high - low) / 2;
    	
    }
    
    //System.out.println(isValid(cowTimes, 4, c, m));
    
    System.out.println(ans);
    
    fout.println(ans);
    
    fin.close();
    fout.close();
    
	}
}