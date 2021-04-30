//package thesportsfestival;

import java.util.*;
import java.io.*;

public class thesportsfestival {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		long[][] dp = new long[n][n];
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int[] nums = new int[n];
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
		}
		Arrays.sort(nums);
		for(int i = 1; i < n; i++) {
			//System.out.println("loop");
			for(int j = i; j < n; j++) {
				dp[j - i][j] = nums[j] - nums[j - i] + Math.min(dp[j - i + 1][j], dp[j - i][j - 1]);
				//System.out.println(nums[j] - nums[j - i]);
			}
		}
//		for(long[] t : dp) {
//			for(long k : t) {
//				System.out.print(k + " ");
//			}
//			System.out.println();
//		}
		System.out.println(dp[0][n - 1]);
	}
}
