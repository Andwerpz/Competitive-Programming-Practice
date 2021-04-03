
//package polygon;

import java.io.*;
import java.util.*;

public class polygon {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int t = Integer.parseInt(st.nextToken());
    
    StringBuilder fout = new StringBuilder();
    
    while(t-- > 0) {
    	int n = Integer.parseInt(fin.readLine());
    	int[][] nums = new int[n][n];
    	for(int i = 0; i < n; i++) {
    		String input = fin.readLine();
    		for(int j = 0; j < n; j++) {
    			nums[i][j] = Integer.parseInt(input.charAt(j) + "");
    		}
    	}
    	boolean isValid = true;
    	for(int i = 0; i < n - 1; i++) {
    		for(int j = 0; j < n - 1; j++) {
    			if(nums[i][j] == 1) {
    				if(nums[i + 1][j] == 0 && nums[i][j + 1] == 0) {
    					isValid = false;
    					break;
    				}
    			}
    		}
    	}
    	fout.append((isValid? "YES" : "NO") + "\n");
    }
    
    System.out.print(fout);
    fin.close();
    
	}
}