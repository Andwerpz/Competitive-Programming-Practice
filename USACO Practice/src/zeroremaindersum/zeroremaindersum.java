package zeroremaindersum;

import java.util.*;
import java.io.*;

public class zeroremaindersum {
	public static void main(String[] args) throws IOException {
		
		//1433F
		
		//this is an interesting dp problem. I've never seen anything above 3 states before.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		int[][] nums = new int[n][m];
		for(int i = 0; i < n; i++) {
			st = new StringTokenizer(fin.readLine());
			for(int j = 0; j < m; j++) {
				nums[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		int[][][][] dp = new int[75][75][75][75];	//maximum value for each: x, y, num selected on current row, remainder
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				for(int l = 0; l < m / 2; l++) {
					Arrays.fill(dp[i][j][l], -1);
				}
			}
		}
		dp[0][0][0][0] = 0;
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				for(int cnt = 0; cnt < m / 2; cnt++) {
					for(int rem = 0; rem < k; rem ++) {
						if(dp[i][j][cnt][rem] == -1) {
							continue;
						}
						int ni = (j == m - 1 ? i + 1 : i);
						int nj = (j == m - 1 ? 0 : j + 1);
						if(i != ni) {
							dp[ni][nj][0][rem] = Math.max(dp[ni][nj][0][rem], dp[i][j][cnt][rem]);
						} 
						else {
							dp[ni][nj][cnt][rem] = Math.max(dp[ni][nj][cnt][rem], dp[i][j][cnt][rem]);
						}
						if (cnt + 1 <= m / 2) {
							int nrem = (rem + nums[i][j]) % k;
							if (i != ni) {
								dp[ni][nj][0][nrem] = Math.max(dp[ni][nj][0][nrem], dp[i][j][cnt][rem] + nums[i][j]);
							} else {
								dp[ni][nj][cnt + 1][nrem] = Math.max(dp[ni][nj][cnt + 1][nrem], dp[i][j][cnt][rem] + nums[i][j]);
							}
						}
					}
				}
			}
		}
		System.out.println(Math.max(0, dp[n][0][0][0]));
	}
}
