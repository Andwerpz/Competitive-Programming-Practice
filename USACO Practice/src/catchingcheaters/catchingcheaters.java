//package catchingcheaters;

import java.util.*;
import java.io.*;

public class catchingcheaters {
	
	static char[] a, b;
	static int[][] dp;
	
	public static int getAns(int i, int j) {
		//printArray(dp);
		if(a[i] == b[j]) {
			//System.out.print("!");
			dp[i][j] = 2;
			if(i > 0 && j > 0 && a[i - 1] == b[j - 1]) {
				//System.out.println(dp[i - 1][j - 1] + 2);
				dp[i][j] = Math.max(dp[i][j], Math.max(2, dp[i - 1][j - 1] + 2));
			}
			if(i > 0 && a[i - 1] != b[j]) {
				dp[i][j] = Math.max(dp[i][j], Math.max(2, dp[i - 1][j] + 3));
			}
			if(j > 0 && a[i] != b[j - 1]) {
				dp[i][j] = Math.max(dp[i][j], Math.max(2, dp[i][j - 1] + 3));
			}
		}
		else {
			//System.out.print(".");
			dp[i][j] = -2;
			if(i > 0 && j > 0 && a[i - 1] == b[j - 1]) {
				dp[i][j] = Math.max(dp[i][j], Math.max(-2, dp[i - 1][j - 1] - 2));
			}
			if(i > 0 && a[i - 1] != b[j]) {
				dp[i][j] = Math.max(dp[i][j], Math.max(-2, dp[i - 1][j] - 1));
			}
			if(j > 0 && a[i] != b[j - 1]) {
				dp[i][j] = Math.max(dp[i][j], Math.max(-2, dp[i][j - 1] - 1));
			}
		}
		
		return dp[i][j];
	}
	
	public static void main(String[] args) throws IOException {
		
		//1446B
		
		//why did this one take so long to make???
		
		//the dp solution is of the same base idea as kadanes subarray with largest sum algorithm, just different specifics, and with a second dimension.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		a = fin.readLine().toCharArray();
		b = fin.readLine().toCharArray();
		dp = new int[n][m];
		int ans = 0;
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				ans = Math.max(ans, getAns(i, j));
			}
		}
		System.out.println(ans);
	}
}
