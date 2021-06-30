//package elimination;

import java.util.*;
import java.io.*;

public class elimination {
	public static void main(String[] args) throws IOException {
		
		//417A
		
		//simple dp problem. Find the minimum cost to get above n * m finalists
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int c = Integer.parseInt(st.nextToken());
		int d = Integer.parseInt(st.nextToken());
		st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(fin.readLine());
		int[] dp = new int[100000];
		Arrays.fill(dp, -1);
		dp[k] = 0;
		for(int i = 0; i < dp.length; i++) {
			if(dp[i] != -1 && i + n < dp.length) {
				if(dp[i + n] == -1) {
					dp[i + n] = dp[i] + c;
				}
				else {
					dp[i + n] = Math.min(dp[i + n], dp[i] + c);
				}
			}
			if(dp[i] != -1 && i + 1 < dp.length) {
				if(dp[i + 1] == -1) {
					dp[i + 1] = dp[i] + d;
				}
				else {
					dp[i + 1] = Math.min(dp[i + 1], dp[i] + d);
				}
			}
		}
//		for(int i : dp) {
//			System.out.print(i + " ");
//		}
//		System.out.println();
		int ans = Integer.MAX_VALUE;
		for(int i = 0; i < dp.length; i++) {
			if(i >= n * m) {
				ans = Math.min(ans, dp[i]);
			}
		}
		System.out.println(ans == -1? "0" : ans);
	}
}
