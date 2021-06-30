package asteroidbelt;

import java.util.*;
import java.io.*;

public class asteroidbelt {
	public static void main(String[] args) throws IOException {
		
		//2021 Keep Austin Hacking
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		int[][] grid = new int[n][3];
		for(int i = 0; i < n; i++) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			grid[i] = new int[] {Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken())};
		}
		boolean[][] v = new boolean[n][3];
		v[0][0] = true;
		Stack<Integer> x = new Stack<Integer>();
		Stack<Integer> y = new Stack<Integer>();
		x.push(0);
		y.push(0);
		int[] dx = new int[] {1, -1, 0, 0};
		int[] dy = new int[] {0, 0, 1, -1};
		boolean isValid = false;
		while(x.size() != 0) {
			int curX = x.pop();
			int curY = y.pop();
			if(curX == n - 1 && curY == 2) {
				isValid = true;
				break;
			}
			for(int i = 0; i < 4; i++) {
				int nextX = curX + dx[i];
				int nextY = curY + dy[i];
				if(nextX >= 0 && nextX < n && nextY >= 0 && nextY < 3 && !v[nextX][nextY] && grid[nextX][nextY] == 0) {
					v[nextX][nextY] = true;
					x.push(nextX);
					y.push(nextY);
				}
			}
		}
		System.out.println(isValid? "YES" : "NO");
	}
}
