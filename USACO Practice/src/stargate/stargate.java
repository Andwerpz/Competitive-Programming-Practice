package stargate;

import java.util.*;
import java.io.*;

public class stargate {
	public static void main(String[] args) throws IOException {
		
		//2021 Keep Austin Hacking
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		ArrayList<ArrayList<int[]>> c = new ArrayList<ArrayList<int[]>>();
		for(int i = 0; i < n; i++) {
			c.add(new ArrayList<int[]>());
		}
		for(int i = 0; i < m; i++) {
			st = new StringTokenizer(fin.readLine());
			int a = Integer.parseInt(st.nextToken()) - 1;
			int b = Integer.parseInt(st.nextToken()) - 1;
			int t = Integer.parseInt(st.nextToken());
			c.get(a).add(new int[] {b, t});
			c.get(b).add(new int[] {a, t});
		}
		boolean[][] nodes = new boolean[n][2];	//0 for visitable by 1, 1 for visitable by n
		Stack<Integer> s = new Stack<Integer>();
		boolean[] v = new boolean[n];
		v[0] = true;
		s.add(0);
		while(s.size() != 0) {
			int cur = s.pop();
			for(int i = 0; i < c.get(cur).size(); i++) {
				int[] next = c.get(cur).get(i);
				if(next[1] != 0 && !v[next[0]]) {
					v[next[0]] = true;
					s.push(next[0]);
					nodes[next[0]][0] = true;
				}
			}
		}
		if(v[n - 1]) {
			System.out.println("YES");
		}
		else {
			s = new Stack<Integer>();
			v[n - 1] = true;
			s.add(n - 1);
			while(s.size() != 0) {
				int cur = s.pop();
				for(int i = 0; i < c.get(cur).size(); i++) {
					int[] next = c.get(cur).get(i);
					if(next[1] != 0 && !v[next[0]]) {
						v[next[0]] = true;
						s.push(next[0]);
						nodes[next[0]][1] = true;
					}
				}
			}
			boolean isValid = false;
			outer:
			for(int i = 0; i < n; i++) {
				if(nodes[i][0]) {
					int cur = i;
					for(int j = 0; j < c.get(cur).size(); j++) {
						int next = c.get(cur).get(j)[0];
						if(nodes[next][1]) {
							isValid = true;
							break outer;
						}
					}
				}
			}
			System.out.println(isValid? "YES" : "NO");
		}
	}
}
