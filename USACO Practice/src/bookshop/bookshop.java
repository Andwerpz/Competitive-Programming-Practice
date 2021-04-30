//package bookshop;

import java.util.*;
import java.io.*;

public class bookshop {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int x = Integer.parseInt(st.nextToken());
		int[] pages = new int[n];
		int[] costs = new int[n];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			costs[i] = Integer.parseInt(st.nextToken());
		}
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			pages[i] = Integer.parseInt(st.nextToken());
		}
		int[][] dp = new int[n][x + 1];
		for(int i = 0; i < n; i++) {
			int curCost = costs[i];
			int curPages = pages[i];
			for(int j = x; j >= 0; j--) {
				if(j - curCost >= 0) {
					dp[i][j] = Math.max(dp[i][j], dp[i][j - curCost] + curPages);
				}
				if(i != n - 1) {
					dp[i + 1][j] = dp[i][j];
				}
			}
		}
		System.out.println(dp[n - 1][x]);
	}
}
