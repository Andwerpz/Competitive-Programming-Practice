//package planarreflections;

import java.util.*;
import java.io.*;

public class planarreflections {
	
	static int[][][] dp = new int[1001][1001][2];
	static int mod = 1000000007;
	static int n;
	static int k;
	
	public static int solve(int curr, int k, int dir) {
		if(k == 1) {
			return 1;
		}
		if(dp[curr][k][dir] != -1) {
			return dp[curr][k][dir];
		}
		int ans = 2;
		if(dir == 1) {	//left to right
			if(curr < n) {
				ans += solve(curr + 1, k, dir) - 1;
				ans %= mod;
			}
			if(curr > 1) {
				ans += solve(curr - 1, k - 1, 1 - dir) - 1;
				ans %= mod;
			}
			dp[curr][k][dir] = ans;
		}
		else {	//right to left
	        if (curr > 1) {
	            ans += solve(curr - 1, k, dir) - 1; 
	            ans %= mod;
	        }
	        if (curr < n) {
	            ans += solve(curr + 1, k - 1, 1 - dir) - 1;  
	        	ans %= mod;
	        }
	        dp[curr][k][dir] = ans;
	    }
		return ans;
	}
	
	public static void main(String[] args) throws IOException {
		
		//i don't have enough stack memory allocated to run this problem, but oj does
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			n = Integer.parseInt(st.nextToken());
			k = Integer.parseInt(st.nextToken());
			for(int i = 0; i < dp.length; i++) {
				for(int j = 0; j < dp[i].length; j++) {
					Arrays.fill(dp[i][j], -1);
				}
			}
			fout.append(solve(1, k, 1)).append("\n");
		}
		System.out.print(fout);
	}
}
