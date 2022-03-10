//package vitalyandadvanceduselessalgorithms;

import java.util.*;
import java.io.*;

public class vitalyandadvanceduselessalgorithms {
	public static void main(String[] args) throws IOException {
		
		//1650F
		
		//notice that the possible range of values for the percentage are 0 - 100. 
		//also notice that all the tasks that vitaly needs to complete are independent from eachother. 
		
		//to solve, you can just do 0-1 knapsack dp for every task. dp[i] is the minimum number of hours
		//to get to i percent.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());
			int[] nums = new int[n];
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			ArrayList<ArrayList<int[]>> train = new ArrayList<ArrayList<int[]>>();
			for(int i = 0; i < n; i++) {
				train.add(new ArrayList<int[]>());
			}
			for(int i = 0; i < m; i++) {
				st = new StringTokenizer(fin.readLine());
				int e = Integer.parseInt(st.nextToken()) - 1;
				int ti = Integer.parseInt(st.nextToken());
				int p = Integer.parseInt(st.nextToken());
				train.get(e).add(new int[] {ti, p, i + 1});	//time spent, percentage gained, original index
			}
//			for(ArrayList<int[]> i : train) {
//				for(int[] j : i) {
//					System.out.println(j[0] + " " + j[1] + " " + j[2]);
//				}
//				System.out.println();
//			}
//			System.out.println();
			int timeSpent = 0;
			boolean isValid = true;
			ArrayList<Integer> ans = new ArrayList<Integer>();
			for(int i = 0; i < n; i++) {
				long[][] dp = new long[train.get(i).size() + 1][101];
				int[][] back = new int[train.get(i).size() + 1][101];	//which percentage point did this op come from
				Arrays.fill(dp[0], Long.MAX_VALUE / 2);
				dp[0][0] = 0;
				for(int j = 0; j < train.get(i).size(); j++) {
					//System.out.println(i + " " + j + " " + n);
					int ti = train.get(i).get(j)[0];
					int p = train.get(i).get(j)[1];
					Arrays.fill(back[j + 1], -1);
					Arrays.fill(dp[j + 1], Long.MAX_VALUE / 2);
					for(int k = 0; k < 101; k++) {
						dp[j + 1][k] = Math.min(dp[j + 1][k], dp[j][k]);
						int nextIndex = Math.min(p + k, 100);
						long nextTime = dp[j][k] + ti;
						if(dp[j + 1][nextIndex] > nextTime) {
							back[j + 1][nextIndex] = k;
							dp[j + 1][nextIndex] = nextTime;
						}
					}
				}
//				for(long[] j : dp) {
//					for(long k : j) {
//						System.out.print((k == Long.MAX_VALUE / 2? -1 : k) + " ");
//					}
//					System.out.println();
//				}
				//System.out.println();
				if(dp[train.get(i).size()][100] + timeSpent > nums[i]) {
					isValid = false;
					break;
				}
				timeSpent += dp[train.get(i).size()][100];
				int curPercent = 100;
				for(int j = train.get(i).size() - 1; j >= 0; j--) {
					if(back[j + 1][curPercent] != -1 && dp[j][curPercent] > dp[j + 1][curPercent]) {
						ans.add(train.get(i).get(j)[2]);
						curPercent = back[j + 1][curPercent];
						if(curPercent <= 0) {
							break;
						}
					}
				}
			}
			if(!isValid) {
				fout.append("-1\n");
				continue;
			}
			fout.append(ans.size()).append("\n");
			for(int i : ans) {
				fout.append(i).append(" ");
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
