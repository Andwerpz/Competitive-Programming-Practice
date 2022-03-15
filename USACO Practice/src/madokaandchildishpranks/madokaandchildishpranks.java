//package madokaandchildishpranks;

import java.util.*;
import java.io.*;

public class madokaandchildishpranks {
	public static void main(String[] args) throws IOException {
		
		//1647C
		
		//first, if there is a black tile in the position [1][1] of the target pattern, the 
		//input is invalid because you can never color that tile black. 
		
		//if there isn't, then you can always color the board to match the target. 
		
		//notice that in the chess patterning, there is a white tile in the upper left corner, and 
		//a black tile right beneath it. We can use this black tile to color in row-by-row the black
		//tiles in the target.
		
		//When we only have 1 row left, just use the black tile to the right of the white tile, and 
		//color cell by cell. 
		
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
			if(nums[0][0] == 1) {
				fout.append("-1\n");
				continue;
			}
			ArrayList<int[]> ans = new ArrayList<int[]>();
			for(int i = n - 1; i >= 1; i--) {
				for(int j = 0; j < m; j++) {
					if(nums[i][j] == 1) {
						ans.add(new int[] {i, j + 1, i + 1, j + 1});
					}
				}
			}
			for(int j = m - 1; j >= 1; j--) {
				if(nums[0][j] == 1) {
					ans.add(new int[] {1, j, 1, j + 1});
				}
			}
			fout.append(ans.size()).append("\n");
			for(int[] i : ans) {
				fout.append(i[0]).append(" ").append(i[1]).append(" ").append(i[2]).append(" ").append(i[3]).append("\n");
			}
		}
		System.out.print(fout);
	}
}
