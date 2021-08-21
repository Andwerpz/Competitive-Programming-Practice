//package coloredrooks;

import java.util.*;
import java.io.*;

public class coloredrooks {
	public static void main(String[] args) throws IOException {
		
		//1068C
		
		//only colors that are harmonic to each other can be connected. For example, if color 1 is harmonic to color 2, 2 is harmonic to 3, then that doesn't mean that 3 is harmonic to 1. 
		//in this example, 1 and 3 cannot be connected.
		
		//to solve, assign each color a row in the grid. Each connection will occupy a column in the grid. When making the connection, for example, color 1 and 2, then at column p, 
		//color the tile in the row assigned to color 1 to that color, and at color 2's row, do the same. If you use one column per connection, they will be isolated connections.
		
		//unconnected colors can be put into a big diagonal line at the other corner of the grid.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		ArrayList<ArrayList<Integer>> c = new ArrayList<ArrayList<Integer>>();
		ArrayList<ArrayList<int[]>> ans = new ArrayList<ArrayList<int[]>>();
		for(int i = 0; i < n; i++) {
			c.add(new ArrayList<Integer>());
			ans.add(new ArrayList<int[]>());
		}
		boolean[] v = new boolean[n];
		int pointer = 1;
		for(int i = 0; i < m; i++) {
			st = new StringTokenizer(fin.readLine());
			int a = Integer.parseInt(st.nextToken());
			int b = Integer.parseInt(st.nextToken());
			v[a - 1] = true;
			v[b - 1] = true;
			ans.get(a - 1).add(new int[] {pointer, a});
			ans.get(b - 1).add(new int[] {pointer, b});
			pointer ++;
		}
		pointer += 100000;
		for(int i = 0; i < n; i++) {
			if(!v[i]) {
				ans.get(i).add(new int[] {pointer, pointer});
				pointer ++;
			}
		}
		StringBuilder fout = new StringBuilder();
		for(int i = 0; i < ans.size(); i++) {
			fout.append(ans.get(i).size()).append("\n");
			for(int j = 0; j < ans.get(i).size(); j++) {
				int[] next = ans.get(i).get(j);
				fout.append(next[0]).append(" ").append(next[1]).append("\n");
			}
		}
		System.out.print(fout);
	}
}
