//package flowers;

import java.util.*;
import java.io.*;

public class flowers {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int t = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		long[] dp = new long[100001];
		dp[0] = 1;
		long mod = 1000000007;
		for(int i = 0; i < dp.length; i++) {
			if(i < k) {
				dp[i] = 1;
			}
			else {
				dp[i] = dp[i - 1] + dp[i - k];
				dp[i] %= mod;
			}
		}
		long[] pfx = new long[dp.length + 1];
		for(int i = 0; i < dp.length; i++) {
			pfx[i + 1] = pfx[i] + dp[i];
			pfx[i + 1] %= mod;
			//System.out.println(pfx[i + 1]);
		}
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			st = new StringTokenizer(fin.readLine());
			int a = Integer.parseInt(st.nextToken());
			int b = Integer.parseInt(st.nextToken());
			long ans = (long) pfx[b + 1] - pfx[a];
			if(ans < 0) {
				ans = mod + ans;
			}
			fout.append(ans).append("\n");
		}
		System.out.println(fout);
	}
}
