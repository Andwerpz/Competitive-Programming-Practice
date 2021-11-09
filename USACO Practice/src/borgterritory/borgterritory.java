package borgterritory;

import java.util.*;
import java.io.*;

public class borgterritory {
	public static void main(String[] args) throws IOException {
		
		//2021 Keep Austin Hacking
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int x1 = Integer.parseInt(st.nextToken());
		int y1 = Integer.parseInt(st.nextToken());
		int n = Integer.parseInt(st.nextToken());
		char[] s = fin.readLine().toCharArray();
		int[][] moves = new int[n][2];
		for(int i = 0; i < n; i++) {
			if(s[i] == 'N') {
				moves[i][1] ++;
			}
			else if(s[i] == 'E') {
				moves[i][0] ++;
			}
			else if(s[i] == 'S') {
				moves[i][1] --;
			}
			else if(s[i] == 'W') {
				moves[i][0] --;
			}
		}
		int[][] path = new int[n][2];
		int x = 0;
		int y = 0;
		boolean isValid = false;
		for(int i = 0; i < n; i++) {
			x += moves[i][0];
			y += moves[i][1];
			path[i] = new int[] {x, y};
			if(x == x1 && y == y1) {
				isValid = true;
				break;
			}
		}
		if(isValid) {
			System.out.println("0 0");
		}
		else {
			ArrayList<int[]> obstacles = new ArrayList<int[]>();
			for(int i = 0; i < n; i++) {
				int obstacleX = path[i][0];
				int obstacleY = path[i][1];
				x = 0;
				y = 0;
				for(int j = 0; j < n; j++) {
					x += moves[j][0];
					y += moves[j][1];
					if(x == obstacleX && y == obstacleY) {
						x -= moves[j][0];
						y -= moves[j][1];
					}
					if(x == x1 && y == y1) {
						obstacles.add(new int[] {obstacleX, obstacleY});
						break;
					}
				}
			}
			if(obstacles.size() != 0) {
				obstacles.sort((a, b) -> Integer.compare(a[0], b[0]) == 0? Integer.compare(a[1], b[1]) : Integer.compare(a[0], b[0]));
				System.out.println(obstacles.get(0)[0] + " " + obstacles.get(0)[1]);
			}
			else {
				System.out.println("-1");
			}
		}
	}
}
