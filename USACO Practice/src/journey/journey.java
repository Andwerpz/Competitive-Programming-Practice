//package journey;

import java.util.*;
import java.io.*;

public class journey {
	public static void main(String[] args) throws IOException {
		
		//1476D
		
		//first, notice that this situation can be represented by a graph. For even days, you have all the cities connected with the starting directions, and the odd days have opposite directions.
		//you just need two graphs, and connect the even day cities with the odd day cities. The first observation is that if you can get to a city, you can always return to the original
		//city. This means that it's transformed from a directed graph to a undirected graph. Then, it's easy to implement solution. For each node, just floodfill until you cant
		//reach anymore cities. The number of cities you can reach is the answer for that node, and any other node in the reached set.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			char[] s = fin.readLine().toCharArray();
			int[] ans = new int[n + 1];
			ArrayList<ArrayList<Integer>> c1 = new ArrayList<ArrayList<Integer>>();
			ArrayList<ArrayList<Integer>> c2 = new ArrayList<ArrayList<Integer>>();
			for(int i = 0; i < n + 1; i++) {
				c1.add(new ArrayList<Integer>());
				c2.add(new ArrayList<Integer>());
			}
			for(int i = 0; i < n; i++) {
				if(s[i] == 'R') {
					c1.get(i).add(i + 1);
					c2.get(i + 1).add(i);
				}
				else {
					c1.get(i + 1).add(i);
					c2.get(i).add(i + 1);
				}
			}
//			System.out.println(c1);
//			System.out.println(c2);
			boolean[] v = new boolean[n + 1];
			boolean[] v2 = new boolean[n + 1];
			for(int i = 0; i < n + 1; i++) {
				if(!v[i]) {
					ArrayDeque<Integer> q = new ArrayDeque<Integer>();
					ArrayDeque<Integer> w = new ArrayDeque<Integer>(); //w = which. 0 for c1, 1 for c2
					HashSet<Integer> group = new HashSet<Integer>();
					int numVisited = 0;
					group.add(i);
					v[i] = true;
					q.push(i);
					w.push(0);
					while(q.size() != 0) {
						numVisited ++;
						int id = q.poll();
						int which = w.poll();
						if(which == 0) {
							for(int j = 0; j < c1.get(id).size(); j++) {
								int nextId = c1.get(id).get(j);
								if(!v2[nextId]) {
									v2[nextId] = true;
									q.push(nextId);
									w.push(1);
								}
							}
						}
						else {
							for(int j = 0; j < c2.get(id).size(); j++) {
								int nextId = c2.get(id).get(j);
								if(!v[nextId]) {
									group.add(nextId);
									v[nextId] = true;
									q.push(nextId);
									w.push(0);
								}
							}
						}
					}
					for(int j : group) {
						ans[j] = numVisited;
					}
				}
			}
			for(int i : ans) {
				fout.append(i).append(" ");
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
