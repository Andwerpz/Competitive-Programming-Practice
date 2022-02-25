//package hardway;

import java.util.*;
import java.io.*;

public class hardway {
	public static void main(String[] args) throws IOException {
		
		//1642A
		
		//notice that the only way that you'll not be able to directly reach an edge of the triangle is if 
		//it is parallel to the x axis and facing away from it.
		
		//so, you just have to determine if an edge is parallel to the x axis, and if it is facing away from it.
		
		//if there are two points that share a y coordinate, then that means that there is an edge parallel to the x axis
		
		//if the third point has a y coordinate less than those two points, then it has to be facing away
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int[][] p = new int[3][2];
			int maxY = 0;
			int count = 0;
			int first = 0;
			int second = 0;
			for(int i = 0; i < 3; i++) {
				StringTokenizer st = new StringTokenizer(fin.readLine());
				p[i][0] = Integer.parseInt(st.nextToken());
				p[i][1] = Integer.parseInt(st.nextToken());
				maxY = Math.max(p[i][1], maxY);
			}
			for(int i = 0; i < 3; i++) {
				if(p[i][1] == maxY) {
					count ++;
					if(count == 1) {
						first = p[i][0];
					}
					else {
						second = p[i][0];
					}
				}
			}
			fout.append(count == 2? Math.abs(first - second) : 0).append("\n");
		}
		System.out.print(fout);
	}
}
