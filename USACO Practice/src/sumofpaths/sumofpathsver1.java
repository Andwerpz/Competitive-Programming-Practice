package sumofpaths;

import java.util.*;
import java.io.*;

public class sumofpathsver1 {
	
	static long[] nums;
	static long[][] dp;
	static long mod = (long) (1e9 + 7);
	
	public static void main(String[] args) throws IOException {
		
		//1467D
		
		//still have to implement solution...
		
		//the tutorial is magic, i swear.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		int q = Integer.parseInt(st.nextToken());
		st = new StringTokenizer(fin.readLine());
		nums = new long[n];
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
		}
		dp = new long[k + 1][n];
		Arrays.fill(dp[0], 1);
		for(int i = 0; i < k; i++) {
			for(int j = 0; j < n; j++) {
				if(j != 0) {
					dp[i + 1][j - 1] += dp[i][j];
					dp[i + 1][j - 1] %= mod;
				}
				if(j != n - 1) {
					dp[i + 1][j + 1] += dp[i][j];
					dp[i + 1][j + 1] %= mod;
				}
			}
		}
		long[] amtSelected = new long[n];
		System.out.println((k / 2 + 1) + " " + ((k + 1) / 2));
		for(int i = 0; i < n; i++) {
			amtSelected[i] = dp[k][i] * (k / 2 + 1);
			//amtSelected[i] = dp[k][i] * ((k + 1) / 2);
			amtSelected[i] %= mod;
			if(i == 0 || i == n - 1) {
				amtSelected[i] += dp[k - 1][i] * ((k + 1) / 2);
				//amtSelected[i] += dp[k - 1][i] * (k / 2 + 1);
			}
			else {
				amtSelected[i] += (dp[k - 1][i] * ((k + 1) / 2)) * 2;
				//amtSelected[i] += (dp[k - 1][i] * (k / 2 + 1)) * 2;
			}
			amtSelected[i] %= mod;
			System.out.print(amtSelected[i] + " ");
		}
		System.out.println();
		for(long[] i : dp) {
			for(long j : i) {
				System.out.print(j + " ");
			}
			System.out.println();
		}
		StringBuilder fout = new StringBuilder();
		long ans = 0;
		for(int i = 0; i < n; i++) {
			ans += amtSelected[i] * nums[i];
			ans %= mod;
		}
		while(q-- > 0) {
			st = new StringTokenizer(fin.readLine());
			int index = Integer.parseInt(st.nextToken()) - 1;
			long next = Integer.parseInt(st.nextToken());
			long diff = next - nums[index];
			diff *= amtSelected[index];
			nums[index] = next;
			diff %= mod;
			System.out.println(diff + " " + ans);
			ans += diff;
			ans %= mod;
			if(ans < 0) {
				System.out.println("YES");
				ans += mod;
			}
			else {
				System.out.println("NO");
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
