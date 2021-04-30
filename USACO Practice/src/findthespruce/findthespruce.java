//package findthespruce;

import java.util.*;
import java.io.*;

public class findthespruce {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());
			char[][] s = new char[n][m];
			for(int i = 0; i < n; i++) {
				s[i] = fin.readLine().toCharArray();
			}
			int curSize = n;
			while(curSize * 2 - 1 > m) {
				curSize --;
			}
			int[][] dp = new int[n][m];	//stores the size of tree that is guaranteed by previous searches starting at that location
			int ans = 0;
			for(int i = 0; i < n; i++) {
				for(int j = 0; j < m; j++) {
					if(s[i][j] == '*') {
						int l = j;
						int r = j;
						int row = i;
						for(int k = 0; k < dp[i][j]; k++) {	//going through guaranteed trees
							row ++;
							r ++;
							l --;
							ans ++;
						}
						while(l >= 0 && r < m && row < n) {
							boolean isValid = true;
							for(int k = l; k <= r; k++) {
								if(s[row][k] != '*') {
									isValid = false;
									break;
								}
							}
							if(isValid) {
								ans ++;
								l --;
								r ++;
								row ++;
							}
							else {
								break;
							}
						}
						int temp = row;
						row --;
						l ++;
						r --;
						while(l != r && l < r) {
							for(int k = l; k <= r; k++) {
								dp[row][k] = Math.max(temp - row, dp[row][k]);
							}
							row --;
							l ++;
							r --;
						}
					}
				}
			}
			
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
