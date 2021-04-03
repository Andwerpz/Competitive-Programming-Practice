//package obsessionwithrobots;

import java.util.*;
import java.io.*;

public class obsessionwithrobots {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		
		String input = fin.readLine();
		boolean[][] board = new boolean[210][210];
		int x = 105;
		int y = 105;
		board[x][y] = true;
		
		int[] dx = new int[] {1, -1, 0, 0};
		int[] dy = new int[] {0, 0, 1, -1};
		boolean isValid = true;
		
		for(int i = 0; i < input.length(); i++) {
			
			int prevX = x;
			int prevY = y;
			
			if(input.charAt(i) == 'L') {
				x -= 1;
			}
			else if(input.charAt(i) == 'R') {
				x += 1;
			}
			else if(input.charAt(i) == 'D') {
				y -= 1;
			}
			else if(input.charAt(i) == 'U') {
				y += 1;
			}
			
			if(board[x][y]) {
				isValid = false;
				break;
			}
			board[x][y] = true;
			board[prevX][prevY] = false;
			
			for(int j = 0; j < 4; j++) {
				if(board[x + dx[j]][y + dy[j]]) {
					isValid = false;
					break;
				}
			}
			if(!isValid) {
				break;
			}
			
			board[prevX][prevY] = true;
		}
		
		if(isValid) {
			System.out.println("OK");
		}
		else {
			System.out.println("BUG");
		}
	}
}
