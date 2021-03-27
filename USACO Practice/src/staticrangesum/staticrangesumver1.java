
package staticrangesum;

import java.io.*;
import java.util.*;

public class staticrangesumver1 {
	public static void main (String [] args) throws IOException {
    
    Scanner fin = new Scanner(System.in);
    StringTokenizer st = new StringTokenizer(fin.nextLine());
    
    int n = Integer.parseInt(st.nextToken());
    int q = Integer.parseInt(st.nextToken());
    
    int[] nums = new int[n];
    int[] pfx = new int[n + 1];
    
    st = new StringTokenizer(fin.nextLine());
    
    for(int i = 0; i < n; i++) {
    	pfx[i + 1] = pfx[i] + Integer.parseInt(st.nextToken());
    }
    
    for(int i = 0; i < q; i++) {
    	
    	st = new StringTokenizer(fin.nextLine());
    	
    	int start = Integer.parseInt(st.nextToken());
    	int end = Integer.parseInt(st.nextToken());
    	
    	System.out.println(pfx[end] - pfx[start]);
    	
    }
    
    fin.close();
    
	}
}