//package aerodynamic;

import java.util.*;
import java.io.*;

public class aerodynamic {
	public static void main(String[] args) throws IOException {
		
		//1299B
		
		//a convex polygon makes a minkowski difference similar with itself only if it has center symmetry. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		if(n % 2 == 1) {
			System.out.println("NO");
		}
		else {
			int[][] points = new int[n][2];
			for(int i = 0; i < n; i++) {
				StringTokenizer st = new StringTokenizer(fin.readLine());
				points[i][0] = Integer.parseInt(st.nextToken()) * 10;
				points[i][1] = Integer.parseInt(st.nextToken()) * 10;
			}
			int midX = 0;
			int midY = 0;
			boolean isValid = true;
			for(int i = 0; i < n / 2; i++) {
				int curMidX = (points[i][0] + points[i + n / 2][0]) / 2;
				int curMidY = (points[i][1] + points[i + n / 2][1]) / 2;
				if(i == 0) {
					midX = curMidX;
					midY = curMidY;
				}
				else if(midX != curMidX || midY != curMidY){
					isValid = false;
					break;
				}
			}
			System.out.print(isValid? "YES" : "NO");
		}
	}
}
