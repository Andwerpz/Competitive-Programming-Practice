//package inversiongraph;

import java.util.*;
import java.io.*;

public class inversiongraph {
	public static void main(String[] args) throws IOException {
		
		//1638C
		
		//you can solve this with one pass
		
		//start at a[0]. notice that a[0] is connected to everything to its left that is less than a[0]. 
		
		//find the last number that a[0] is connected to. This is a[x]. If there is a number that is bigger than a[0]
		//between a[x] and a[0], call it a[y], a[0] has to be connected to a[y], since a[y] is also connected to a[x]. 
		
		//so to solve, start with a[0], and look for bigger numbers. If the next number greater than a[0] occurs after a[x], then
		//it is a new connected component, otherwise, a[0] can be considered equal to a[y], and keep looking. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			HashSet<Integer> v = new HashSet<Integer>();
			int max = 0;
			int ans = 0;
			for(int i = 0; i < n; i++) {
				int next = Integer.parseInt(st.nextToken());
				if(next > max) {
					if(v.size() == 0) {
						ans ++;
					}
					for(int j = max + 1; j < next; j++) {
						v.add(j);
					}
					max = next;
				}
				else {
					v.remove(next);
				}
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
