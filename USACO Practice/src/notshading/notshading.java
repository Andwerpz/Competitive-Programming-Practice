//package notshading;

import java.util.*;
import java.io.*;

public class notshading {
	public static void main(String[] args) throws IOException {
		
		//1627A
		
		//unless there is no black tile on the board, you can always color the target tile black. 
		
		//if the target is black, no moves required. 
		//if a tile that shares a row or column with the target is black, then 1 move is required
		//if none of the above, then max 2 moves are required. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());
			int r = Integer.parseInt(st.nextToken()) - 1;
			int c = Integer.parseInt(st.nextToken()) - 1;
			char[][] grid = new char[n][m];
			boolean found = false;
			boolean foundRC = false;
			for(int i = 0; i < n; i++) {
				String line = fin.readLine();
				for(int j = 0; j < m; j++) {
					grid[i][j] = line.charAt(j);
					if(grid[i][j] == 'B') {
						found = true;
						if(i == r || j == c) {
							foundRC = true;
						}
					}
				}
			}
			if(!found) {
				fout.append("-1\n");
				continue;
			}
			else if(grid[r][c] == 'B') {
				fout.append("0\n");
				continue;
			}
			else if(foundRC) {
				fout.append("1\n");
				continue;
			}
			fout.append("2\n");
		}
		System.out.print(fout);
	}
}
