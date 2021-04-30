//package removalgame;

import java.util.*;
import java.io.*;

public class removalgame {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		int n = Integer.parseInt(fin.readLine());
		long[][] dp = new long[n][n];	//the max score for the interval low, high
		int[] nums = new int[n];
		StringTokenizer st = new StringTokenizer(fin.readLine());
		long sum = 0;
		for(int i = 0; i < n; i++) {
			dp[i][i] = Integer.parseInt(st.nextToken());
			nums[i] = (int) dp[i][i];
			sum += nums[i];
		}
		
		for(int i = 1; i < n; i++) {
			for(int j = 0; j < n - i; j++) {
				int l = j;
				int r = j + i;
				dp[l][r] = Math.max(nums[l] - dp[l + 1][r], nums[r] - dp[l][r - 1]);
			}
			
		}
		//System.out.println(dp[0][n - 1] + " " + sum);
		System.out.println((sum - dp[0][n - 1]) / 2 + dp[0][n - 1]);
	}
}
