//package grid00100;

import java.util.*;
import java.io.*;

public class grid00100 {
	public static void main(String[] args) throws IOException {
		
		//1371D
		
		//it is best to first make all the rows and columns have 1 item, before starting to make them have two items. This reduces the f(x) value to a minimum of 2. You can do this
		//by first filling up one diagonal and once it's completely filled in, moving on to the next diag. To do the next diag, just increase the x offset by 1, and increase the y just like
		//the previous diag. When x exceeds n, then just take the mod of x. If k % n == 0, then the function value is 0, else the function value is 2. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int k = Integer.parseInt(st.nextToken());
			int[][] g = new int[n][n];
			fout.append(k % n == 0? "0\n" : "2\n");
			int x = 0;
			int y = 0;
			int xOffset = 0;
			while(k != 0) {
				g[x % n][y % n] = 1;
				k --;
				x ++;
				y ++;
				if(y == n) {
					xOffset ++;
					x = xOffset;
					y = 0;
				}
			}
			for(int i = 0; i < n; i++) {
				for(int j = 0; j < n; j++) {
					fout.append(g[i][j]);
				}
				fout.append("\n");
			}
		}
		System.out.print(fout);
	}
}
