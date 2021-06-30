//package feedingchicken;

import java.util.*;
import java.io.*;

public class feedingchicken {
	public static void main(String[] args) throws IOException {
		
		//1254A
		
		//just go down the grid in a sort of zig-zag pattern. That way, all of your chicken pens will connect to each other.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int r = Integer.parseInt(st.nextToken());
			int c = Integer.parseInt(st.nextToken());
			int k = Integer.parseInt(st.nextToken());
			char[] symbols = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890".toCharArray();
			char[][] grid = new char[r][c];
			int numFood = 0;
			for(int i = 0; i < r; i++) {
				grid[i] = fin.readLine().toCharArray();
				for(int j = 0; j < c; j++) {
					if(grid[i][j] == 'R') {
						numFood ++;
					}
				}
			}
			boolean backwards = false;
			int multiple = numFood / k;
			int remainder = numFood % k;
			int curAmt = multiple;
			int pointer = 0;
			if(remainder != 0) {
				curAmt ++;
				remainder --;
			}
			char[][] ans = new char[r][c];
			for(int i = 0; i < r; i++) {
				for(int j = (backwards? c - 1 : 0); (backwards? j >= 0 : j < c); j += 0) {
					ans[i][j] = symbols[pointer];
					if(grid[i][j] == 'R') {
						curAmt --;
					}
					if(curAmt == 0) {
						curAmt = multiple;
						if(pointer != k - 1) {
							pointer ++;
						}
						if(remainder != 0) {
							curAmt ++;
							remainder --;
						}
					}
					j += backwards? -1 : 1;
				}
				fout.append(String.valueOf(ans[i])).append("\n");
				backwards = !backwards;
			}
		}
		System.out.print(fout);
	}
}
