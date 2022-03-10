package countingshortcuts;

import java.util.*;
import java.io.*;

public class countingshortcuts {
	
	public static int find(ArrayList<ArrayList<Integer>> c, int s, int f) {	//find length of shortest path from s to f
		boolean[] v = new boolean[c.size()];
		int counter = 0;
		Queue<Integer> q = new ArrayDeque<>();
		q.add(s);
		v[s] = true;
		while(true) {
			counter ++;
			ArrayList<Integer> nextQ = new ArrayList<Integer>();
			while(q.size() != 0) {
				int next = q.poll();
				for(int i : c.get(next)) {
					if(!v[i]) {
						v[i] = true;
						nextQ.add(i);
					}
				}
			}
			if(v[f]) {
				break;
			}
			q.addAll(nextQ);
		}
		return counter;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1650G
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			fin.readLine();
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());
			st = new StringTokenizer(fin.readLine());
			int s = Integer.parseInt(st.nextToken()) - 1;
			int f = Integer.parseInt(st.nextToken()) - 1;
			ArrayList<ArrayList<Integer>> c = new ArrayList<ArrayList<Integer>>();
			for(int i = 0; i < n; i++) {
				c.add(new ArrayList<Integer>());
			}
			for(int i = 0; i < m; i++) {
				st = new StringTokenizer(fin.readLine());
				int u = Integer.parseInt(st.nextToken()) - 1;
				int v = Integer.parseInt(st.nextToken()) - 1;
				c.get(u).add(v);
				c.get(v).add(u);
			}
			int pathLen = find(c, s, f);
			System.out.println(pathLen);
			long ans = 0;
			long mod = (long) 1e9 + 7l;
			HashSet<Integer> q = new HashSet<>();	//shortest path
			boolean[] v = new boolean[n];
			v[s] = true;
			q.add(s);
			long[] val = new long[n];
			val[s] = 1;
			HashSet<Integer> qp1 = new HashSet<>();
			boolean[] vp1 = new boolean[n];
			vp1[s] = true;
			long[] valp1 = new long[n];
			for(int i = 0; i < pathLen; i++) {
				ArrayList<Integer> nextQ = new ArrayList<Integer>();
				ArrayList<Integer> nextQp1 = new ArrayList<>();
				long[] nextVal = new long[n];
				for(int next : q) {
					for(int j : c.get(next)) {
						if(!v[j] || q.contains(j)) {
							v[j] = true;
							nextQ.add(j);
							nextVal[j] += val[next];
							nextVal[j] %= mod;
						}
//						else if(q.contains(j)) {
//							vp1[j] = true;
//							qp1.add(j);
//							valp1[j] += val[next];
//							valp1[j] %= mod;
//						}
					}
				}
				for(int j = 0; j < n; j++) {
					val[j] = nextVal[j];
				}
				System.out.println(q);
				q.clear();
				q.addAll(nextQ);
//				for(int next : qp1) {
//					for(int j : c.get(next)) {
//						if(!vp1[j]) {
//							vp1[j] = true;
//							nextQp1.add(j);
//							valp1[j] += valp1[next];
//							valp1[j] %= mod;
//						}
//					}
//				}
//				qp1.clear();
//				qp1.addAll(nextQp1);
				
//				for(long j : valp1) {
//					System.out.print(j + " ");
//				}
//				System.out.println("\n");
			}
			for(long j : val) {
				System.out.print(j + " ");
			}
			System.out.println();
			for(int i : c.get(f)) {
				ans += val[i];
				ans %= mod;
			}
			ans += val[f];
			ans %= mod;
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
