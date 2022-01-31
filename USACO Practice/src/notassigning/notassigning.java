//package notassigning;

import java.util.*;
import java.io.*;

public class notassigning {
	public static void main(String[] args) throws IOException {
		
		//1627C
		
		//notice that you can repeat primes.
		
		//since the maximum length of path you have to consider is 2, you can just repeat two primes, 2 and 3. 
		
		//notice that if a node has more than 2 children, then you won't ever be able to label the edges in a way that satisfies
		//the constraints. 
		
		//so, the only shape the tree can make is a line or a chain. And to label, just alternate between 2 and 3. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			boolean isValid = true;
			int start = -1;
			ArrayList<ArrayList<Integer>> c = new ArrayList<ArrayList<Integer>>();
			for(int i = 0; i < n; i++) {
				c.add(new ArrayList<Integer>());
			}
			HashMap<ArrayList<Integer>, Integer> order = new HashMap<ArrayList<Integer>, Integer>();
			for(int i = 0; i < n - 1; i++) {
				StringTokenizer st = new StringTokenizer(fin.readLine());
				int a = Integer.parseInt(st.nextToken()) - 1;
				int b = Integer.parseInt(st.nextToken()) - 1;
				order.put(new ArrayList<Integer>(Arrays.asList(a, b)), i);
				c.get(a).add(b);
				c.get(b).add(a);
				if((c.get(a).size() == 3 || c.get(b).size() == 3) && isValid) {
					isValid = false;
				}
			}
			if(!isValid) {
				fout.append("-1\n");
				continue;
			}
			//locate the start of the chain
			for(int i = 0; i < n; i++) {
				if(c.get(i).size() == 1) {
					start = i;
					break;
				}
			}
			int[] ans = new int[n - 1];
			int cur = start;
			int next = c.get(start).get(0);
			int prime = 2;
			while(true) {
				int index = 0;
				if(order.containsKey(new ArrayList<Integer>(Arrays.asList(cur, next)))) {
					index = order.get(new ArrayList<Integer>(Arrays.asList(cur, next)));
				}
				else {
					index = order.get(new ArrayList<Integer>(Arrays.asList(next, cur)));
				}
				ans[index] = prime;
				if(c.get(next).size() == 1) {
					break;
				}
				prime = prime == 3? 2 : 3;
				int prev = cur;
				cur = next;
				next = c.get(cur).get(0) == prev? c.get(cur).get(1) : c.get(cur).get(0);
			}
			for(int i : ans) {
				fout.append(i).append(" ");
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
