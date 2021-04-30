//package dimaandsalad;

import java.util.*;
import java.io.*;

public class dimaandsalad {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		int[][] fruits = new int[n][2];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			fruits[i][0] = Integer.parseInt(st.nextToken());
		}
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			fruits[i][1] = Integer.parseInt(st.nextToken()) * k;
		}
		int base = 110000;	//the "0" of our dp array
		long[][] dp = new long[n][base * 2];
		dp[0][base + fruits[0][0] - fruits[0][1]] = fruits[0][0];
		for(int i = 1; i < n; i++) {
			long diff = fruits[i][0] - fruits[i][1];
			for(int j = 0; j < dp[i].length; j++) {
				if(dp[i - 1][j] != 0 || j == base) {
					int index = j + (int) diff;
					long val = dp[i - 1][j] + fruits[i][0];
					if(index >= 0 && index < base * 2) {
						dp[i][index] = Math.max(dp[i - 1][index], val);
						//System.out.println("value replaced");
					}
					//System.out.println("replacing vaue " + index + " " + val + " " + dp[i][index]);
				}
			}
			for(int j = 0; j < dp[i].length; j++) {
				dp[i][j] = Math.max(dp[i - 1][j], dp[i][j]);
			}
		}
		System.out.println(dp[n - 1][base] == 0? "-1" : (dp[n - 1][base] + ""));
	}
}
