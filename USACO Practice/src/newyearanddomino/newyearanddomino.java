//package newyearanddomino;

import java.util.*;
import java.io.*;

public class newyearanddomino {
	public static void main(String[] args) throws IOException {
		
		//precalculate a pfx sum array for the number of dominoes you can put in a rectangle.
		//also calculate an array that stores the amount of horizontal and vertical disallowed overlaps at any given point, kind of like a pfx array
		//when calculating the initial subrectangle needs to account for both horizontal and vertical overlaps at the boundary. 
		//the two subtracting subrectangles need to account for their respective side, the one exposed downwards needs to account for horizontal overlaps, and 
		//the one exposed to the right needs to account for vertical overlaps.
		//the final array that accounts for the overlap of the subtracting arrays doesn't need to account for any overlap, since it is completely inside the two subrectangles.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int h = Integer.parseInt(st.nextToken());
		int w = Integer.parseInt(st.nextToken());
		char[][] grid = new char[h][w];
		for(int i = 0; i < h; i++) {
			grid[i] = fin.readLine().toCharArray();
		}
		int[][] nums = new int[h][w];
		for(int i = 0; i < h; i++) {
			for(int j = 0; j < w; j++) {
				if(grid[i][j] == '.') {
					if(i + 1 < h && grid[i + 1][j] == '.') {
						nums[i][j] ++;
					}
					if(j + 1 < w && grid[i][j + 1] == '.') {
						nums[i][j] ++;
					}
				}
			}
		}
		int[][] pfx = new int[h + 1][w + 1];
		int[][] hor = new int[h][w];
		int[][] vert = new int[h][w];
		for(int i = 1; i <= h; i++) {
			for(int j = 1; j <= w; j++) {
				pfx[i][j] += nums[i - 1][j - 1] + pfx[i - 1][j] + pfx[i][j - 1] - pfx[i - 1][j - 1];
			}
		}
		for(int i = 0; i < h - 1; i++) {	//doing horizontal overlaps
			int count = 0;
			for(int j = 0; j < w; j++) {
				if(grid[i + 1][j] == '.' && grid[i][j] == '.') {
					count ++;
				}
				hor[i][j] = count;
			}
		}
		for(int i = 0; i < w - 1; i++) {	//vertical overlaps
			int count = 0;
			for(int j = 0; j < h; j++) {
				if(grid[j][i + 1] == '.' && grid[j][i] == '.') {
					count ++;
				}
				vert[j][i] = count;
			}
		}
//		System.out.println();
//		for(int[] i : pfx) {
//			for(int j : i) {
//				System.out.print(j + " ");
//			}
//			System.out.println();
//		}
//		System.out.println();
//		for(int[] i : hor) {
//			for(int j : i) {
//				System.out.print(j + " ");
//			}
//			System.out.println();
//		}
//		System.out.println();
//		for(int[] i : vert) {
//			for(int j : i) {
//				System.out.print(j + " ");
//			}
//			System.out.println();
//		}
//		System.out.println();
		StringBuilder fout = new StringBuilder();
		int q = Integer.parseInt(fin.readLine());
		while(q -- > 0) {
			st = new StringTokenizer(fin.readLine());
			int x1 = Integer.parseInt(st.nextToken());
			int y1 = Integer.parseInt(st.nextToken());
			int x2 = Integer.parseInt(st.nextToken());
			int y2 = Integer.parseInt(st.nextToken());
			int mainAdd = (pfx[x2][y2] - hor[x2 - 1][y2 - 1] - vert[x2 - 1][y2 - 1]);
			int horSub = (pfx[x2][y1 - 1] - ((y1 - 2 >= 0)? hor[x2 - 1][y1 - 2] : 0));
			int vertSub = (pfx[x1 - 1][y2] - ((x1 - 2 >= 0)? vert[x1 - 2][y2 - 1] : 0));
			int secondAdd = pfx[x1 - 1][y1 - 1];
			int ans = mainAdd - horSub - vertSub + secondAdd;
			//System.out.println(mainAdd + " " + horSub + " " + vertSub + " " + secondAdd);
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
