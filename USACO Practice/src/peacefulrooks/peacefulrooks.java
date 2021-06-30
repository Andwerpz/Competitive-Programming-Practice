//package peacefulrooks;

import java.util.*;
import java.io.*;

public class peacefulrooks {
	public static void main(String[] args) throws IOException {
		
		//1411C
		
		//if a rook is already on the main diag, then it requires no moves
		//if a rook can go directly to a main diag spot, then it requires only 1 move. 
		//if a rook can move to a main diag spot, but if moving there makes it under attack by another rook, see if that other rook can move to a main diag spot. If they form a chain
		//where the last one can move to a diag spot, then each rook only requires one move. 
		//if the rooks in the chain form a loop, where the last one in the chain is blocked by the first one, then you can fix this by moving one of the rooks in the chain to the empty spot
		//given to you by the problem constraints; m < n. From there, all rooks only need 1 move to get to a main diag spot.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());
			int ans = 0;
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
			boolean[] v = new boolean[n];
			for(int i = 0; i < n; i++) {
				if(!v[i]) {
					if(c.get(i).size() == 2 && c.get(i).get(0) == i) {
						//System.out.println("CINT");
						continue;
					}
					int group = 1;
					boolean loop = false;
					ArrayDeque<Integer> q = new ArrayDeque<Integer>();
					ArrayDeque<Integer> p = new ArrayDeque<Integer>();
					q.add(i);
					p.add(-1);
					v[i] = true;
					while(q.size() != 0) {
						int cur = q.poll();
						int prev = p.poll();
						for(int j = 0; j < c.get(cur).size(); j++) {
							int next = c.get(cur).get(j);
							if(next != prev) {
								if(v[next]) {
									loop = true;
									break;
								}
								else {
									q.add(next);
									p.add(cur);
									v[next] = true;
									group ++;
								}
							}
						}
					}
					ans += group + (loop? 2 : 0) - 1;
				}
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
