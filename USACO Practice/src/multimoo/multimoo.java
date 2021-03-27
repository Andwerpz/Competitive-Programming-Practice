/*
ID: andwerp1
LANG: JAVA
TASK: multimoo
*/

//package multimoo;

import java.io.*;
import java.util.*;

public class multimoo {
	
	static int getSize(int[] first, int teamColor, int[][] board) {
		
		int color = board[first[0]][first[1]];
		
		Stack<int[]> toProcess = new Stack<int[]>();
		toProcess.add(first);
		
		HashSet<ArrayList<Integer>> visited = new HashSet<ArrayList<Integer>>();
		visited.add(new ArrayList<Integer>(Arrays.asList(first[0], first[1])));
		
		while(toProcess.size() != 0) {
			
			int[] cur = toProcess.pop();
			
			int x = cur[0];
			int y = cur[1];
			
			x -= 1;
			
			if(x >= 0 && (board[x][y] == color || board[x][y] == teamColor) && !visited.contains(new ArrayList<Integer>(Arrays.asList(x, y)))) {	//-x
				
				toProcess.add(new int[] {x, y});
				visited.add(new ArrayList<Integer>(Arrays.asList(x, y)));
				
			}
			
			x += 2;
			
			if(x < board.length && (board[x][y] == color || board[x][y] == teamColor) && !visited.contains(new ArrayList<Integer>(Arrays.asList(x, y)))) {	//+x
				
				toProcess.add(new int[] {x, y});
				visited.add(new ArrayList<Integer>(Arrays.asList(x, y)));
				
			}
			
			x -= 1;
			y -= 1;
			
			if(y >= 0 && (board[x][y] == color || board[x][y] == teamColor) && !visited.contains(new ArrayList<Integer>(Arrays.asList(x, y)))) {	//-y
				
				toProcess.add(new int[] {x, y});
				visited.add(new ArrayList<Integer>(Arrays.asList(x, y)));
				
			}
			
			y += 2;

			if(y < board.length && (board[x][y] == color || board[x][y] == teamColor) && !visited.contains(new ArrayList<Integer>(Arrays.asList(x, y)))) {	//+y
				
				toProcess.add(new int[] {x, y});
				visited.add(new ArrayList<Integer>(Arrays.asList(x, y)));
				
			}
			
		}
		
		return visited.size();
		
	}
	
