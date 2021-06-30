//package cowandsnacks;

import java.util.*;
import java.io.*;

public class cowandsnacks {
	public static void main(String[] args) throws IOException {
		
		//1209D
		
		//just do a floodfill through the graph. The number of edges required to travel through to visit all nodes is equal to the amount of people that you can satisfy. Subtract
		//that value from m to get the number of people that you cannot satisfy.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		boolean[] v = new boolean[n];
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
		int amtSatisfied = 0;
		for(int i = 0; i < n; i++) {
			if(!v[i]) {
				Queue<Integer> q = new ArrayDeque<Integer>();
				q.add(i);
				v[i] = true;
				while(q.size() != 0) {
					int cur = q.poll();
					for(int j = 0; j < c.get(cur).size(); j++) {
						int next = c.get(cur).get(j);
						if(!v[next]) {
							amtSatisfied ++;
							v[next] = true;
							q.add(next);
						}
					}
				}
			}
		}
		System.out.println(m - amtSatisfied);
	}
}
