//package bargainingtable;

import java.util.*;
import java.io.*;

public class bargainingtable {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		boolean[][] room = new boolean[n][m];
		for(int i = 0; i < n; i++) {
			char[] next = fin.readLine().toCharArray();
			for(int j = 0; j < m; j++) {
				if(next[j] == '1') {
					room[i][j] = true;
				}
				else {
					room[i][j] = false;
				}
			}
		}
		int ans = 0;
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				//System.out.print(room[i][j]);
				if(!room[i][j]) {
					int cPointer = j;
					int minRow = -1;
					while(cPointer < m && !room[i][cPointer]) {
						int rPointer = i;
						while(rPointer < n && !room[rPointer][cPointer] && (rPointer < minRow || minRow == -1)) {
							//System.out.print("# ");
							rPointer ++;
						}
						//System.out.println();
						if(rPointer < minRow || minRow == -1) {
							minRow = rPointer;
						}
						int curPerimeter = (cPointer - j + 1) * 2 + (rPointer - i) * 2;
						if(curPerimeter > ans) {
							ans = curPerimeter;
						}
						cPointer ++;
						
					}
				}
				//System.out.println();
				//System.out.print(ans + " ");
			}
			//System.out.println();
		}
		System.out.println(ans);
	}
}
