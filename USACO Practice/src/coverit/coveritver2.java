package coverit;

import java.util.*;
import java.io.*;

public class coveritver2 {
	public static void main(String[] args) throws IOException {
		
		//1176E
		
		//Mike Mirzayanov is a genius.
		
		//The idea behind this is to generate the array of costs from one node to all nodes, and take the minimum out of the set of even and odd paths.
		//Since it is guaranteed for an even path node to be connected to an odd path node, if you select all nodes out of the minimum size subset,
		//then it is guaranteed that you will cover all nodes.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
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
			int[] costs = new int[n];
			boolean[] v = new boolean[n];
			ArrayDeque<Integer> q = new ArrayDeque<Integer>();
			ArrayDeque<Integer> cost = new ArrayDeque<Integer>();
			q.add(0);
			cost.add(0);
			v[0] = true;
			int even = 0;
			while(q.size() != 0) {
				int cur = q.poll();
				int curCost = cost.poll();
				if(curCost % 2 == 0) {
					even ++;
				}
				for(int i = 0; i < c.get(cur).size(); i++) {
					int next = c.get(cur).get(i);
					if(!v[next]) {
						costs[next] = curCost + 1;
						q.add(next);
						cost.add(curCost + 1);
						v[next] = true;
					}
				}
			}
			int ans = 0;
			if(even * 2 <= n) {
				ans = even;
				fout.append(ans).append("\n");
				for(int i = 0; i < n; i++) {
					if(costs[i] % 2 == 0) {
						fout.append(i + 1).append(" ");
					}
				}
				fout.append("\n");
			}
			else {
				ans = n - even;
				fout.append(ans).append("\n");
				for(int i = 0; i < n; i++) {
					if(costs[i] % 2 == 1) {
						fout.append(i + 1).append(" ");
					}
				}
				fout.append("\n");
			}
		}
		System.out.print(fout);
	}
}
