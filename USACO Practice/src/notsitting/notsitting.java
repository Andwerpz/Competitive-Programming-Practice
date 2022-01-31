//package notsitting;

import java.util.*;
import java.io.*;

public class notsitting {
	
	public static int dist(int x1, int y1, int x2, int y2) {
		return Math.abs(x1 - x2) + Math.abs(y1 - y2);
	}
	
	public static int maxDist(int n, int m, int r, int c) {
		return Math.max(Math.max(dist(0, 0, r, c), dist(n, m, r, c)), Math.max(dist(n, 0, r, c), dist(0, m, r, c)));
	}
	
	public static void main(String[] args) throws IOException {
		
		//1627B
		
		//Notice that Rahul gets to pick where to sit first. This means that rahul wants to minimize the maximum distance to any
		//chair in the grid. 
		
		//So in order to maximize distance, all tina needs to do is to paint the center chairs pink. For each tile, calculate the maximum 
		//distance to any chair, and then greedily color the ones that have the minimum max dist. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());
			ArrayList<Integer> ans = new ArrayList<Integer>();
			for(int i = 0; i < n; i++) {
				for(int j = 0; j < m; j++) {
					ans.add(maxDist(n - 1, m - 1, i, j));
				}
			}
			ans.sort((a, b) -> Integer.compare(a, b));
			for(int i = 0; i < ans.size(); i++) {
				fout.append(ans.get(i)).append(" ");
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
