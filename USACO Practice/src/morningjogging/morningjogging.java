//package morningjogging;

import java.util.*;
import java.io.*;

public class morningjogging {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t -- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());
			int[][] paths = new int[n][m];
			int[][] sorted = new int[n * m][2];	//ordering the paths in order so that we can match each runner up to a min cost path
			int[][] runners = new int[m][n];
			for(int i = 0; i < n; i++) {
				st = new StringTokenizer(fin.readLine());
				for(int j = 0; j < m; j++) {
					//System.out.println(i * (n + 1) + j + " " + i + " " + j);
					paths[i][j] = Integer.parseInt(st.nextToken());
					sorted[i * m + j][0] = paths[i][j];
					sorted[i * m + j][1] = i;
				}
				Arrays.sort(paths[i]);
			}

			Arrays.sort(sorted, (a, b) -> a[0] - b[0]);
			for(int i = 0; i < m; i++) {
				int node = sorted[i][1];
				int length = sorted[i][0];
				runners[i][node] = length;
			}
			for(int i = 0; i < n; i++) {
				int pointer = m - 1;
				for(int j = 0; j < m; j++) {
					if(runners[j][i] == 0) {
						runners[j][i] = paths[i][pointer];
						pointer --;
					}
				}
			}
			for(int j = 0; j < n; j++) {
				for(int i = 0; i < m; i++) {
					fout.append(runners[i][j]).append(" ");
				}
				fout.append("\n");
			}
		}
		System.out.print(fout);
	}
}
