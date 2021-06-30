package parenting101;

import java.util.*;
import java.io.*;

public class parenting101 {
	
	static int[][] dp;
	static int[] nums;
	
	public static int getLongestPalindrome(int l, int r) {
		if(dp[l][r] != -1) {
			return dp[l][r];
		}
		int ans = 0;
		if(l == r) {
			ans = 1;
		}
		else if(nums[l] == nums[r]) {
			if(Math.abs(l - r) == 1) {
				ans = 2;
			}
			else {
				ans = getLongestPalindrome(l + 1, r - 1) + 2;
			}
		}
		else {
			ans = Math.max(getLongestPalindrome(l + 1, r), getLongestPalindrome(l, r - 1));
		}
		dp[l][r] = ans;
		return ans;
	}
	
	public static void main(String[] args) throws IOException {
		
		//2021 Keep Austin Hacking
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		nums = new int[n];
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
		}
		dp = new int[n][n];
		for(int i = 0; i < n; i++) {
			Arrays.fill(dp[i], -1);
		}
		int ans = getLongestPalindrome(0, n - 1);
		System.out.println(ans);
	}
}
