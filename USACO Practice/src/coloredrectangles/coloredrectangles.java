//package coloredrectangles;

import java.util.*;
import java.io.*;

public class coloredrectangles {
	
	static long[][][] dp;
	
	public static void main(String[] args) throws IOException {
		
		//1398D
		
		//this is a classic example of a brute force dp problem. Since we know that the answer must consist of a prefix of all colored segments largest segments, 
		//we can just construct a dp array that tests all possible combinations of prefixes.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int r = Integer.parseInt(st.nextToken());
		int g = Integer.parseInt(st.nextToken());
		int b = Integer.parseInt(st.nextToken());
		Integer[] rNums = new Integer[r];
		Integer[] gNums = new Integer[g];
		Integer[] bNums = new Integer[b];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < r; i++) {
			rNums[i] = Integer.parseInt(st.nextToken());
		}
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < g; i++) {
			gNums[i] = Integer.parseInt(st.nextToken());
		}
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < b; i++) {
			bNums[i] = Integer.parseInt(st.nextToken());
		}
		Arrays.sort(rNums, (a, c) -> -(a - c));
		Arrays.sort(gNums, (a, c) -> -(a - c));
		Arrays.sort(bNums, (a, c) -> -(a - c));
		dp = new long[r + 1][g + 1][b + 1];
		long ans = 0;
		for(int i = 0; i < r + 1; i++) {
			for(int j = 0; j < g + 1; j++) {
				for(int k = 0; k < b + 1; k++) {
					long cur = dp[i][j][k];
					//System.out.println(cur);
					if(i + 1 <= r && j + 1 <= g) {
						dp[i + 1][j + 1][k] = Math.max(dp[i + 1][j + 1][k], cur + rNums[i] * gNums[j]);
					}
					if(j + 1 <= g && k + 1 <= b) {
						dp[i][j + 1][k + 1] = Math.max(dp[i][j + 1][k + 1], cur + gNums[j] * bNums[k]);
					}
					if(k + 1 <= b && i + 1 <= r) {
						dp[i + 1][j][k + 1] = Math.max(dp[i + 1][j][k + 1], cur + bNums[k] * rNums[i]);
					}
					ans = Math.max(ans, cur);
				}
			}
		}
		System.out.println(ans);
	}
}
