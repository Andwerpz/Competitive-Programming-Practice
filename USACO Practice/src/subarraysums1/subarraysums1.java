
//package subarraysums1;

import java.io.*;
import java.util.*;

public class subarraysums1 {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    int x = Integer.parseInt(st.nextToken());
    long pfx = 0;
    HashMap<Long, Long> dict = new HashMap<Long, Long>();
    dict.put((long)0, (long)1);	//for subarrays consisting of one entry equal to x
    
    long ans = 0;
    st = new StringTokenizer(fin.readLine());
    for(int i = 0; i < n; i++) {
    	pfx += Integer.parseInt(st.nextToken());
    	if(dict.containsKey(pfx - x)) {
    		ans += dict.get(pfx - x);
    	}
    	if(dict.containsKey(pfx)) {
    		dict.put(pfx, dict.get(pfx) + 1);
    	}
    	else {
    		dict.put(pfx, (long)1);
    	}
    }
    
    System.out.println(ans);
    
    fin.close();
    
	}
}