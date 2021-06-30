//package spanningtreewithmaximumdegree;

import java.util.*;
import java.io.*;

public class spanningtreewithmaximumdegree {
	public static void main(String[] args) throws IOException {
		
		//1133F1
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
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
		}
		int max = 0;
		int maxNode = 0;
		for(int i = 0; i < n; i++) {
			if(c.get(i).size() > max) {
				max = c.get(i).size();
				maxNode = i;
			}
		}
		StringBuilder fout = new StringBuilder();
		Queue<Integer> q = new ArrayDeque<Integer>();
		boolean[] v = new boolean[n];
		q.add(maxNode);
		v[maxNode] = true;
		//System.out.println(maxNode);
		while(q.size() != 0) {
			int cur = q.poll();
			for(int i = 0; i < c.get(cur).size(); i++) {
				int next = c.get(cur).get(i);
				if(!v[next]) {
					v[next] = true;
					fout.append(cur + 1).append(" ").append(next + 1).append("\n");
					q.add(next);
				}
			}
		}
		System.out.print(fout);
	}
}
