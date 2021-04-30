package bargain;

import java.util.*;
import java.io.*;

public class bargainver2 {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		char[] s = fin.readLine().toCharArray();
		int n = s.length;
		int[] nums = new int[n];
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(s[i] + "");
			System.out.println(nums[i]);
		}
		int mod = 1000000007;
		long ans = 0;
		long sum = 0;
		long p = 1;
		for(long i = n - 1; i >= 0; i--) {
			long k = (i * (i + 1) / 2 % mod * p % mod + sum) % mod;
	        sum = (sum + p * (n - i) % mod) % mod;
	        p = p * 10 % mod;
	        ans = (ans + nums[(int)i] * k % mod) % mod;
	        System.out.println(sum + " " + p + " " + k);
		}
		System.out.println(ans);
	}
}
