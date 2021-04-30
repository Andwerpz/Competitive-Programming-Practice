//package dicecombinations;

import java.util.*;
import java.io.*;

public class dicecombinations {
	
	static int[] dp;
	static int mod = 1000000007;
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		int n = Integer.parseInt(fin.readLine());
		dp = new int[n + 1];
		dp[0] = 1;
		for(int i = 1; i < dp.length; i++) {
			for(int j = 1; j <= 6; j++) {
				if(i - j >= 0) {
					dp[i] += dp[i - j];
					dp[i] %= mod;
				}
			}
		}
		System.out.println(dp[n]);
	}
}
