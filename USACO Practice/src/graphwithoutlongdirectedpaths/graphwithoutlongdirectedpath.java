//package graphwithoutlongdirectedpaths;

import java.util.*;
import java.io.*;

public class graphwithoutlongdirectedpath {
	public static void main(String[] args) throws IOException {
		
		//1144F
		
		//simple AB coloring graph problem. For example, if you're colored red, then all edges connected to you are outbound, and if you're blue then
		//all edges connected to you are inbound. You can easily see that all path lengths will be exactly one edge long; they all end at blue nodes.
		//you can easily see that you can't use more than one color, since then you're risking having a path that is more than 1 edge long.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int[][] edges = new int[m][2];
		ArrayList<ArrayList<Integer>> c = new ArrayList<ArrayList<Integer>>();
		for(int i = 0; i < n; i++) {
			c.add(new ArrayList<Integer>());
		}
		for(int i = 0; i < m; i++) {
			st = new StringTokenizer(fin.readLine());
			int a = Integer.parseInt(st.nextToken()) - 1;
			int b = Integer.parseInt(st.nextToken()) - 1;
			c.get(a).add(b);
			c.get(b).add(a);
			edges[i] = new int[] {a, b};
		}
		int[] color = new int[n];
		Arrays.fill(color, -1);
		color[0] = 0;
		ArrayDeque<Integer> q = new ArrayDeque<Integer>();
		q.add(0);
		boolean isValid = true;
		outer:
		while(q.size() != 0) {
			int cur = q.poll();
			int nextColor = color[cur] == 0? 1 : 0;
			for(int i = 0; i < c.get(cur).size(); i++) {
				int next = c.get(cur).get(i);
				if(color[next] == -1) {
					color[next] = nextColor;
					q.add(next);
				}
				else if(color[next] != -1 && color[next] != nextColor) {
					isValid = false;
					break outer;
				}
			}
		}
		if(isValid) {
			StringBuilder fout = new StringBuilder();
			fout.append("YES\n");
			for(int i = 0; i < m; i++) {
				fout.append(color[edges[i][0]]);
			}
			System.out.println(fout);
		}
		else {
			System.out.println("NO");
		}
	}
}
