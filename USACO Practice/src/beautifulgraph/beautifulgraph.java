//package beautifulgraph;

import java.util.*;
import java.io.*;

public class beautifulgraph {
	public static void main(String[] args) throws IOException {
		
		//1093D
		
		//given a fully connected graph, notice that the graph must be bipartite for you to be able to assign values to nodes, making edge sums odd. This is because to make an odd number, you must
		//have an even and odd number. So the answer seems like 2 raised to the power of number of nodes in 1 bipartite section. But you need to remember that you can flip it, and assign odd numbers
		//to the other section. If you have multiple unconnected graphs inside the input, then you need to compute each graphs' answer separately, and multiply them together.
		
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
			int[] color = new int[n];
			Arrays.fill(color, -1);
			boolean isValid = true;
			long ans = 1;
			long mod = 998244353;
			boolean[] v = new boolean[n];
			ArrayList<Long> groups = new ArrayList<Long>();
			outer:
			for(int i = 0; i < n; i++) {
				if(!v[i]) {
					Stack<Integer> s = new Stack<Integer>();
					s.add(i);
					color[i] = 0;
					v[i] = true;
					int total = 0;
					int num0 = 0;
					while(s.size() != 0) {
						int cur = s.pop();
						if(color[cur] == 0) {
							num0 ++;
						}
						total ++;
						int nextColor = color[cur] == 0? 1 : 0;
						for(int j = 0; j < c.get(cur).size(); j++) {
							int next = c.get(cur).get(j);
							if(color[next] != nextColor && color[next] != -1) {
								isValid = false;
								break outer;
							}
							if(!v[next]) {
								s.add(next);
								v[next] = true;
								color[next] = nextColor;
							}
						}
					}
					//System.out.println(total + " " + num0);
					long sum0 = 1;
					long sum1 = 1;
					for(int j = 0; j < num0; j++) {
						sum0 *= 2;
						sum0 %= mod;
					}
					for(int j = 0; j < total - num0; j++) {
						sum1 *= 2;
						sum1 %= mod;
					}
					long curAns = sum0 + sum1;
					curAns %= mod;
					groups.add(curAns);
				}
			}
			if(isValid) {
				for(long i : groups) {
					ans *= i;
					ans %= mod;
				}
				fout.append(ans).append("\n");
			}
			else {
				fout.append("0\n");
			}
		}
		System.out.print(fout);
	}
}
