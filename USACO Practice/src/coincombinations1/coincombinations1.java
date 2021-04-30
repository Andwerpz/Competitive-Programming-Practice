//package coincombinations1;

import java.util.*;
import java.io.*;

public class coincombinations1 {
	
	static long[] dp;
	static int[] coins;
	static int mod = 1000000007;
	
	public static long solve(int target) {
		long ans = 0;
		if(target < 0) {
			return 0;
		}
		else if(target == 0) {
			ans = 1;
		}
		else if(dp[target] != -1) {
			return dp[target];
		}
		else {
			for(int c : coins) {
				ans += solve(target - c);
			}
		}
		ans %= mod;
		dp[target] = ans;
		return ans;
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int x = Integer.parseInt(st.nextToken());
		dp = new long[1000001];
		Arrays.fill(dp, -1);
		coins = new int[n];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < coins.length; i++) {
			coins[i] = Integer.parseInt(st.nextToken());
		}
		for(int i = 0; i < dp.length; i++) {
			solve(i);
			//System.out.println(dp[i] + " " + i);
		}
		System.out.println(solve(x));
	}
}
