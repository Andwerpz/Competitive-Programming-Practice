//package removingdigits;

import java.util.*;
import java.io.*;

public class removingdigits {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		int n = Integer.parseInt(fin.readLine());
		int[] dp = new int[n + 1];
		for(int i = 1; i < dp.length; i++) {
			int next = i;
			int ans = -1;
			int num = (int) Math.log10(next) + 1;
			for(int j = 0; j < num; j++) {
				int test = next % 10;
				next /= 10;
				if((ans == -1 || dp[i - test] + 1 < ans) && test != 0) {
					ans = dp[i - test] + 1;
				}
			}
			dp[i] = ans;
		}
		System.out.println(dp[n]);
	}
}
