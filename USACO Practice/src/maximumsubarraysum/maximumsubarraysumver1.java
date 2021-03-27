
package maximumsubarraysum;

import java.io.*;
import java.util.*;

public class maximumsubarraysumver1 {
	public static void main (String [] args) throws IOException {
		
	//to find the max subarray sum we use kadanes algorithm
		
	//alternatively, we could generate a prefix sum and find the minimum and maximum values. Subtract those and you find the maximum subarray sum
    
    BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    long sum = Integer.MIN_VALUE / 2;
    st = new StringTokenizer(fin.readLine());
    long max = sum;
    
    for(int i = 0; i < n; i++) {
    	int a = Integer.parseInt(st.nextToken());
    	if(a > sum + a) {
    		sum = a;
    	}
    	else {
    		sum += a;
    	}
    	if(max < sum) {
    		max = sum;
    	}
    }
    
    StringBuilder fout = new StringBuilder();
    fout.append(max).append("\n");
    
    System.out.print(fout);
    fin.close();
    
	}
}