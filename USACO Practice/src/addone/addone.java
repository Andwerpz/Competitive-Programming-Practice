//package addone;

import java.util.*;
import java.io.*;

public class addone {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		int t = Integer.parseInt(fin.readLine());
		int[] dp = new int[200005];	//maximum value for m
		int mod = 1000000007;
		for(int i = 0; i < 9; i++) {
			dp[i] = 2;
		}
		dp[9] = 3;
		for(int i = 10; i < dp.length; i++) {
			dp[i] = (dp[i - 9] + dp[i - 10]) % mod;
		}
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());
			long ans = 0;
			while(n > 0) {
				int next = n % 10;
				if(m + next < 10) {
					ans += 1;
				}
				else {
					ans += dp[m + next - 10];
				}
				ans %= mod;
				n /= 10;
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
