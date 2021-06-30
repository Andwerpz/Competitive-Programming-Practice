//package colourtheflag;

import java.util.*;
import java.awt.Point;
import java.io.*;

public class colourtheflag {
	public static void main(String[] args) throws IOException {
		
		//1534A
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());
			char[][] grid = new char[n][m];
			for(int i = 0; i < n; i++) {
				grid[i] = fin.readLine().toCharArray();
			}
			Point c = new Point(0, 0);
			char which = 'R';
			outer:
			for(int i = 0; i < n; i++) {
				for(int j = 0; j < m; j++) {
					if(grid[i][j] != '.') {
						which = grid[i][j];
						c.x = i;
						c.y = j;
						break outer;
					}
				}
			}
			
			boolean isValid = true;
			Stack<Point> s = new Stack<Point>();
			Stack<Character> color = new Stack<Character>();
			grid[c.x][c.y] = which;
			which = (which == 'R'? 'W' : 'R');
			s.add(c);
			color.add(which);
			int[] dx = new int[] {1, -1, 0, 0};
			int[] dy = new int[] {0, 0, 1, -1};
			boolean[][] v = new boolean[n][m];
			v[c.x][c.y] = true;
			outer:
			while(s.size() != 0) {
				Point cur = s.pop();
				char curColor = color.pop();
				for(int i = 0; i < 4; i++) {
					int x = cur.x + dx[i];
					int y = cur.y + dy[i];
					if(x >= 0 && x < n && y >= 0 && y < m) {
						if(grid[x][y] == '.' || grid[x][y] == curColor) {
							if(!v[x][y]) {
								grid[x][y] = curColor;
								v[x][y] = true;
								s.add(new Point(x, y));
								color.add(curColor == 'R'? 'W' : 'R');
							}
						}
						else {
							isValid = false;
							break outer;
						}
					}
				}
			}
			if(isValid) {
				fout.append("YES\n");
				for(int i = 0; i < n; i++) {
					fout.append(String.valueOf(grid[i])).append("\n");
				}
			}
			else {
				fout.append("NO\n");
			}
		}
		System.out.print(fout);
	}
}
