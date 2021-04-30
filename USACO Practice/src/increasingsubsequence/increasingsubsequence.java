//package increasingsubsequence;

import java.util.*;
import java.io.*;

public class increasingsubsequence {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		int n = Integer.parseInt(fin.readLine());
		int[] dp = new int[n + 1];	//the index at which a subsequence of length i terminates. Take the one with the smallest ending value
		Arrays.fill(dp, Integer.MAX_VALUE);
		dp[0] = 0;
		int[] nums = new int[n];
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
		}
		for(int i = 0; i < n; i++) {
			int high = n;
			int low = 0;
			int mid = low + (high - low) / 2;
			int ans = high;
			int target = nums[i];
			while(low <= high) {	//finding the first number in dp that is greater or equal to the current number
				if(dp[mid] >= target) {
					if(ans > mid) {
						ans = mid;
					}
					high = mid - 1;
				}
				else {
					low = mid + 1;
				}
				mid = low + (high - low) / 2;
			}
			dp[ans] = target;
		}
		int ans = 0;
		for(int i = 0; i < dp.length; i++) {
			if(dp[i] != Integer.MAX_VALUE) {
				ans = i;
			}
			//System.out.print(dp[i] + " ");
		}
		System.out.println(ans);
	}
}
