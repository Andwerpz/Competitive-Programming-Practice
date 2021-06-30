//package solvethemaze;

import java.util.*;
import java.io.*;

public class solvethemaze {
	public static void main(String[] args) throws IOException {
		
		//1365D
		
		//surround each enemy inside walls, and then check whether you can reach all of the good guys from the exit. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		int counter = 0;
		while(t-- > 0) {
			counter ++;
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());
			int[][] board = new int[n][m];
			ArrayList<int[]> enemies = new ArrayList<int[]>();
			ArrayList<int[]> good = new ArrayList<int[]>();
			for(int i = 0; i < n; i++) {
				char[] input = fin.readLine().toCharArray();
				for(int j = 0; j < m; j++) {
					char next = input[j];
					if(next == 'B') {
						enemies.add(new int[] {i, j});
						board[i][j] = 2;
					}
					else if(next == 'G') {
						good.add(new int[] {i, j});
						board[i][j] = 1;
					}
					else if(next == '#') {
						board[i][j] = -1;
					}
					else {
						board[i][j] = 0;
					}
				}
			}
			boolean isValid = true;
			int[] dx = new int[] {1, -1, 0, 0};
			int[] dy = new int[] {0, 0, 1, -1};
			outer:
			for(int i = 0; i < enemies.size(); i++) {
				int[] cur = enemies.get(i);
				for(int j = 0; j < 4; j++) {
					int x = cur[0] + dx[j];
					int y = cur[1] + dy[j];
					if(x >= 0 && x < n && y >= 0 && y < m) {
						//System.out.println(x + " " + y);
						if(board[x][y] == 1) {
							isValid = false;
							break outer;
						}
						else if(board[x][y] != 2) {
							board[x][y] = -1;
						}
					}
				}
			}
			int[][] v = new int[n][m];
			//System.out.println(isValid);
			int pointer = 1;
			for(int i = 0; i < good.size(); i++) {
				int[] cur = good.get(i);
				boolean curValid = true;
				if(v[cur[0]][cur[1]] == 0) {
					pointer ++;
					curValid = false;
					Queue<Integer> x = new ArrayDeque<Integer>();
					Queue<Integer> y = new ArrayDeque<Integer>();
					v[cur[0]][cur[1]] = pointer;
					x.add(cur[0]);
					y.add(cur[1]);
					outer:
					while(x.size() != 0) {
						//System.out.println("ES");
						int curX = x.poll();
						int curY = y.poll();
						if(curX == n - 1 && curY == m - 1) {
							curValid = true;
							break;
						}
						for(int j = 0; j < 4; j++) {
							int nextX = curX + dx[j];
							int nextY = curY + dy[j];
							if(nextX >= 0 && nextX < n && nextY >= 0 && nextY < m) {
								if((board[nextX][nextY] == 1 || board[nextX][nextY] == 0) && v[nextX][nextY] == 0) {
									//System.out.println("NEXT");
									v[nextX][nextY] = pointer;
									x.add(nextX);
									y.add(nextY);
								}
								if(v[nextX][nextY] < pointer && v[nextX][nextY] != 0 && board[nextX][nextY] != -1) {
									curValid = true;
									break outer;
								}
							}
						}
					}
				}
				isValid &= curValid;
			}
			fout.append(isValid? "YES\n" : "NO\n");
		}
		System.out.print(fout);
	}
}
