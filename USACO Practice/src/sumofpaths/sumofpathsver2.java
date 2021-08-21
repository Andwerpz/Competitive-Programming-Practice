package sumofpaths;

import java.util.*;
import java.io.*;

public class sumofpathsver2 {
	
	static long[] nums;
	static long[][] dp;
	static long mod = (long) (1e9 + 7);
	
	public static void main(String[] args) throws IOException {
		
		//1467D
		
		//confirmed, the tutorial is magic. 
		
		//first, given dp[i][j], where i is the number of moves taken, and j is the index position, calculate how many good paths of length i will end at index position j. 
		//notice that dp[i][j] also represents the number of good paths of length i that start at index j. 
		
		//here is the magic:
		
		//Let a[i][j] denote the number of times cell j appears after exactly i moves in all valid paths of length k. 
		//Well a[i][j] = dp[i][j] * dp[k - i][j] because we can split a path of length k into two paths of length i and length k - i, with the first path ending at cell i and the second path starting at cell j.
		
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
		for(int i = 0; i < k + 1; i++) {
			for(int j = 0; j < n; j++) {
				amtSelected[j] += dp[i][j] * dp[k - i][j];
				amtSelected[j] %= mod;
			}
		}
//		System.out.println();
//		for(long[] i : dp) {
//			for(long j : i) {
//				System.out.print(j + " ");
//			}
//			System.out.println();
//		}
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
			//System.out.println(diff + " " + ans);
			ans += diff;
			ans %= mod;
			if(ans < 0) {
				//System.out.println("YES");
				ans += mod;
			}
			else {
				//System.out.println("NO");
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
