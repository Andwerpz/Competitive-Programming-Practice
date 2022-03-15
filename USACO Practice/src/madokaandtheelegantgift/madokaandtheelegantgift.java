//package madokaandtheelegantgift;

import java.util.*;
import java.io.*;

public class madokaandtheelegantgift {
	public static void main(String[] args) throws IOException {
		
		//1647B
		
		//notice that if a subrectangle is nice, then it needs to be the largest subrectangle possible
		//within the connected set of black tiles. 
		
		//the only time there can be two intersecting nice subrectangles is when the connected set of
		//black tiles do not perfectly form a rectangle.
		
		//to check for this, all we have to do is find for each set of connected black tiles, the min
		//x, y and max x, y, and check in the rectangular bounding box defined by these two points.
		//if we find a single white tile, then the table is not elegant.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());
			int[][] nums = new int[n][m];
			for(int i = 0; i < n; i++) {
				char[] s = fin.readLine().toCharArray();
				for(int j = 0; j < m; j++) {
					nums[i][j] = s[j] == '0'? 0 : 1;
				}
			}
			int[] dx = new int[] {-1, 1, 0, 0};
			int[] dy = new int[] {0, 0, -1, 1};
			boolean[][] v = new boolean[n][m];
			boolean isValid = true;
			outer:
			for(int i = 0; i < n; i++) {
				for(int j = 0; j < m; j++) {
					if(v[i][j] || nums[i][j] == 0) {
						continue;
					}
					v[i][j] = true;
					Stack<int[]> s = new Stack<int[]>();
					s.add(new int[] {i, j});
					int rMin = i;
					int rMax = i;
					int cMin = j;
					int cMax = j;
					while(s.size() != 0) {
						int[] cur = s.pop();
						rMin = Math.min(rMin, cur[0]);
						rMax = Math.max(rMax, cur[0]);
						cMin = Math.min(cMin, cur[1]);
						cMax = Math.max(cMax, cur[1]);
						for(int k = 0; k < 4; k++) {
							int rNext = cur[0] + dx[k];
							int cNext = cur[1] + dy[k];
							if(rNext == n || rNext == -1 || cNext == m || cNext == -1) {
								continue;
							}
							if(!v[rNext][cNext] && nums[rNext][cNext] == 1) {
								v[rNext][cNext] = true;
								s.add(new int[] {rNext, cNext});
							}
						}
					}
					for(int r = rMin; r <= rMax; r++) {
						for(int c = cMin; c <= cMax; c++) {
							if(nums[r][c] == 0) {
								isValid = false;
								break outer;
							}
						}
					}
//					for(boolean[] b : v) {
//						for(boolean c : b) {
//							System.out.print(c? "#" : '.');
//						}
//						System.out.println();
//					}
//					System.out.println();
				}
			}
			fout.append(isValid? "YES\n" : "NO\n");
		}
		System.out.print(fout);
	}
}
