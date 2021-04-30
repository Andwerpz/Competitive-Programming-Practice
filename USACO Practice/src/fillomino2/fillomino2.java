//package fillomino2;

import java.util.*;
import java.io.*;

public class fillomino2 {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		int[][] g = new int[n][n];
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			g[i][i] = Integer.parseInt(st.nextToken());
		}
		for(int i = 0; i < n - 1; i++) {
			for(int j = i + 1; j < n; j++) {
				g[i][j] = -1;
			}
		}
		boolean isValid = true;
		for(int i = 0; i < n; i++) {
			int cur = g[i][i];
			int numLeft = cur - 1;
			int x = i;
			int y = i;
			while(numLeft > 0) {
				if(y - 1 >= 0 && g[x][y - 1] == 0) {
					g[x][y - 1] = cur;
					y--;
				}
				else if(x + 1 < n && g[x + 1][y] == 0) {
					g[x + 1][y] = cur;
					x++;
				}
				else {
					isValid = false;
					break;
				}
				numLeft --;
			}
			if(!isValid) {
				break;
			}
		}
		StringBuilder fout = new StringBuilder();
		if(isValid) {
			for(int i = 0; i < n; i++) {
				for(int j = 0; j < n; j++) {
					if(g[i][j] != -1) {
						fout.append(g[i][j]).append(" ");
					}
				}
				fout.append("\n");
			}
			System.out.print(fout);
		}
		else {
			System.out.println(-1);			
		}
	}
}
