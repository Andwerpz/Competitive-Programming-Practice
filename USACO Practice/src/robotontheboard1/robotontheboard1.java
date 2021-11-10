//package robotontheboard1;

import java.util.*;
import java.io.*;

public class robotontheboard1 {
	public static void main(String[] args) throws IOException {
		
		//1607E
		
		//since you can only do the moves in order, you can simulate all the moves, and stop when the trail traced out by the robot
		//exceeds the size of the board. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());
			char[] s = fin.readLine().toCharArray();
			int[][] commands = new int[s.length][2];
			for(int i = 0; i < s.length; i++) {
				if(s[i] == 'R') {
					commands[i] = new int[] {1, 0};
				}
				else if(s[i] == 'L') {
					commands[i] = new int[] {-1, 0};
				}
				else if(s[i] == 'U') {
					commands[i] = new int[] {0, -1};
				}
				else {
					commands[i] = new int[] {0, 1};
				}
			}
			int curX = 1;
			int curY = 1;
			int minX = 1;
			int minY = 1;
			int maxX = 1;
			int maxY = 1;
			for(int i = 0; i < commands.length; i++) {
				curX += commands[i][0];
				curY += commands[i][1];
				if(curX < minX) {
					if(maxX - curX + 1 > m) {
						break;
					}
					minX = curX;
				}
				else if(curY < minY) {
					if(maxY - curY + 1 > n) {
						break;
					}
					minY = curY;
				}
				else if(curX > maxX) {
					if(maxX - curX + 1 > m) {
						break;
					}
					maxX = curX;
				}
				else if(curY > maxY) {
					if(maxY - curY + 1 > n) {
						break;
					}
					maxY = curY;
				}
				//System.out.println("LOO");
			}
			//System.out.println(minX + " " + minY);
			fout.append((1 + (1 - minY)) + " " + (1 + (1 - minX)) + "\n");
		}
		System.out.print(fout);
	}
}
