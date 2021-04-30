package marvologauntsring;

import java.util.*;
import java.io.*;

public class marvologauntsringver3 {
	public static void main(String[] args) throws IOException {
		
		//so we do three passes, considering one multiplier at a time. 
		//to find the max value for one multipler, is pretty easy, just iterate through the entire array.
		//to find the max for two, you just iterate through the entire array, and find the maximum sum of both the second number, and the max of the first number at the current position.
		//for three and up, it's just the same thing, you can treat the first two, or any number,  as a single entity, since you already calculated the maximum value at any position.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		long[] m = new long[3];
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		for(int i = 0; i < 3; i++) {
			m[i] = Integer.parseInt(st.nextToken());
		}
		long[] nums = new long[n];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
		}
		long[][] dp = new long[3][n];	//dp[i][j]: stores the largest sum that we can achieve using i values considering up to the jth number.
		for(int i = 0; i < 3; i++) {
			Arrays.fill(dp[i], Long.MIN_VALUE);
		}
		for(int i = 0; i < 3; i++) {
			for(int j = 0; j < n; j++) {
				if(j == 0) {
					if(i == 0) {
						dp[0][0] = nums[0] * m[0];
						//System.out.println(nums[0] * m[0]);
					}
					else {
						dp[i][0] = dp[i - 1][0] + nums[0] * m[i];
					}
				}
				else {
					if(i == 0) {
						dp[0][j] = Math.max(nums[j] * m[0], dp[0][j - 1]);
					}
					else {
						dp[i][j] = Math.max(nums[j] * m[i] + dp[i - 1][j], dp[i][j - 1]);
					}
				}
			}
		}
		
		System.out.println(dp[2][n - 1]);
	}
}
