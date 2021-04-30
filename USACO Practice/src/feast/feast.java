//package feast;

import java.io.*;
import java.util.*;

public class feast {
	public static void main (String [] args) throws IOException {
		
	//since we can only drink water once, we keep two dp arrays, one with no water, and one with water.
    
    BufferedReader fin = new BufferedReader(new FileReader("feast.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("feast.out")));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    int t = Integer.parseInt(st.nextToken());
    int a = Integer.parseInt(st.nextToken());
    int b = Integer.parseInt(st.nextToken());
    boolean[] dp = new boolean[t + 1];
    boolean[] dpWater = new boolean[t + 1];
    int ans = 0;
    dp[0] = true;
    for(int i = 0; i < dp.length; i++) {
    	if(dp[i]) {
    		if(i + a <= t) {
    			dp[i + a] = true;
    		}
    		if(i + b <= t) {
    			dp[i + b] = true;
    		}
    		dpWater[i / 2] = true;
    		if(i > ans) {
    			ans = i;
    		}
    	}
    }
    for(int i = 0; i < dpWater.length; i++) {
    	if(dpWater[i]) {
    		if(i + a <= t) {
    			dpWater[i + a] = true;
    		}
    		if(i + b <= t) {
    			dpWater[i + b] = true;
    		}
    		if(i > ans) {
    			ans = i;
    		}
    	}
    }
    fout.println(ans);
    fin.close();
    fout.close();
    
	}
}