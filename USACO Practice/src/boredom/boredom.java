//package boredom;

import java.util.*;
import java.io.*;

public class boredom {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		int[] nums = new int[n];
		long[] groups = new long[100001];
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
			groups[nums[i]] += nums[i];
		}
		long[][] dp = new long[2][groups.length];	//the best sum ending on group i either ending on picking the number, or not picking the number.
		//dp[0][i] = Math.max(dp[0][i - 1], dp[1][i - 1])
		//dp[1][i] = Math.max(dp[0][i - 1], dp[1][i - 2]) + groups[i];
		dp[0][0] = 0;
		dp[1][0] = groups[0];
		dp[0][1] = groups[0];
		dp[1][1] = groups[1];
		//System.out.println(dp[0][1] + " " + dp[1][1]);
		for(int i = 2; i < groups.length; i++) {
			dp[0][i] = Math.max(dp[0][i - 1], dp[1][i - 1]);
			dp[1][i] = Math.max(dp[0][i - 1], dp[1][i - 2]) + groups[i];
			//System.out.println(dp[0][i] + " " + dp[1][i]);
		}
		System.out.println(Math.max(dp[0][dp[0].length - 1], dp[1][dp[0].length - 1]));
	}
}
