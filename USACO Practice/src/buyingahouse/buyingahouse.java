
//package buyingahouse;

import java.io.*;
import java.util.*;

public class buyingahouse {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    int m = Integer.parseInt(st.nextToken()) - 1;
    int k = Integer.parseInt(st.nextToken());
    
    int min = Integer.MAX_VALUE;
    st = new StringTokenizer(fin.readLine());
    
    for(int i = 0; i < n; i++) {
    	int input = Integer.parseInt(st.nextToken());
    	if(input <= k && Math.abs(m - i) < min && input != 0) {
    		min = Math.abs(m - i);
    	}
    }
    
    System.out.println(min * 10);
    
    fin.close();
    
	}
}