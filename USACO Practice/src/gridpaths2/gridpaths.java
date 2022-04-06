//package gridpaths2;

import java.util.*;
import java.io.*;

public class gridpaths {
	
	static char[] inputPath;
	static int[] dr = new int[] {-1, 1, 0, 0};
	static int[] dc = new int[] {0, 0, -1, 1};
	static char[] pathChars = new char[] {'U', 'D', 'L', 'R'};
	static boolean[][] v;
	
	public static int move(int r, int c, int pathLength) {
		
		//System.out.println(r + " " + c);
		
		//initial checks
		if(pathLength == 48) {
			if(r == 7 && c == 1) {
				return 1;
			}
			return 0;
		}
		else if(r == 7 && c == 1) {
			//path too short
			return 0;
		}
		
		//check if path is against a wall. 
		//if it cuts the grid in two, then discard current path
		if(!v[r - 1][c] && !v[r + 1][c] && v[r][c + 1] && v[r][c - 1]) {	//hitting a side wall
			return 0;
		}
		else if(!v[r][c - 1] && !v[r][c + 1] && v[r + 1][c] && v[r - 1][c]) {	//hitting a side wall
			return 0;
		}
		
		//we're making a move
		int ans = 0;
		v[r][c] = true;
		
		//if a turn is already determined
		char nextTurn = inputPath[pathLength];
		if(nextTurn == 'U' || nextTurn == 'D' || nextTurn == 'L' || nextTurn == 'R') {
			int nextR = r;
			int nextC = c;
			if(nextTurn == 'U') {
				nextR --;
			}
			else if(nextTurn == 'D') {
				nextR ++;
			}
			else if(nextTurn == 'R') {
				nextC ++;
			}
			else if(nextTurn == 'L') {
				nextC --;
			}
			if(!v[nextR][nextC]) {
				ans += move(nextR, nextC, pathLength + 1);
			}
		}
		
		//checking for dead ends
		else if((c < 6) && !v[r][c + 1] && ((v[r - 1][c + 1] && v[r][c + 2]) || (v[r + 1][c + 1] && v[r][c + 2]) || (v[r - 1][c + 1] && v[r + 1][c + 1]))) {
			//dead end on right
			ans = move(r, c + 1, pathLength + 1);	
		}
		else if((c > 2) && !v[r][c - 1] && ((v[r - 1][c - 1] && v[r][c - 2]) || (v[r + 1][c - 1] && v[r][c - 2]) || (v[r - 1][c - 1] && v[r + 1][c - 1]))) {
			//dead end on left
			ans = move(r, c - 1, pathLength + 1);
		}
		else if((r < 6) && !v[r + 1][c] && ((v[r + 1][c - 1] && v[r + 2][c]) || (v[r + 1][c + 1] && v[r + 2][c]) || (v[r + 1][c - 1] && v[r + 1][c + 1]))) {
			//dead end on bottom
			ans = move(r + 1, c, pathLength + 1);
		}
		else if((r > 2) && !v[r - 1][c] && ((v[r - 1][c - 1] && v[r - 2][c]) || (v[r - 1][c + 1] && v[r - 2][c]) || (v[r - 1][c - 1] && v[r - 1][c + 1]))) {
			//dead end on top
			ans = move(r - 1, c, pathLength + 1);
		}
		
		//normal movement
		else {
			for(int i = 0; i < 4; i++) {
				int nextR = r + dr[i];
				int nextC = c + dc[i];
				if(!v[nextR][nextC]) {
					ans += move(nextR, nextC, pathLength + 1);
				}
			}
		}
		
		v[r][c] = false;
		return ans;
	}
	
	public static void main(String[] args) throws IOException {
		
		//CSES 1625
		
		//complete search recursive solution with optimizations
		
		//if a path cuts the grid into two parts, then that path is invalid
		//if a path creates a dead end: a cell where there is only 1 unvisited adjacent cell to it, then it must visit that cell. 
		//if a path visits the end cell before visiting all the other cells, then we can discard it
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		inputPath = fin.readLine().toCharArray();
		v = new boolean[9][9];
		for(int i = 0; i < 9; i++) {
			v[i][0] = true;
			v[i][8] = true;
			v[0][i] = true;
			v[8][i] = true;
		}
		v[1][1] = true;
		long startTime = System.currentTimeMillis();
		System.out.println(move(1, 1, 0));
		//System.out.println("Time Elapsed: " + (System.currentTimeMillis() - startTime));
	}
}
