//package maximumdistributedtree;

import java.util.*;
import java.io.*;

public class maximumdistributedtree {
	public static void main(String[] args) throws IOException {
		
		//1401D
		
		//the number of paths running through a given edge is equal to the product of verticies from the two components when the given edge is removed.
		
		//to calculate for every edge in linear time, just look through verticies starting from the verticies with only one edge. 
		
		//if you have more factors than edges, then multiply the largest factors into the largest weighted edge. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		long mod = 1000000007;
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			ArrayList<ArrayList<Integer>> c = new ArrayList<ArrayList<Integer>>();
			long[] edgeCount = new long[n];
			for(int i = 0; i < n; i++) {
				c.add(new ArrayList<Integer>());
			}
			for(int i = 0; i < n - 1; i++) {
				StringTokenizer st = new StringTokenizer(fin.readLine());
				int a = Integer.parseInt(st.nextToken()) - 1;
				int b = Integer.parseInt(st.nextToken()) - 1;
				c.get(a).add(b);
				c.get(b).add(a);
			}
			boolean[] v = new boolean[n];
			ArrayList<Long> edges = new ArrayList<Long>();
			Queue<Integer> s = new ArrayDeque<Integer>();
			for(int i = 0; i < n; i++) {
				edgeCount[i] = c.get(i).size();
				if(edgeCount[i] == 1) {
					s.add(i);
					v[i] = true;
				}
			}
			//System.out.println(s);
			
			long[] prevNodes = new long[n];
			while(s.size() != 0) {
				int curNode = s.poll();
				long curVal = 1;
				for(int i = 0; i < c.get(curNode).size(); i++) {
					int nextNode = c.get(curNode).get(i);
					if(v[nextNode]) {
						curVal += prevNodes[nextNode];
					}
				}
				prevNodes[curNode] = curVal;
				//System.out.println("CUR NODE: " + curNode + " VAL: " + curVal);
				for(int i = 0; i < c.get(curNode).size(); i++) {
					int nextNode = c.get(curNode).get(i);
					if(prevNodes[nextNode] == 0) {
						edges.add(curVal * (n - curVal));
						edgeCount[nextNode] --;
						edgeCount[curNode] --;
					}
					if(!v[nextNode]) {
						
						if(edgeCount[nextNode] == 1) {
							v[nextNode] = true;
							s.add(nextNode);
						}	
					}
				}
			}
//			System.out.println(edges);
//			for(int i : prevNodes) {
//				System.out.print(i + " ");
//			}
//			System.out.println();
			int m = Integer.parseInt(fin.readLine());
			Long[] factors = new Long[m];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < m; i++) {
				factors[i] = Long.parseLong(st.nextToken());
			}
			Arrays.sort(factors);
			edges.sort((a, b) -> Long.compare(a, b));
			int pointer = m - 1;
			long ans = 0;
			for(int i = edges.size() - 1; i >= 0; i--) {
				long nextFactor = 1;
				if(pointer != -1) {
					nextFactor = factors[pointer];
					pointer --;
				}
				while(pointer != -1 && pointer >= i) {
					nextFactor *= factors[pointer];
					nextFactor %= mod;
					pointer --;
				}
				ans += ((long) edges.get(i)) * nextFactor;
				ans %= mod;
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
