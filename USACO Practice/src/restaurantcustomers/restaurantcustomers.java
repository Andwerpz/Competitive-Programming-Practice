
//package restaurantcustomers;

import java.io.*;
import java.util.*;

public class restaurantcustomers {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    int[][] times = new int[n * 2][2];
    
    for(int i = 0; i < n; i++) {
    	st = new StringTokenizer(fin.readLine());
    	int a = Integer.parseInt(st.nextToken());
    	int b = Integer.parseInt(st.nextToken());
    	times[i] = new int[] {a, 0};
    	times[i + n] = new int[] {b, 1};
    }
    
    Arrays.sort(times, (a, b) -> a[0] - b[0]);
    
    int max = 0;
    int cur = 0;
    
    for(int i = 0; i < times.length; i++) {
    	
    	//System.out.println(cur);
    	
    	if(times[i][1] == 0) {
    		cur++;
    	}
    	
    	else {
    		cur--;
    	}
    	
    	if(cur > max) {
    		max = cur;
    	}
    	
    }
    
    System.out.println(max);
    
    //StringBuilder fout = new StringBuilder();
    
    //System.out.print(fout);
    fin.close();
    
	}
}