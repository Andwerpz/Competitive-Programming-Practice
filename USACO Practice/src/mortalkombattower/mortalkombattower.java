//package mortalkombattower;

import java.util.*;
import java.io.*;

public class mortalkombattower {
	public static void main(String[] args) throws IOException {
		
		//1418C
		
		//there is a simple dp solution. For every position on the tower, find the minimum way to get to it ending on your move, and your friends move. 
		//for your move, you can just take the minimum of your friends previous or previous-previous move, since you don't need to use skip tokens. For your friend though,
		//he needs to look at 1 or two moves back, and also add 1 if there is a hard boss. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int[] bosses = new int[n];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				bosses[i] = Integer.parseInt(st.nextToken());
			}
			if(n > 3) {
				int[][] dp = new int[2][n];	//0 - friend, 1 - you
				Arrays.fill(dp[0], -1);
				Arrays.fill(dp[1], -1);
				dp[0][0] = bosses[0] == 1? 1 : 0;
				dp[0][1] = (bosses[1] == 1? 1 : 0) + dp[0][0];
				dp[1][1] = dp[0][0];
				dp[0][2] = dp[1][1] + (bosses[2] == 1? 1 : 0);
				dp[1][2] = Math.min(dp[0][1], dp[0][0]);
				for(int i = 3; i < n; i++) {
					dp[1][i] = Math.min(dp[0][i - 1], dp[0][i - 2]);
					dp[0][i] = Math.min((bosses[i] == 1? 1 : 0) + dp[1][i - 1], (bosses[i] == 1? 1 : 0) + (bosses[i - 1] == 1? 1 : 0) + dp[1][i - 2]);
				}
				fout.append(Math.min(dp[0][n - 1], dp[1][n - 1])).append("\n");
//				for(int [] i : dp) {
//					for(int j : i) {
//						System.out.print(j + " ");
//					}
//					System.out.println();
//				}
//				System.out.println();
			}
			else {
				fout.append(bosses[0]).append("\n");
			}
		}
		System.out.print(fout);
	}
}
