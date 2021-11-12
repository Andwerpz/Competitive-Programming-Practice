//package banquetpreparations2;

import java.util.*;
import java.io.*;

public class banquetpreparations2 {
	public static void main(String[] args) throws IOException {
		
		//1607H
		
		//if you plot each dish on the coordinate plane, (a = x; b = y), plot the range of points that each dish can become 
		//after eating m units of food. 
		
		//notice that for each dish, the range of points always forms a diagonal line of slope -1. If lines of two dishes don't intersect, 
		//then it is impossible for those two dishes to be made the same. 
		
		//so, to solve, first generate these lines, and then group the dishes based on whether it is possible for them to intersect. 
		//then it is just a basic 2 pointer problem grouping the groups greedily to make the least amount of unique dishes. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			fin.readLine();
			int n = Integer.parseInt(fin.readLine());
			int[][] dishes = new int[n][9];	//x, y, m, layer, start, end, eatenx, eateny, old index
			for(int i = 0; i < n; i++) {
				StringTokenizer st = new StringTokenizer(fin.readLine());
				for(int j = 0; j < 3; j++) {
					dishes[i][j] = Integer.parseInt(st.nextToken());
				}
				dishes[i][8] = i;
			}
			for(int i = 0; i < n; i++) {
				int x = dishes[i][0]; int y = dishes[i][1]; int m = dishes[i][2];
				dishes[i][3] = x + y - m;
				dishes[i][4] = Math.max(0, x - m);
				dishes[i][5] = x;
				
			}
			Arrays.sort(dishes, (a, b) -> a[3] == b[3]? Integer.compare(a[4], b[4]) : Integer.compare(a[3], b[3]));
//			for(int i = 0; i < n; i++) {
//				for(int j : dishes[i]) {
//					System.out.print(j + " ");
//				}
//				System.out.println();
//			}
			int prevLayer = dishes[0][3];
			int high = dishes[0][5];
			int low = dishes[0][4];
			boolean[] answered = new boolean[n];
			int numUnique = 0;
			for(int i = 1; i < n; i++) {
				int layer = dishes[i][3];
				int start = dishes[i][4];
				int end = dishes[i][5];
				if(layer != prevLayer || start > high) {
					numUnique ++;
					//go back, and set the answers
					int index = i - 1;
					if(low < 0) {
						low = 0;
					}
					int xLeft = low;
					int yLeft = prevLayer - low;
					//System.out.println(xLeft + " " + yLeft + " I: " + i);
					//System.out.println("LO: " + low + " LAY: " + prevLayer);
					while(true) {
						int nextLow = dishes[index][4];
						int nextHigh = dishes[index][5];
						int nextLayer = dishes[index][3];
						if(!(nextLow <= low && nextHigh >= high && nextLayer == prevLayer) || answered[index]) {
							break;
						}
						answered[index] = true;
						dishes[index][6] = dishes[index][0] - xLeft;
						dishes[index][7] = dishes[index][1] - yLeft;
						//System.out.println(dishes[index][6] + " " + dishes[index][7]);
						index --;
						if(index == -1) {
							break;
						}
					}
					prevLayer = layer;
					low = start;
					high = end;
				}
				else {
					low = Math.max(low, start);
					high = Math.min(high, end);
				}
			}
			numUnique ++;
			int index = n - 1;
			int xLeft = low;
			int yLeft = prevLayer - low;
			while(true) {
				int nextLow = dishes[index][4];
				int nextHigh = dishes[index][5];
				int nextLayer = dishes[index][3];
				if(!(nextLow <= low && nextHigh >= high && nextLayer == prevLayer) || answered[index]) {
					break;
				}
				answered[index] = true;
				dishes[index][6] = dishes[index][0] - xLeft;
				dishes[index][7] = dishes[index][1] - yLeft;
				//System.out.println(dishes[index][6] + " " + dishes[index][7]);
				index --;
				if(index == -1) {
					break;
				}
			}
			Arrays.sort(dishes, (a, b) -> Integer.compare(a[8], b[8]));
			fout.append(numUnique).append("\n");
			for(int i = 0; i < n; i++) {
				fout.append(dishes[i][6]).append(" ").append(dishes[i][7]).append("\n");
			}
		}
		System.out.print(fout);
	}
}
