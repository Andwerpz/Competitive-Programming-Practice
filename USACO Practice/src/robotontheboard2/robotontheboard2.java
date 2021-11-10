//package robotontheboard2;

import java.util.*;
import java.io.*;

public class robotontheboard2 {
	public static void main(String[] args) throws IOException {
		
		//1607F
		
		//came up with the right answer, my implementation just sucks. 
		//in cpp, instead of vector<int>, use pair<int, int>
		
		//you just have to check the size of path for each cell in the grid. Notice that from each cell, since each cell has only 1 outgoing edge,
		//there is only 1 possible path for the robot to take. This means that if you process a path, and another path happens to intersect
		//with that already processed path, you don't need to process the rest of the path, since you already know where it is going. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		int t = Integer.parseInt(fin.readLine());
		while(t-- > 0) {
			fin.readLine();
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());
			char[][] board = new char[n][m];
			for(int i = 0; i < n; i++) {
				board[i] = fin.readLine().toCharArray();
			}
			int[][] steps = new int[n][m];
			for(int i = 0; i < n; i++) {
				Arrays.fill(steps[i], -1);
			}
			for(int i = 0; i < n; i++) {
				for(int j = 0; j < m; j++) {
					if(steps[i][j] == -1) {
						boolean loop = false;
						HashSet<ArrayList<Integer>> visited = new HashSet<ArrayList<Integer>>();
						Stack<ArrayList<Integer>> order = new Stack<ArrayList<Integer>>();
						ArrayList<Integer> cur = new ArrayList<Integer>(Arrays.asList(i, j));
						ArrayList<Integer> next = new ArrayList<Integer>();
						visited.add(cur);
						order.push(cur);
						int x = i;
						int y = j;
						while(true) {	//iterate until you find a loop, or you go off the board
							char nextMove = board[x][y];
							if(nextMove == 'L') {
								y --;
							}
							else if(nextMove == 'R') {
								y ++;
							}
							else if(nextMove == 'U') {
								x --;
							}
							else {
								x ++;
							}
							//first check if we've hit a loop, or out of bounds
							if(x < 0 || y < 0 || x >= n || y >= m) {
								break;
							}
							next = new ArrayList<Integer>(Arrays.asList(x, y));
							order.add(next);
							if(visited.contains(next)) {
								loop = true;
								break;
							}
							//we aren't in loop, or out of bounds. Check if we've already visited this cell
							if(steps[x][y] != -1) {
								break;
							}
							//this is our first time visiting this cell. 
							visited.add(next);
						}
						if(loop) {	
							//we need to first assign the same value to all cells that are in the loop
							ArrayList<Integer> loopEnd = order.pop();
							ArrayList<ArrayList<Integer>> loopCells = new ArrayList<ArrayList<Integer>>();
							while(true) {
								next = order.pop();
								loopCells.add(next);
								if(loopEnd.equals(next)) {
									break;
								}
							}
							for(ArrayList<Integer> a : loopCells) {
								steps[a.get(0)][a.get(1)] = loopCells.size() - 1;
							}
							//now just proceed like normal
							int counter = loopCells.size();
							while(order.size() != 0) {
								next = order.pop();
								steps[next.get(0)][next.get(1)] = counter;
								counter ++;
							}
						}
						else {
							ArrayList<Integer> last = order.pop();
							int counter = 0;
							if(steps[last.get(0)][last.get(1)] == -1) {	//new cell. Initialize value to 0
								steps[last.get(0)][last.get(1)] = 0;
								counter = 1;
							}
							else {	//already visited cell. Start with value in cell
								counter = steps[last.get(0)][last.get(1)];
								counter ++;
							}
							while(order.size() != 0) {
								next = order.pop();
								steps[next.get(0)][next.get(1)] = counter;
								counter ++;
							}
						}
					}
				}
			}
			int r = 0;
			int c = 0;
			int d = steps[0][0];
			for(int i = 0; i < n; i++) {
				for(int j = 0; j < m; j++) {
					if(steps[i][j] > d) {
						r = i;
						c = j;
						d = steps[i][j];
					}
				}
			}
			r ++;
			c ++;
			d ++;
			fout.append(r + " " + c + " " + d + "\n");
		}
		System.out.print(fout);
	}
}
