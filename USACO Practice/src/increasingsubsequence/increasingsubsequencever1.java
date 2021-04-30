package increasingsubsequence;

import java.util.*;
import java.io.*;

public class increasingsubsequencever1 {
	public static void main(String[] args) throws IOException {
		
		//slow solution, O(n^2)
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		int n = Integer.parseInt(fin.readLine());
		int[] nums = new int[n];
		int[] dp = new int[n];	//save the longest increasing subsequence ending at index i
		int[] dpSearch = new int[n];
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
		}
		int max = 0;
		for(int i = 0; i < n; i++) {
			for(int j : dp) {
				System.out.print(j + " ");
			}
			System.out.println();
			int cur = nums[i];
			int ans = 0;
			for(int j = 0; j < i; j++) {
				if(nums[j] < nums[i]) {
					ans = Math.max(dp[j], ans);
				}
			}
			dp[i] = ans + 1;
			max = Math.max(dp[i], max);
		}
		System.out.println(max);
	}
}
