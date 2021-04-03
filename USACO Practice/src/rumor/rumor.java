//package rumor;

import java.util.*;
import java.io.*;

public class rumor {
	public static void main(String[] args) throws IOException{
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int[] cost = new int[n];
		ArrayList<ArrayList<Integer>> connections = new ArrayList<ArrayList<Integer>>();
		
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			cost[i] = Integer.parseInt(st.nextToken());
			connections.add(new ArrayList<Integer>());
		}
		
		for(int i = 0; i < m; i++) {
			st = new StringTokenizer(fin.readLine());
			int a = Integer.parseInt(st.nextToken()) - 1;
			int b = Integer.parseInt(st.nextToken()) - 1;
			connections.get(a).add(b);
			connections.get(b).add(a);
		}
		
		ArrayList<ArrayList<Integer>> groups = new ArrayList<ArrayList<Integer>>();
		boolean[] visited = new boolean[n];
		
		for(int i = 0; i < n; i++) {
			if(!visited[i]) {
				ArrayList<Integer> curGroup = new ArrayList<Integer>();
				curGroup.add(i);
				Stack<Integer> s = new Stack<Integer>();
				s.add(i);
				visited[i] = true;
				while(s.size() != 0) {
					int cur = s.pop();
					ArrayList<Integer> con = connections.get(cur);
					for(int j = 0; j < con.size(); j++) {
						if(!visited[con.get(j)]) {
							visited[con.get(j)] = true;
							s.add(con.get(j));
							curGroup.add(con.get(j));
						}
					}
				}
				groups.add(curGroup);
			}
		}
		
		long sum = 0;
		
		for(int i = 0; i < groups.size(); i++) {
			int min = Integer.MAX_VALUE;
			for(int j = 0; j < groups.get(i).size(); j++) {
				if(cost[groups.get(i).get(j)] < min) {
					min = cost[groups.get(i).get(j)];
				}
			}
			sum += min;
		}
		System.out.println(sum);
	}
}
