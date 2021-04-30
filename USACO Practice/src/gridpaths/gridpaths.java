//package gridpaths;

import java.util.*;
import java.io.*;

public class gridpaths {
	public static void main(String[] args) throws IOException {
		
		//for each grid cell, we compute how many paths there are to get to this cell. 
		//to do this, we start from the top left cell with a value of one, and add to each cell to the right and bottom, the stored value in
		//that cell. Repeat for all cells.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		int n = Integer.parseInt(fin.readLine());
		char[][] grid = new char[n][n];
		for(int i = 0; i < n; i++) {
			grid[i] = fin.readLine().toCharArray();
		}
		int[][] dp = new int[n][n];
		int mod = 1000000007;
		dp[0][0] = grid[0][0] == '.'? 1 : 0;
		for(int i = 0; i < dp.length; i++) {
			for(int j = 0; j < dp.length; j++) {
				if(grid[i][j] == '.') {
					if(i + 1 != dp.length && grid[i + 1][j] == '.') {
						dp[i + 1][j] += dp[i][j];
						dp[i + 1][j] %= mod;
					}
					if(j + 1 != dp.length && grid[i][j + 1] == '.') {
						dp[i][j + 1] += dp[i][j];
						dp[i][j + 1] %= mod;
					}
				}
				
			}
		}
		System.out.println(dp[n - 1][n - 1]);
	}
}
