//package maximumwhitesubtree;

import java.util.*;
import java.io.*;

public class maximumwhitesubtree {
	
	static ArrayList<ArrayList<Integer>> c;
	
	public static void main(String[] args) throws IOException {
		
		//1324F
		
		//the technique is called "rerooting" apparently
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		int[] colors = new int[n];
		c = new ArrayList<ArrayList<Integer>>();
		int[][] order = new int[n][2];	//orders the nodes based on how many ancestors they have
		for(int i = 0; i < n; i++) {
			c.add(new ArrayList<Integer>());
			order[i][1] = i;
			order[i][0] = -1;
		}
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			int next = Integer.parseInt(st.nextToken());
			colors[i] = next == 0? -1 : 1;
		}
		for(int i = 0; i < n - 1; i++) {
			st = new StringTokenizer(fin.readLine());
			int a = Integer.parseInt(st.nextToken()) - 1;
			int b = Integer.parseInt(st.nextToken()) - 1;
			c.get(a).add(b);
			c.get(b).add(a);
		}
		Stack<Integer> s = new Stack<Integer>();
		boolean[] v = new boolean[n];
		v[0] = true;
		s.add(0);
		order[0][0] = 0;
		while(s.size() != 0) {
			int next = s.pop();
			int curCost = order[next][0];
			for(int i = 0; i < c.get(next).size(); i++) {
				if(!v[c.get(next).get(i)]) {
					order[c.get(next).get(i)][0] = curCost + 1;
					v[c.get(next).get(i)] = true;
					s.add(c.get(next).get(i));
				}
			}
		}
		for(boolean i : v) {
			if(!i) {
				System.out.println("DIDNT VISIT ALL");
			}
		}
//		if(n == 100) {
//			for(int[] i : order) {
//				System.out.print(i[0] + " ");
//			}
//			System.out.println();
//		}
		
		int[] maxOfChildren = new int[n];	//max difference 
		Arrays.sort(order, (a, b) -> a[0] - b[0]);
		for(int i = n - 1; i >= 0; i--) {
			int next = order[i][1];
			boolean hasChildren = true;
			int max = colors[next];
			////System.out.println("CUR NODE: " + next);
			////System.out.println("START MAX: " + max);
			if(hasChildren) {
				int numAncestors = order[next][0];
				for(int j = 0; j < c.get(next).size(); j++) {
					int id = c.get(next).get(j);
					if(order[id][0] > numAncestors && maxOfChildren[id] > 0) {
						max += maxOfChildren[id];
					}
				}
			}
			maxOfChildren[next] = max;
			////System.out.println("MAX OF CHILDREN: " + next + " " + maxOfChildren[next]);
		}
		if(n == 100) {
			for(int i : maxOfChildren) {
				System.out.print(i + " ");
			}
			System.out.println();
		}
		int[] ans = new int[n];	//maximum difference of subtree that contains this node
		for(int i = 0; i < n; i++) {
			int next = order[i][1];
			//System.out.println("CUR NODE: " + next);
			if(i == 0) {
				ans[next] = maxOfChildren[i];
			}
			else {
				int parentId = -1;
				for(int j = 0; j < c.get(next).size(); j++) {
					int id = c.get(next).get(j);
					//System.out.println("COMPARE: " + order[id][0] + " " + order[next][0]);
					if(order[id][0] < order[next][0]) {
						if(parentId == -1) {
							parentId = id;
						}
						else {
							System.out.println("INVALID");
						}
					}
				}
				//System.out.println("PARENT: " + parentId);
				int curAns = Math.max(ans[parentId] + (maxOfChildren[next] == -1? -1 : 0), maxOfChildren[next]);
				//System.out.println("TEST: " + (ans[parentId] + (maxOfChildren[next] == -1? -1 : 0)));
				ans[next] = curAns;
			}
			//System.out.println("ANS: " + ans[next]);
		}
		StringBuilder fout = new StringBuilder();
		for(int i = 0; i < n; i++) {
			fout.append(ans[i]).append(" ");
		}
		System.out.println(fout);
	}
}
