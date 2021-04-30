//package ktree;

import java.util.*;
import java.io.*;

public class ktree {
	public static void main(String[] args) throws IOException {
		
		//use complementary counting
		//we need to guarantee that all sums have at least one node included that is above d. if you think about it, then the only paths that
		//violate the requirement are the ones that don't have any nodes above d. That is pretty simple to count, so what we do is count the number
		//of different paths that lead to n that we can possibly take, using all the edge weights at first, and then count the number of paths
		//to get to n that only use edge weights less than d. Subtract the set of all paths that only use weights less than d from the set of all paths, and you 
		//are left with the set of paths that use at least one node that is equal or greater than d.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		int d = Integer.parseInt(st.nextToken());
		long mod = 1000000007;
		long[][] dp = new long[n + 1][n + 1];	//dp[i][j]: ith node considered, j th sum, saving how many ways we can get there
//		for(int i = 0; i <= n; i++) {
//			dp[0][i] = (i >= d)? 1 : 0;
//		}
		dp[0][0] = 1;
		for(int i = 1; i <= n; i++) {
			for(int j = 0; j <= n; j++) {
				long cur = dp[i - 1][j];
				for(int m = 1; m <= k; m++) {
					if(m + j <= n) {
						dp[i][m + j] += cur;
						dp[i][m + j] %= mod;
					}
					else {
						break;
					}
				}
			}
			dp[i][n] += dp[i - 1][n];
			dp[i][n] %= mod;
		}
//		for(long[] i : dp) {
//			for(long j : i) {
//				System.out.print(j + " ");
//			}
//			System.out.println();
//		}
		long ansAll = dp[n][n];
		//System.out.println(dp[n][n]);
		dp = new long[n + 1][n + 1];
		dp[0][0] = 1;
		for(int i = 1; i <= n; i++) {
			for(int j = 0; j <= n; j++) {
				long cur = dp[i - 1][j];
				for(int m = 1; m < d; m++) {
					if(m + j <= n) {
						dp[i][m + j] += cur;
						dp[i][m + j] %= mod;
					}
					else {
						break;
					}
				}
			}
			dp[i][n] += dp[i - 1][n];
			dp[i][n] %= mod;
		}
//		for(long[] i : dp) {
//			for(long j : i) {
//				System.out.print(j + " ");
//			}
//			System.out.println();
//		}
		//System.out.println(ansAll - dp[n][n]);
		long ans = ansAll - dp[n][n];
		if(ans < 0) {
			ans += mod;
		}
		System.out.println(ans);
	}
}
