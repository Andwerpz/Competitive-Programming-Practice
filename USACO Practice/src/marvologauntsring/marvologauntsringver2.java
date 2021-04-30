package marvologauntsring;

import java.util.*;
import java.io.*;

public class marvologauntsringver2 {
	public static void main(String[] args) throws IOException {
		
		//we consider one number at a time. We start out with all numbers multiplying with the first number.
		//when considering the next number, we can switch the third, second and third, or all three to the new number, or we could stay on the original values. 
		//choose the maximum option and repeat.
		
		//too greedy, needs three passes
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		long[] m = new long[3];
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		for(int i = 0; i < 3; i++) {
			m[i] = Integer.parseInt(st.nextToken());
		}
		long[] nums = new long[n];
		int[] dp = new int[3];	//saves the index in which the multipliers multiply with for each number.
		long ans = 0;
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
		}
		ans = m[0] * nums[0] + m[1] * nums[0] + m[2] * nums[0];
		for(int i = 1; i < n; i++) {
			if(m[0] * nums[dp[0]] + m[1] * nums[dp[1]] + m[2] * nums[i] > ans) {
				dp[2] = i;
				ans = m[0] * nums[dp[0]] + m[1] * nums[dp[1]] + m[2] * nums[i];
			}
			if(m[0] * nums[dp[0]] + m[1] * nums[i] + m[2] * nums[i] > ans) {
				dp[1] = i;
				dp[2] = i;
				ans = m[0] * nums[dp[0]] + m[1] * nums[i] + m[2] * nums[i];
			}
			if(m[0] * nums[i] + m[1] * nums[i] + m[2] * nums[i] > ans) {
				dp[0] = i;
				dp[1] = i;
				dp[2] = i;
				ans = m[0] * nums[i] + m[1] * nums[i] + m[2] * nums[i];
			}
		}
		System.out.println(ans);
	}
}
