//package minimizingcoins;

import java.util.*;
import java.io.*;

public class minimizingcoins {
	
	static int[] coins;
	static int[] dp;
	
	public static int solve(int remaining) {
		if(remaining < 0) {
			return -1;
		}
		if(remaining == 0) {
			return 0;
		}
		if(dp[remaining] != -2) {
			return dp[remaining];
		}
		int ans = -1;
		for(int i = 0; i < coins.length; i++) {
			int next = solve(remaining - coins[i]);
			if(next != -1) {
				if(ans == -1) {
					ans = next + 1;
				}
				ans = Math.min(ans, next + 1);
			}
		}
		dp[remaining] = ans;
		return ans;
	}
	
	public static void main(String[] args) throws IOException {
		
		//use recursive dp and memorization(memoization)
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		dp = new int[1000001];	//to facilitate memoization
		Arrays.fill(dp, -2);
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int x = Integer.parseInt(st.nextToken());
		st = new StringTokenizer(fin.readLine());
		coins = new int[n];
		for(int i = 0; i < n; i++) {
			coins[i] = Integer.parseInt(st.nextToken());
		}
		dp[0] = 0;
		for(int i = 1; i < dp.length; i++) {
			//System.out.println(i);
			solve(i);
		}
		System.out.println(solve(x));
	}
}
