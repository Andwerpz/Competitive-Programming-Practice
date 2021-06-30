//package lakesinberland;

import java.util.*;
import java.io.*;

public class lakesinberland {
	public static void main(String[] args) throws IOException {
		
		//you start out with k or greater lakes, and the goal is to reduce the number of lakes to exactly k. All you need to do is get rid of the smallest lakes, until 
		//you have k lakes.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		HashSet<Integer> lakes = new HashSet<Integer>();
		ArrayList<int[]> sizes = new ArrayList<int[]>();
		int[][] g = new int[n][m];
		for(int i = 0; i < n; i++) {
			String input = fin.readLine();
			for(int j = 0; j < m; j++) {
				char next = input.charAt(j);
				g[i][j] = (next == '*')? 0 : -1;
			}
		}
		int[] xDiff = new int[] {0, 0, 1, -1};
		int[] yDiff = new int[] {1, -1, 0, 0};
		int pointer = 0;
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				if(g[i][j] == -1) {
					//System.out.println("LAKE DETECTED: " + i + " " + j);
					pointer ++;
					Stack<ArrayList<Integer>> s = new Stack<ArrayList<Integer>>();
					HashSet<ArrayList<Integer>> v = new HashSet<ArrayList<Integer>>();
					ArrayList<Integer> first = new ArrayList<Integer>(Arrays.asList(i, j));
					s.add(first);
					v.add(first);
					boolean isOcean = false;
					int size = 0;
					while(s.size() != 0) {
						size ++;
						ArrayList<Integer> next = s.pop();
						int x = next.get(0);
						int y = next.get(1);
						g[x][y] = pointer;
						if(x + 1 == n || x - 1 == -1 || y + 1 == m || y - 1 == -1) {
							isOcean = true;
						}
						for(int u = 0; u < 4; u++) {
							int[] cur = new int[] {x + xDiff[u], y + yDiff[u]};
							if(cur[0] != -1 && cur[0] != n && cur[1] != m && cur[1] != -1 && g[cur[0]][cur[1]] == -1 && !v.contains(new ArrayList<Integer>(Arrays.asList(cur[0], cur[1])))) {
								ArrayList<Integer> newArray = new ArrayList<Integer>(Arrays.asList(cur[0], cur[1]));
								s.add(newArray);
								v.add(newArray);
							}
						}
					}
					if(!isOcean) {
						lakes.add(pointer);
						sizes.add(new int[] {size, pointer});
					}
				}
			}
		}
		int removeNum = lakes.size() - k;
//		for(int[] i : g) {
//			for(int j : i) {
//				System.out.print(j + " ");
//			}
//			System.out.println();
//		}
		//System.out.println("NUM LAKES: " + lakes.size());
		sizes.sort((a, b) -> a[0] - b[0]);
//		for(int[] i : sizes) {
//			System.out.print(i[1] + " ");
//		}
//		System.out.println();
		int cost = 0;
		HashSet<Integer> remove = new HashSet<Integer>();
		for(int i = 0; i < removeNum; i++) {
			cost += sizes.get(i)[0];
			remove.add(sizes.get(i)[1]);
		}
		StringBuilder fout = new StringBuilder();
		fout.append(cost).append("\n");
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				if(g[i][j] == 0) {
					fout.append("*");
				}
				else if(remove.contains(g[i][j])) {
					fout.append("*");
				}
				else {
					fout.append(".");
				}
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
