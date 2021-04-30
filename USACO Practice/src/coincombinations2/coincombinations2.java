//package coincombinations2;

import java.util.*;
import java.io.*;

public class coincombinations2 {
	public static void main(String[] args) throws IOException {
		
		//too slow, but the complexity is correct. Maybe try using c
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int x = Integer.parseInt(st.nextToken());
		int mod = 1000000007;
		int[] coins = new int[n];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			coins[i] = Integer.parseInt(st.nextToken());
		}
		int[][] dp = new int[n][x + 1];
		dp[0][0] = 1;
		for(int i = 0; i < coins.length; i++) {
			int curCoin = coins[i];
			for(int j = 0; j < dp[i].length; j++) {
				if(i != coins.length - 1) {
					dp[i + 1][j] = dp[i][j];
				}
				if(j + curCoin <= x) {
					dp[i][j + curCoin] += dp[i][j];
					dp[i][j + curCoin] %= mod;
				}
				//System.out.print(dp[i][j] + " ");
			}
			//System.out.println();
		}
		System.out.println(dp[n - 1][x]);
	}
}
