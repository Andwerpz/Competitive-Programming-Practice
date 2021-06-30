//package therobot;

import java.util.*;
import java.io.*;

public class therobot {
	public static void main(String[] args) throws IOException {
		
		//1468K
		
		//this problem is weird, it required me to double check the answer in the algorithm, nvm, i figured it out
		
		//since the only effective positions for the block to be is on the path of the robot, just test each block position, there are n block positions, and n tests, so O(n^2)
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t -- > 0) {
			char[] s = fin.readLine().toCharArray();
			int n = s.length;
			int[] xDiff = new int[n];
			int[] yDiff = new int[n];
			for(int i = 0; i < n; i++) {
				char next = s[i];
				if(next == 'U') {
					yDiff[i] = 1;
				}
				else if(next == 'D') {
					yDiff[i] = -1;
				}
				else if(next == 'R') {
					xDiff[i] = 1;
				}
				else if(next == 'L') {
					xDiff[i] = -1;
				}
			}
//			for(int i = 0; i < n; i++) {
//				System.out.println(xDiff[i] + " " + yDiff[i]);
//			}
			int x = 0;
			int y = 0;
			int ansX = 0;
			int ansY = 0;
			for(int i = 0; i < n; i++) {
				int blockX = x + xDiff[i];
				int blockY = y + yDiff[i];
				int curX = x;
				int curY = y;
				if(blockX != 0 || blockY != 0) {
					for(int j = i + 1; j < n; j++) {
						//System.out.println("CUR POS: " + curX + " " + curY);
						curX += xDiff[j];
						curY += yDiff[j];
						
						if(curX == blockX && curY == blockY) {
							//System.out.println("BLOCKED: " + curX + " " + curY);
							curX -= xDiff[j];
							curY -= yDiff[j];
						}
					}
					if(curX == 0 && curY == 0 && (blockX != 0 || blockY != 0)) {
						//final test
						curX = 0;
						curY = 0;
						for(int j = 0; j < n; j++) {
							//System.out.println("CUR POS: " + curX + " " + curY);
							curX += xDiff[j];
							curY += yDiff[j];
							
							if(curX == blockX && curY == blockY) {
								//System.out.println("BLOCKED: " + curX + " " + curY);
								curX -= xDiff[j];
								curY -= yDiff[j];
							}
						}
						if(curX == 0 && curY == 0) {
							ansX = blockX;
							ansY = blockY;
							break;
						}
						
					}
				}
				
				
				x += xDiff[i];
				y += yDiff[i];
			}
			fout.append(ansX + " " + ansY).append("\n");
		}
		System.out.print(fout);
	}
}
