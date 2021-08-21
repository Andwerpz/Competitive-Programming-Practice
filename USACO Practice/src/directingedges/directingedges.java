//package directingedges;

import java.util.*;
import java.io.*;

public class directingedges {
	public static void main(String[] args) throws IOException {
		
		//1385E
		
		//first, given the directed edges, you need to find out whether there are any cycles in the graph already. To do this, just make a topological sort of the graph, starting from the nodes
		//that don't have any outgoing edges. From there it is easy to check for cycles. If there are no nodes with no outgoing edges, and directed edges do exist, then there must be a cycle as well.
		
		//If there are no cycles already in the graph, then it is guaranteed that you can direct the remaining edges to make a graph with no cycles. Just utilize the topological sort, and always direct the edges
		//towards the greater or the lesser node.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());
			ArrayList<int[]> directed = new ArrayList<int[]>();
			boolean[] v = new boolean[n];
			ArrayList<ArrayList<Integer>> c = new ArrayList<ArrayList<Integer>>();
			ArrayList<ArrayList<Integer>> cReverse = new ArrayList<ArrayList<Integer>>();
			boolean[] noOutgoing = new boolean[n];
			Arrays.fill(noOutgoing, true);
			ArrayList<int[]> undirected = new ArrayList<int[]>();
			for(int i = 0; i < n; i++) {
				c.add(new ArrayList<Integer>());
				cReverse.add(new ArrayList<Integer>());
			}
			for(int i = 0; i < m; i++) {
				st = new StringTokenizer(fin.readLine());
				int which = Integer.parseInt(st.nextToken());
				int a = Integer.parseInt(st.nextToken()) - 1;
				int b = Integer.parseInt(st.nextToken()) - 1;
				if(which == 0) {	//undirected
					undirected.add(new int[] {a, b});
				}
				else {	//directed
					directed.add(new int[] {a, b});
					c.get(a).add(b);
					cReverse.get(b).add(a);
					noOutgoing[a] = false;
				}
			}
			boolean isValid = true;
			int[] priority = new int[n];
			int pointer = 0;
			int[] numC = new int[n];
			for(int i = 0; i < n; i++) {
				numC[i] = c.get(i).size();
			}
			Arrays.fill(priority, -1);
			for(int i = 0; i < n; i++) {
				if(noOutgoing[i]) {
					Stack<Integer> s = new Stack<Integer>();
					s.add(i);
					priority[i] = pointer;
					pointer ++;
					while(s.size() != 0) {
						int cur = s.pop();
						priority[cur] = pointer;
						pointer ++;
						for(int j = 0; j < cReverse.get(cur).size(); j++) {
							int next = cReverse.get(cur).get(j);
							numC[next] --;
							if(numC[next] == 0) {
								s.add(next);
							}
						}
					}
				}
			}
			for(int i = 0; i < directed.size(); i++) {
				int a = directed.get(i)[0];
				int b = directed.get(i)[1];
				if(priority[a] == -1 || priority[b] == -1) {
					isValid = false;
					break;
				}
				if(priority[a] < priority[b]) {
					isValid = false;
					break;
				}
			}
			if(!isValid) {
				fout.append("NO\n");
			}
			else {
				fout.append("YES\n");
				for(int i = 0; i < undirected.size(); i++) {
					int[] next = undirected.get(i);
					int a = next[0];
					int b = next[1];
					if(priority[a] == -1) {
						priority[a] = pointer;
						pointer ++;
					}
					if(priority[b] == -1) {
						priority[b] = pointer;
						pointer ++;
					}
					if(priority[a] < priority[b]) {
						fout.append(b + 1).append(" ").append(a + 1);
					}
					else {
						fout.append(a + 1).append(" ").append(b + 1);
					}
					fout.append("\n");
				}
				for(int i = 0; i < directed.size(); i++) {
					fout.append(directed.get(i)[0] + 1).append(" ").append(directed.get(i)[1] + 1).append("\n");
				}
			}
		}
		System.out.print(fout);
	}
}
