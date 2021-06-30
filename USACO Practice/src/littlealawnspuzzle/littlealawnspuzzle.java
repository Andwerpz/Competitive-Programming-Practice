//package littlealawnspuzzle;

import java.util.*;
import java.io.*;

public class littlealawnspuzzle {
	public static void main(String[] args) throws IOException {
		
		//1534C
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		long mod = 1000000007;
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			HashMap<Integer, Integer> dict = new HashMap<Integer, Integer>();
			StringTokenizer st = new StringTokenizer(fin.readLine());
			ArrayList<ArrayList<Integer>> c = new ArrayList<ArrayList<Integer>>();
			for(int i = 0; i < n; i++) {
				c.add(new ArrayList<Integer>());
				int next = Integer.parseInt(st.nextToken());
				dict.put(next, i);
			}
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				int next = Integer.parseInt(st.nextToken());
				int a = i;
				int b = dict.get(next);
				c.get(a).add(b);
				c.get(b).add(a);
			}
			int groups = 0;
			boolean[] v = new boolean[n];
			for(int i = 0; i < n; i++) {
				if(!v[i]) {
					groups ++;
					v[i] = true;
					Stack<Integer> s = new Stack<Integer>();
					s.push(i);
					while(s.size() != 0) {
						int cur = s.pop();
						for(int j = 0; j < c.get(cur).size(); j++) {
							int next = c.get(cur).get(j);
							if(!v[next]) {
								v[next] = true;
								s.push(next);
							}
						}
					}
				}
			}
			long ans = 1;
			for(int i = 0; i < groups; i++) {
				ans *= 2;
				ans %= mod;
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
