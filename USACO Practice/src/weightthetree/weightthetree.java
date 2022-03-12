//package weightthetree;

import java.util.*;
import java.io.*;

public class weightthetree {
	public static void main(String[] args) throws IOException {
		
		//1646D
		
		//coloring the tree bipartite gives you the correct amount of good nodes, but it doesn't give
		//you the minimum weight.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		ArrayList<ArrayList<Integer>> c = new ArrayList<ArrayList<Integer>>();
		for(int i = 0; i < n; i++) {
			c.add(new ArrayList<Integer>());
		}
		for(int i = 0; i < n - 1; i++) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int u = Integer.parseInt(st.nextToken()) - 1;
			int v = Integer.parseInt(st.nextToken()) - 1;
			c.get(u).add(v);
			c.get(v).add(u);
		}
		if(n == 2) {
			System.out.println("2 2");
			System.out.println("1 1");
			return;
		}
		int[] color = new int[n];	//1 or 2
		Stack<Integer> s = new Stack<Integer>();
		s.add(0);
		color[0] = 1;
		int num1 = 0;
		while(s.size() != 0) {
			int next = s.pop();
			int curColor = color[next];
			if(curColor == 1) {
				num1 ++;
			}
			for(int i : c.get(next)) {
				if(color[i] == 0) {
					color[i] = curColor == 1? 2 : 1;
					s.add(i);
				}
			}
		}
		int goodColor = num1 >= n - num1? 1 : 2;
		int sum = 0;
		for(int i = 0; i < n; i++) {
			sum += color[i] == goodColor? c.get(i).size() : 1;
		}
		StringBuilder fout = new StringBuilder();
		fout.append(Math.max(num1, n - num1)).append(" ").append(sum).append("\n");
		for(int i = 0; i < n; i++) {
			fout.append(color[i] == goodColor? c.get(i).size() : 1).append(" ");
		}
		System.out.println(fout);
	}
}
