package spacewalk;

import java.util.*;
import java.io.*;

public class spacewalk {
	public static void main(String[] args) throws IOException {
		
		//2021 Keep Austin Hacking
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int y1 = Integer.parseInt(st.nextToken()) - 1;
		int x1 = Integer.parseInt(st.nextToken()) - 1;
		int y2 = Integer.parseInt(st.nextToken()) - 1;
		int x2 = Integer.parseInt(st.nextToken()) - 1;
		int n = Integer.parseInt(st.nextToken());
		int[][] grid = new int[n][n];
		for(int i = 0; i < n; i++) {
			st = new StringTokenizer(fin.readLine());
			for(int j = 0; j < n; j++) {
				grid[i][j] = Integer.parseInt(st.nextToken());
			}
		}
		PriorityQueue<int[]> q = new PriorityQueue<int[]>((a, b) -> a[0] - b[0]);
		boolean[][] v = new boolean[n][n];
		v[x1][y1] = true;
		q.add(new int[] {0, x1, y1});
		int[] dx = new int[] {1, -1, 0, 0};
		int[] dy = new int[] {0, 0, 1, -1};
		int ans = 0;
		while(q.size() != 0) {
			int[] cur = q.poll();
			int curX = cur[1];
			int curY = cur[2];
			int curCost = cur[0];
			if(curX == x2 && curY == y2) {
				ans = curCost;
			}
			for(int i = 0; i < 4; i++) {
				int nextX = curX + dx[i];
				int nextY = curY + dy[i];
				if(nextX >= 0 && nextX < n && nextY >= 0 && nextY < n && !v[nextX][nextY]) {
					v[nextX][nextY] = true;
					q.add(new int[] {curCost + grid[nextX][nextY], nextX, nextY});
				}
			}
		}
		System.out.println(ans);
	}
}
