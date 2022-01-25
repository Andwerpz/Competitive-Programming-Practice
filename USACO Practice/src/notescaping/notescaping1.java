//package notescaping;

import java.util.*;
import java.io.*;

public class notescaping1 {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());
			int k = Integer.parseInt(st.nextToken());
			int[] floorCost = new int[n];
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				floorCost[i] = Integer.parseInt(st.nextToken());
			}
			ArrayList<ArrayList<int[]>> ladders = new ArrayList<ArrayList<int[]>>();
			for(int i = 0; i < n; i++) {
				ladders.add(new ArrayList<int[]>());
			}
			for(int i = 0; i < k; i++) {
				st = new StringTokenizer(fin.readLine());
				int[] next = new int[5];
				for(int j = 0; j < 5; j++) {
					next[j] = Integer.parseInt(st.nextToken());
					if(j < 4) {
						next[j] --;
					}
				}
				ladders.get(next[0]).add(next);
			}
			int[][] dp = new int[n][m];
			boolean[][] v = new boolean[n][m];
			//calculate costs of first floor
			for(int i = 1; i < m; i++) {
				dp[0][i] = floorCost[0] * i;
			}
			//first floor ladders
			for(int[] l : ladders.get(0)) {
				int nextVal = dp[l[0]][l[1]] - l[4];
				int c = l[2];
				int d = l[3];
				if(!v[c][d]) {
					dp[c][d] = nextVal;
					v[c][d] = true;
				}
				dp[c][d] = Math.min(dp[c][d], nextVal);
			}
			for(int i = 1; i < n - 1; i++) {
				//check if this floor is possible
				boolean thisFloorPossible = false;
				for(int j = 0; j < m; j++) {
					if(v[i][j]) {
						thisFloorPossible = true;
						break;
					}
				}
				if(!thisFloorPossible) {
					continue;
				}
				for(int j = 0; j < m; j++) {
					if(!v[i][j]) {
						dp[i][j] = Integer.MAX_VALUE;
					}
				}
				//left to right sweep first
				int val = 0;
				boolean found = false;
				for(int j = 0; j < m; j++) {
					if(v[i][j]) {
						if(!found) {
							val = dp[i][j];
						}
						found = true;
						val = Math.min(val, dp[i][j]);
					}
					if(found) {
						dp[i][j] = Math.min(val, dp[i][j]);
						val += floorCost[i];
					}
				}
				//right to left sweep
				val = 0;
				found = false;
				for(int j = m - 1; j >= 0; j--) {
					if(v[i][j]) {
						if(!found) {
							val = dp[i][j];
						}
						found = true;
						val = Math.min(val, dp[i][j]);
					}
					if(found) {
						dp[i][j] = Math.min(val, dp[i][j]);
						val += floorCost[i];
					}
				}
				//ladders
				for(int[] l : ladders.get(i)) {
					int nextVal = dp[l[0]][l[1]] - l[4];
					int c = l[2];
					int d = l[3];
					if(!v[c][d]) {
						dp[c][d] = nextVal;
						v[c][d] = true;
					}
					dp[c][d] = Math.min(dp[c][d], nextVal);
				}
			}
			//check if last floor is visited
			boolean thisFloorPossible = false;
			for(int j = 0; j < m; j++) {
				if(v[n - 1][j]) {
					thisFloorPossible = true;
					break;
				}
			}
			if(!thisFloorPossible) {
				fout.append("NO ESCAPE\n");
				continue;
			}
			//process last floor. Only left to right sweep is needed
			for(int j = 0; j < m; j++) {
				if(!v[n - 1][j]) {
					dp[n - 1][j] = Integer.MAX_VALUE;
				}
			}
			int val = 0;
			boolean found = false;
			for(int j = 0; j < m; j++) {
				if(v[n - 1][j]) {
					if(!found) {
						val = dp[n - 1][j];
					}
					found = true;
					val = Math.min(val, dp[n - 1][j]);
				}
				if(found) {
					dp[n - 1][j] = Math.min(val, dp[n - 1][j]);
					val += floorCost[n - 1];
				}
			}
			fout.append(dp[n - 1][m - 1]).append("\n");
			
//			for(int i = n - 1; i >= 0; i--) {
//				int[] next = dp[i];
//				for(int j : next) {
//					System.out.print(j + " ");
//				}
//				System.out.println();
//			}
//			System.out.println();
//			for(int i = n - 1; i >= 0; i--) {
//				boolean[] next = v[i];
//				for(boolean j : next) {
//					System.out.print((j? 1 : 0) + " ");
//				}
//				System.out.println();
//			}
		}
		System.out.print(fout);
	}
}
