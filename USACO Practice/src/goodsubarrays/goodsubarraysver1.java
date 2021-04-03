
package goodsubarrays;

import java.io.*;
import java.util.*;

public class goodsubarraysver1 {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int t = Integer.parseInt(st.nextToken());
    StringBuilder fout = new StringBuilder();
    
    for(int i = 0; i < t; i++) {
    	int n = Integer.parseInt(fin.readLine());
    	HashMap<Long, Long> dict = new HashMap<Long, Long>();
    	dict.put((long)0, (long)1);
    	long ans = 0;
    	long pfx = 0;
    	String input = fin.readLine();
    	for(int j = 0; j < n; j++) {
    		pfx += (long) Integer.parseInt(input.charAt(j) + "") - 1;
    		if(dict.containsKey(pfx)) {	//look for pfx because we want sums of 0
    			ans += dict.get(pfx);
    		}
    		if(dict.containsKey(pfx)) {
    			dict.put(pfx, dict.get(pfx) + 1);
    		}
    		else {
    			dict.put(pfx, (long)1);
    		}
    	}
    	fout.append(ans + "\n");
    }
    
    System.out.print(fout);
    fin.close();
    
	}
}