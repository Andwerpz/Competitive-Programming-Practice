//package heidiandtheturingtesteasy;

import java.util.*;
import java.io.*;

public class heidiandtheturingtest {
	public static void main(String[] args) throws IOException {
		
		//1184C1
		
		//since there is only one point, we can still define the square. Just find the minimum and maximum of each x and y that at least 2 points are lined up. The extra
		//point can't affect this since it's only one point. Then just test for each point whether it is on the square, and if it is not, then that is our point.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		int minH = Integer.MAX_VALUE;
		int maxH = Integer.MIN_VALUE;
		int minV = Integer.MAX_VALUE;
		int maxV = Integer.MIN_VALUE;
		HashSet<Integer> horizontal = new HashSet<Integer>();
		HashSet<Integer> vertical = new HashSet<Integer>();
		int[][] points = new int[n * 4 + 1][2];
		for(int i = 0; i < points.length; i++) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int x = Integer.parseInt(st.nextToken());
			int y = Integer.parseInt(st.nextToken());
			if(vertical.contains(x)) {
				minV = Math.min(x, minV);
				maxV = Math.max(x, maxV);
			}
			if(horizontal.contains(y)) {
				minH = Math.min(y, minH);
				maxH = Math.max(y, maxH);
			}
			vertical.add(x);
			horizontal.add(y);
			points[i] = new int[] {x, y};
		}
//		System.out.println(minV + " " + maxV);
//		System.out.println(minH + " " + maxH);
		for(int i = 0; i < points.length; i++) {
			int x = points[i][0];
			int y = points[i][1];
			if(((x == minV || x == maxV) && !(y <= maxH && y >= minH)) || ((y == minH || y == maxH) && !(x <= maxV && x >= minV)) || (x != minV && x != maxV && y != minH && y != maxH)) {
				System.out.println(x + " " + y);
				break;
			}
		}
	}
}
