//package balancedremovalseasier;

import java.util.*;
import java.io.*;

public class balancedremovalseasier {
	public static void main(String[] args) throws IOException {
		
		//1237C1
		
		//all you have to do is for each point, just pick the closest point to it, prioritizing the three different coordinates in order. 
		//it won't work if you pick the closest point in euclidean distance, since there might be a point that is just as close, or a little bit farther away that is
		//still within the bounding box.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		int[][] points = new int[n][4];
		for(int i = 0; i < n; i++) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			points[i][0] = Integer.parseInt(st.nextToken());
			points[i][1] = Integer.parseInt(st.nextToken());
			points[i][2] = Integer.parseInt(st.nextToken());
			points[i][3] = i + 1;
		}
		//Arrays.sort(points, (a, b) -> Comparator.compareIntArr(a, b));
		StringBuilder fout = new StringBuilder();
		boolean[] v = new boolean[n];
		for(int i = 0; i < n; i++) {
			if(!v[i]) {
				v[i] = true;
				int minXDiff = Integer.MAX_VALUE;
				int minYDiff = Integer.MAX_VALUE;
				int minZDiff = Integer.MAX_VALUE;
				int minIndex = 0;
				for(int j = 0; j < n; j++) {
					if(!v[j] && ((Math.abs(points[j][0] - points[i][0]) < minXDiff) ||
							(Math.abs(points[j][0] - points[i][0]) == minXDiff && Math.abs(points[j][1] - points[i][1]) < minYDiff) || 
							(Math.abs(points[j][0] - points[i][0]) == minXDiff && Math.abs(points[j][1] - points[i][1]) == minYDiff && Math.abs(points[j][2] - points[i][2]) < minZDiff))) {
						minXDiff = Math.abs(points[j][0] - points[i][0]);
						minYDiff = Math.abs(points[j][1] - points[i][1]);
						minZDiff = Math.abs(points[j][2] - points[i][2]);
						minIndex = j;
					}
				}
				v[minIndex] = true;
				fout.append(i + 1).append(" ").append(minIndex + 1).append("\n");
			}
		}
		System.out.print(fout);
	}
	
	static class Comparator {
		public static int compareIntArr(int[] a, int[] b) {
			if(Integer.compare(a[0], b[0]) != 0) {
				return Integer.compare(a[0], b[0]);
			}
			else {
				if(Integer.compare(a[1], b[1]) != 0) {
					return Integer.compare(a[1], b[1]);
				}
				else {
					return Integer.compare(a[2], b[2]);
				}
			}
		}
	}
}
