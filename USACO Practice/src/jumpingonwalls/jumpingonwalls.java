
//package jumpingonwalls;

import java.io.*;
import java.util.*;

public class jumpingonwalls {
	
	//static boolean[][] visited;
	
	static boolean game(boolean[][] safe, boolean[][] visited, int water, int k, int x, int y) {
		
		//System.out.println(x + " " + y + " " + water);
//		for(int i = 0; i < safe.length; i++) {
//			for(int j = 0; j < safe[i].length; j++) {
//				if(x == i && j == y) {
//					System.out.print("O");
//				}
//				else if(visited[i][j]) {
//					System.out.print("*");
//				}
//				else if(safe[i][j]) {
//					System.out.print("-");
//				}
//				else {
//					System.out.print("X");
//				}
//			}
//			System.out.println();
//		}
		
		visited[x][y] = true;
		
		if(water >= y) {
			return false;
		}
		if(y + k >= safe[0].length || y + 1 >= safe[0].length) {
			return true;
		}
		
		boolean up = false;
		boolean down = false;
		boolean jump = false;
		if(x == 0 && safe[1][y + k] && !visited[1][y + k]) {
			//System.out.println("jump");
			jump = game(safe, visited, water + 1, k, 1, y + k);
		}
		else if(x == 1 && safe[0][y + k] && !visited[0][y + k]) {
			//System.out.println("jump");
			jump = game(safe, visited, water + 1, k, 0, y + k);
		}
		if(safe[x][y + 1] && !visited[x][y + 1]) {
			//System.out.println("up");
			up = game(safe, visited, water + 1, k, x, y + 1);
		}
		if(y != 0 && safe[x][y - 1] && !visited[x][y - 1]) {
			//System.out.println("down");
			down = game(safe, visited, water + 1, k, x, y - 1);
		}
		
		
		return up || down || jump;
	}
	
	public static void main (String [] args) throws IOException {
		
	//we can just simulate the whole thing; O(n), n <= 10^5 (maybe, we'll see)
	//lets do it recursively
		
	//when we do it recursively, we have to make sure that we don't go to somewhere that we have already visited. 
	//also, prioritize jumping, since this makes us able to go backwards in the future.
    
    BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    int k = Integer.parseInt(st.nextToken());
    //visited = new boolean[2][n];
    
    boolean[][] safe = new boolean[2][n];
    for(int i = 0; i < 2; i++) {
    	String input = fin.readLine();
    	for(int j = 0; j < n; j++) {
    		if(input.charAt(j) == '-') {
    			safe[i][j] = true;
    		}
    	}
    }
    
    int water = -1;
    boolean done = false;
    boolean[][] visited = new boolean[2][n];
    
    System.out.println(game(safe, visited, water, k, 0, 0)? "YES" : "NO");
    fin.close();
    
	}
}