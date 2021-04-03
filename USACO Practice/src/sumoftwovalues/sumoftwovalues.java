
//package sumoftwovalues;

import java.io.*;
import java.util.*;

public class sumoftwovalues {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    int x = Integer.parseInt(st.nextToken());
    int[] nums = new int[n];
    HashMap<Integer, Integer> dict = new HashMap<Integer, Integer>();
    
    st = new StringTokenizer(fin.readLine());
    
    int a = 0;
    int b = 0;
    
    boolean isPossible = false;
    
    for(int i = 0; i < n; i++) {
    	nums[i] = Integer.parseInt(st.nextToken());
    	if(!dict.containsKey(nums[i])) {
    		dict.put(nums[i], i);
    	}
    	if(dict.containsKey(x - nums[i]) && dict.get(x - nums[i]) != i) {
    		a = i;
    		b = dict.get(x - nums[i]);
    		isPossible = true;
    		break;
    	}
    }
    
    if(!isPossible) {
    	System.out.println("IMPOSSIBLE");
    }
    else {
    	System.out.println((a + 1) + " " + (b + 1));
    }
    
    
    StringBuilder fout = new StringBuilder();
    
    System.out.print(fout);
    fin.close();
    
	}
}