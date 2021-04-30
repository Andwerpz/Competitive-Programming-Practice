//package ayoubandlostarray;

import java.util.*;
import java.io.*;

public class ayoubandlostarray {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		
		long[] op = new long[3];	//stores how many different numbers there are % 3
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int l = Integer.parseInt(st.nextToken());
		int r = Integer.parseInt(st.nextToken());
		int mod = 1000000007;
		long[][] dp = new long[n][3];
		int base = (r - l + 1) / 3;
		int offset = l % 3;	//huh
		int remainder = (r - l + 1) % 3;
		Arrays.fill(op, base);
		for(int i = offset; i < offset + remainder; i++) {
			op[i % 3] ++;
		}
		dp[0][0] = op[0];
		dp[0][1] = op[1];
		dp[0][2] = op[2];
		
		for(int i = 1; i < n; i++) {
			
			for(int j = 0; j < 3; j++) {
				for(int k = 0; k < 3; k++) {
					dp[i][(j + k) % 3] += dp[i - 1][j] * op[k];
					dp[i][(j + k) % 3] %= mod;
				}
			}
//			for(long j : dp[i]) {
//				System.out.print(j + " ");
//			}
//			System.out.println();
		}
		System.out.println(dp[n - 1][0]);
	}
}
