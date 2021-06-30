//package kforthepriceofonehardversion;

import java.util.*;
import java.io.*;

public class kforthepriceofonehardversion {
	public static void main(String[] args) throws IOException {
		
		//1282B2
		
		//simple dp solution. For each number of goods bought, what is the minimum amount of money that you can spend. 
		//dp[i + 1] = Math.min(dp[i + 1], dp[i] + goods[i]);
		//dp[i + k] = Math.min(dp[i + k], dp[i] + goods[i + k - 1]);
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int p = Integer.parseInt(st.nextToken());
			int k = Integer.parseInt(st.nextToken());
			int[] goods = new int[n];
			int[] dp = new int[n + 1];
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				goods[i] = Integer.parseInt(st.nextToken());
			}
			Arrays.sort(goods);
			Arrays.fill(dp, -1);
			dp[0] = 0;
			int max = 0;
			for(int i = 0; i < dp.length; i++) {
				if(dp[i] != -1) {
					max = i;
					if(i + 1 <= n && p - (dp[i] + goods[i]) >= 0) {
						dp[i + 1] = Math.min(dp[i + 1] == -1? Integer.MAX_VALUE : dp[i + 1], dp[i] + goods[i]);
					}
					if(i + k <= n && p - (dp[i] + goods[i + k - 1]) >= 0) {
						dp[i + k] = Math.min(dp[i + k] == -1? Integer.MAX_VALUE : dp[i + k], dp[i] + goods[i + k - 1]);
					}
				}
				
			}
//			for(int i : dp) {
//				System.out.print(i + " ");
//			}
//			System.out.println();
			fout.append(max).append("\n");
		}
		System.out.print(fout);
	}
}
