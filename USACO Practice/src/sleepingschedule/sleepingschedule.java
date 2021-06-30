//package sleepingschedule;

import java.util.*;
import java.io.*;

public class sleepingschedule {
	public static void main(String[] args) throws IOException {
		
		//1324E
		
		//simple dp problem
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int h = Integer.parseInt(st.nextToken());
		int l = Integer.parseInt(st.nextToken());
		int r = Integer.parseInt(st.nextToken());
		int[][] dp = new int[n][h];
		st = new StringTokenizer(fin.readLine());
		int[] nums = new int[n];
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
		}
		for(int i = 0; i < n; i++) {
			Arrays.fill(dp[i], -1);
		}
		int first = nums[0];
		dp[0][first % h] = (first >= l && first <= r)? 1 : 0;
		dp[0][(first - 1) % h] = (first - 1 >= l && first - 1 <= r)? 1 : 0;
		int ans = 0;
		for(int i = 1; i < n; i++) {
			int cur = nums[i];
			for(int j = 0; j < h; j++) {
				if(dp[i - 1][j] != -1) {
					int next = (j + cur) % h;
					dp[i][next] = Math.max(((next >= l && next <= r)? 1 : 0) + dp[i - 1][j], dp[i][next]);
					next --;
					if(next == -1) {
						next = h - 1;
					}
					dp[i][next] = Math.max(((next >= l && next <= r)? 1 : 0) + dp[i - 1][j], dp[i][next]);
				}
			}
		}
		for(int i = 0; i < h; i++) {
			ans = Math.max(dp[n - 1][i], ans);
		}
		System.out.println(ans);
	}
}
