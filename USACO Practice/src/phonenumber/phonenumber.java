//package phonenumber;

import java.util.*;
import java.io.*;

public class phonenumber {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		char[] s = fin.readLine().toCharArray();
		int n = s.length;
		int[] nums = new int[n];
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(s[i] + "");
		}
		long[][] dp = new long[n][10];	//for each digit, track how many moves each digit will bring.
		Arrays.fill(dp[n - 1], 1);
		for(int i = n - 2; i >= 0; i--) {
			HashSet<Integer> chosen = new HashSet<Integer>();
			for(int j = 0; j < 10; j++) {
				int next = j + nums[i + 1];
				if(next % 2 == 0) {
					next /= 2;
					dp[i][j] = dp[i + 1][next];
					chosen.add(next);
				}
				else {
					next /= 2;
					dp[i][j] = dp[i + 1][next] + dp[i + 1][next + 1];
					chosen.add(next);
					chosen.add(next + 1);
				}
				//System.out.print(dp[i][j] + " ");
			}
			//System.out.println();
			for(int j = 0; j < 10; j++) {
				if(!chosen.contains(j)) {
					dp[i + 1][j] = 0;
				}
			}
		}
//		for(long[] i : dp) {
//			for(long j : i) {
//				System.out.print(j + " ");
//			}
//			System.out.println();
//		}
		long ans = 0;
		for(int i = 0; i < 10; i++) {
			ans += dp[0][i];
		}
		boolean contains = true;
		int curNum = nums[0];
		for(int i = 1; i < n; i++) {
			int next = curNum + nums[i];
			if(next % 2 == 0) {
				next /= 2;
				if(next == nums[i]) {
					curNum = next;
				}
				else {
					contains = false;
					break;
				}
			}
			else {
				next /= 2;
				if(next == nums[i]) {
					curNum = next;
				}
				else if(next + 1 == nums[i]) {
					curNum = next + 1;
				}
				else {
					contains = false;
					break;
				}
			}
		}
		ans -= contains? 1 : 0;
		System.out.println(ans);
	}
}
