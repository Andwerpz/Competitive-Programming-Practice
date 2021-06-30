//package navigationsystem;

import java.util.*;
import java.io.*;

public class navigationsystem {
	public static void main(String[] args) throws IOException {
		
		//1320B
		
		//the solution is very long winded, either refer to tutorial, or to day 6/16/2021 in notebook.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		ArrayList<ArrayList<Integer>> c = new ArrayList<ArrayList<Integer>>();
		ArrayList<ArrayList<Integer>> cReverse = new ArrayList<ArrayList<Integer>>();	//use this one for dijkstra
		for(int i = 0; i < n; i++) {
			c.add(new ArrayList<Integer>());
			cReverse.add(new ArrayList<Integer>());
		}
		for(int i = 0; i < m; i++) {
			st = new StringTokenizer(fin.readLine());
			int a = Integer.parseInt(st.nextToken()) - 1;
			int b = Integer.parseInt(st.nextToken()) - 1;
			c.get(a).add(b);
			cReverse.get(b).add(a);
		}
		PriorityQueue<int[]> q = new PriorityQueue<int[]>((a, b) -> a[1] - b[1]);
		int k = Integer.parseInt(fin.readLine());
		int[] path = new int[k];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < k; i++) {
			path[i] = Integer.parseInt(st.nextToken()) - 1;
		}
		int[] minCost = new int[n];
		Arrays.fill(minCost, Integer.MAX_VALUE);
		minCost[path[k - 1]] = 0;
		q.add(new int[] {path[k - 1], 0});
		while(q.size() != 0) {
			int[] cur = q.poll();
			if(cur[1] > minCost[cur[0]]) {
				continue;
			}
			int nextCost = cur[1] + 1;
			int id = cur[0];
			for(int i = 0; i < cReverse.get(id).size(); i++) {
				int nextId = cReverse.get(id).get(i);
				if(minCost[nextId] > nextCost) {
					minCost[nextId] = nextCost;
					q.add(new int[] {nextId, nextCost});
				}
			}
		}
		int ansMin = 0;
		int ansMax = 0;
		for(int i = 0; i < k - 1; i++) {
			int cur = path[i];
			int min = Integer.MAX_VALUE;
			for(int j = 0; j < c.get(cur).size(); j++) {
				int next = c.get(cur).get(j);
				min = Math.min(min, minCost[next]);
			}
			for(int j = 0; j < c.get(cur).size(); j++) {
				int next = c.get(cur).get(j);
				if(next != path[i + 1] && minCost[next] == min) {
					ansMax ++;
					break;
				}
			}
			if(min != minCost[path[i + 1]]) {
				ansMin ++;
			}
		}
		System.out.println(ansMin + " " + ansMax);
	}
}
