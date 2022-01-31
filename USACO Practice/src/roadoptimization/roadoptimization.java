//package roadoptimization;

import java.util.*;
import java.io.*;

public class roadoptimization {
	public static void main(String[] args) throws IOException {
		
		//1625C
		
		//haha get worked around
		//instead of making one big dp array, we can just store 2 layers at a time. 
		//since we optimize one layer before moving onto the next, we can do this.
		
		//dp with three states, which sign we are currently at, how many signs we have skipped, how many have we currently skipped in a row.
		
		//first two are pretty obvious why. The third one is because we need to know at which speed we are travelling currently. 
		//we can't just store the speed as a dp state, since speed values are from 1 - 10^4. 500 ^ 2 * 10^4 is way too much. 
		
		//advancing dp states:	we can do one of two actions at each sign, skip it, or don't skip it
		//dp[i + 1][j][0] = dp[i][j][k] + timeToNextSign; 			we are not skipping the next sign
		//dp[i + 1][j + 1][k + 1] = dp[i][j][k] + timeToNextSign	we are skipping the next sign
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int l = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		int[][] dp = new int[k + 1][k + 1]; 	//which sign, how many skipped so far, how many skipped in a row
		int[][] signs = new int[n + 1][2];	//location, speed
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			signs[i][0] = Integer.parseInt(st.nextToken());
		}
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			signs[i][1] = Integer.parseInt(st.nextToken());
		}
		signs[n][0] = l;
		signs[n][1] = 0;
		Arrays.sort(signs, (a, b) -> Integer.compare(a[0], b[0]));
		for(int i = 0; i < k + 1; i++) {
			for(int j = 0; j < k + 1; j++) {
				dp[i][j] = -1;
			}
		}
		dp[0][0] = 0;
		for(int i = 0; i < n; i++) {
			int distToNext = signs[i + 1][0] - signs[i][0];
			int[][] temp = new int[k + 1][k + 1];
			for(int j = 0; j < k + 1; j++) {
				for(int m = 0; m < k + 1; m++) {
					if(dp[j][m] != -1) {
						int curSpeed = signs[i - m][1];
						int curTime = dp[j][m];
						//System.out.println(curSpeed + " " + curTime + " " + distToNext);
						temp[j][0] = temp[j][0] == 0? curTime + distToNext * curSpeed : Math.min(temp[j][0], curTime + distToNext * curSpeed);
						//System.out.println("NEXT: " + dp[i + 1][j][0]);
						if(j != k) {
							temp[j + 1][m + 1] = temp[j + 1][m + 1] == 0? curTime + distToNext * curSpeed : Math.min(temp[j + 1][m + 1], curTime + distToNext * curSpeed);
						}
					}
					//System.out.print(dp[i][j][m] + " ");
				}
				//System.out.println();
			}
			//System.out.println();
			for(int j = 0; j < k + 1; j++) {
				for(int m = 0; m < k + 1; m++) {
					dp[j][m] = temp[j][m] == 0? -1 : temp[j][m];
				}
			}
		}
		for(int [] j : dp) {
			for(int m : j) {
				//System.out.print(m + " ");
			}
			//System.out.println();
		}
		int ans = Integer.MAX_VALUE;
		for(int i = 0; i < k + 1; i++) {
			for(int j = 0; j < k + 1; j++) {
				if(dp[i][j] != -1) {
					//System.out.println(dp[n][i][j]);
					ans = Math.min(ans, dp[i][j]);
				}
			}
		}
		System.out.println(ans);
	}
}
