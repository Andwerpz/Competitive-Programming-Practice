package bargain;

import java.util.*;
import java.io.*;

public class bargainver1 {
	public static void main(String[] args) throws IOException {
		
		//too complicated, maybe fix later
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		char[] s = fin.readLine().toCharArray();
		int n = s.length;
		long mod = 1000000007;
		int[] nums = new int[n];
		long[] pfx = new long[n];
		long[] sfx = new long[n];
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(s[i] + "");
			if(i == 0) {
				pfx[i] = nums[i];
				sfx[i] = 0;
			}
			else {
				pfx[i] = pfx[i - 1] * 10 + nums[i];
				pfx[i] %= mod;
				sfx[i] = sfx[i - 1] * 10 + (nums[i] * i);
				sfx[i] %= mod;
				
			}
			System.out.println("PREFIX: " + pfx[i] + " SUFFIX: " + sfx[i]);
		}
		
		long[] dp = new long[n];
		long count = 1;
		for(int i = 0; i < n; i++) {
			if(i == 0) {
				dp[i] = 0;
			}
			else {
				dp[i] = dp[i - 1] + dp[i - 1] * 10 + (nums[i] * (count)) + pfx[i - 1];
				dp[i] %= mod;System.out.println(count + " " + dp[i]);
				if(i == 1) {
					count = 3;
				}
				else {
					count += 2 + i - 1;
				}
				count %= mod;
				
			}
		}
		System.out.println(dp[n - 1]);
	}
}
