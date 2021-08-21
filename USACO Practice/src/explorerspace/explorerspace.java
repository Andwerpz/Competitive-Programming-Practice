//package explorerspace;

import java.util.*;
import java.io.*;

public class explorerspace {
	
	static ArrayList<ArrayList<int[]>> c;
	static int[][] dp;
	
	public static int getMin(int a, int k) {
		if(dp[a][k] != -1) {
			return dp[a][k];
		}
		if(k == 0) {
			dp[a][k] = 0;
			return 0;
		}
		int ans = Integer.MAX_VALUE;
		for(int i = 0; i < c.get(a).size(); i++) {
			ans = Math.min(ans, getMin(c.get(a).get(i)[0], k - 1) + c.get(a).get(i)[1]);
		}
		dp[a][k] = ans;
		return ans;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1517D
		
		//first, if the starting value of k is odd, then you won't be able to find a path back to the starting node.
		//next, it is always optimal to find the minimum path length of k / 2 and just backtrack along it to make a total path length of k.
		
		//to do this, you can do a search for each grid cell to find the shortest path length for that particular cell, but then you find that the complexity is near O(n * m * 2^k). Not good
		//notice that alot of the subproblems for adjacent grid cells overlap. We can just use dp to solve a total of n * m * k subproblems, which is good enough.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		c = new ArrayList<ArrayList<int[]>>();
		for(int i = 0; i < n * m; i++) {
			c.add(new ArrayList<int[]>());
		}
		for(int i = 0; i < n; i++) {
			st = new StringTokenizer(fin.readLine());
			for(int j = 0; j < m - 1; j++) {
				int cost = Integer.parseInt(st.nextToken());
				int a = i * m + j;
				int b = a + 1;
				c.get(a).add(new int[] {b, cost});
				c.get(b).add(new int[] {a, cost});
			}
		}
		for(int i = 0; i < n - 1; i++) {
			st = new StringTokenizer(fin.readLine());
			for(int j = 0; j < m; j++) {
				int cost = Integer.parseInt(st.nextToken());
				int a = i * m + j;
				int b = a + m;
				c.get(a).add(new int[] {b, cost});
				c.get(b).add(new int[] {a, cost});
			}
		}
		StringBuilder fout = new StringBuilder();
		dp = new int[n * m][k / 2 + 1];
		for(int i = 0; i < n * m; i++) {
			Arrays.fill(dp[i], -1);
		}
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				if(k % 2 == 1) {
					fout.append("-1 ");
				}
				else {
					fout.append(getMin((i * m) + j, (k / 2)) * 2).append(" ");
				}
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