	public static void main (String [] args) throws IOException {
		
	//to solve, we need to find the largest connected group of 1 color, and find the largest combination of 2 connected colors
	//since the board size is small; <= 250, we can brute force the connections.
		
	//start by floodfilling one color, and when we hit another color, start up a secondary floodfill that checks the size of the color that we ran into.
	//add the maximum size from the colors that we run into with the size of the current color, and save the maximum out of all of them
		
	//this solution is too slow to get past worst case
    
    BufferedReader fin = new BufferedReader(new FileReader("multimoo.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("multimoo.out")));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    
    int[][] board = new int[n][n];
    
    for(int i = 0; i < n; i++) {
    	
    	st = new StringTokenizer(fin.readLine());
    	
    	for(int j = 0; j < n; j++) {
    		
    		board[i][j] = Integer.parseInt(st.nextToken());
    		
    	}
    	
    }
    
    int curColor = -1;
    
    int maxSizeOne = 0;
    int maxSizeTwo = 0;
    
    HashSet<ArrayList<Integer>> globalVisited = new HashSet<ArrayList<Integer>>();
    
    for(int i = 0; i < n; i++) {
    	
    	for(int j = 0; j < n; j++) {
    		
    		//System.out.println(maxSizeOne + " " + maxSizeTwo);
    		
    		if(board[i][j] != curColor && !globalVisited.contains(new ArrayList<Integer>(Arrays.asList(i, j)))) {
    			
    			curColor = board[i][j];
    			
    			Stack<int[]> toProcess = new Stack<int[]>();
    			toProcess.add(new int[] {i, j});
    			
    			HashSet<ArrayList<Integer>> visited = new HashSet<ArrayList<Integer>>();
    			visited.add(new ArrayList<Integer>(Arrays.asList(i, j)));
    			
    			HashSet<Integer> visitedColors = new HashSet<Integer>();
    			
    			int maxSecondSize = 0;
    			
    			while(toProcess.size() != 0) {
    				
    				int[] cur = toProcess.pop();
    				
    				int x = cur[0];
    				int y = cur[1];
    				
    				globalVisited.add(new ArrayList<Integer>(Arrays.asList(x, y)));
    				
    				x -= 1;
    				
    				if(x >= 0 && board[x][y] == curColor && !visited.contains(new ArrayList<Integer>(Arrays.asList(x, y)))) {	//-x
    					
    					toProcess.add(new int[] {x, y});
    					visited.add(new ArrayList<Integer>(Arrays.asList(x, y)));
    					
    				}
    				
    				else if(x >= 0 && !visitedColors.contains(board[x][y])) {
    					
    					visitedColors.add(board[x][y]);
    					
    					int size = getSize(new int[] {x, y}, curColor, board);
    					
    					if(size > maxSecondSize) {
    						maxSecondSize = size;
    					}
    					
    				}
    				
    				x += 2;
    				
    				if(x < board.length && board[x][y] == curColor && !visited.contains(new ArrayList<Integer>(Arrays.asList(x, y)))) {	//+x
    					
    					toProcess.add(new int[] {x, y});
    					visited.add(new ArrayList<Integer>(Arrays.asList(x, y)));
    					
    				}
    				
    				else if(x < board.length && !visitedColors.contains(board[x][y])) {
    					
    					visitedColors.add(board[x][y]);
    					
    					int size = getSize(new int[] {x, y}, curColor, board);
    					
    					if(size > maxSecondSize) {
    						maxSecondSize = size;
    					}
    					
    				}
    				
    				x -= 1;
    				y -= 1;
    				
    				if(y >= 0 && board[x][y] == curColor && !visited.contains(new ArrayList<Integer>(Arrays.asList(x, y)))) {	//-y
    					
    					toProcess.add(new int[] {x, y});
    					visited.add(new ArrayList<Integer>(Arrays.asList(x, y)));
    					
    				}
    				
    				else if(y >= 0 && !visitedColors.contains(board[x][y])) {
    					
    					visitedColors.add(board[x][y]);
    					
    					int size = getSize(new int[] {x, y}, curColor, board);
    					
    					if(size > maxSecondSize) {
    						maxSecondSize = size;
    					}
    					
    				}
    				
    				y += 2;
    				
    				if(y < board.length && board[x][y] == curColor && !visited.contains(new ArrayList<Integer>(Arrays.asList(x, y)))) {	//+y
    					
    					toProcess.add(new int[] {x, y});
    					visited.add(new ArrayList<Integer>(Arrays.asList(x, y)));
    					
    				}
    				
    				else if(y < board.length && !visitedColors.contains(board[x][y])) {
    					
    					visitedColors.add(board[x][y]);
    					
    					int size = getSize(new int[] {x, y}, curColor, board);
    					
    					if(size > maxSecondSize) {
    						maxSecondSize = size;
    					}
    					
    				}
    				
    			}
    			
    			if(visited.size() > maxSizeOne) {
    				maxSizeOne = visited.size();
    			}
    			
    			if(maxSecondSize > maxSizeTwo) {
    				maxSizeTwo = maxSecondSize;
    			}
    			
    			if(maxSecondSize == n * n) {
    				break;
    			}
    			
    		}
    		
    	}
    	
    	if(maxSizeTwo == n * n) {
    		break;
    	}
    	
    }
    
    fout.println(maxSizeOne + "\n" + maxSizeTwo);
    
    fin.close();
    fout.close();
    
	}
}