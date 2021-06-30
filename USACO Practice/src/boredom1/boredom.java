package boredom1;

import java.util.*;
import java.io.*;

public class boredom {
	public static void main(String[] args) throws IOException {
		
		//2021 Keep Austin Hacking
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		long mod = 1000000007;
		long[][] grid = new long[n][m];
		grid[0][0] = 1;
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				if(i != n - 1) {
					grid[i + 1][j] += grid[i][j];
					grid[i + 1][j] %= mod;
				}
				if(j != m - 1) {
					grid[i][j + 1] += grid[i][j];
					grid[i][j + 1] %= mod;
				}
			}
		}
		System.out.println(grid[n - 1][m - 1]);
	}
}
