//package crosscoloring;

import java.util.*;
import java.io.*;

public class crosscoloring {
	public static void main(String[] args) throws IOException {
		
		//1644D
		
		//let the number of unique colors on the board = a. Then, the answer is k ^ a. 
		
		//really, we need to know the number of operations with cells that aren't covered by other operations. 
		
		//the easiest way to compute this is to process the queries backwards. When we try a query, all we are asking is if
		//there exists a white cell in the same row or column of the target cell. 
		
		//to do this, we can maintain a set of colored rows and columns. There are 3 cases where a query doesn't have any white cells:
		//1. both the row and column it is in have been colored
		//2. all rows have been colored
		//3. all columns have been colored
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());
			int k = Integer.parseInt(st.nextToken());
			int q = Integer.parseInt(st.nextToken());
			long mod = 998244353;
			int[][] ops = new int[q][2];
			for(int i = 0; i < q; i++) {
				st = new StringTokenizer(fin.readLine());
				ops[i][0] = Integer.parseInt(st.nextToken()) - 1;
				ops[i][1] = Integer.parseInt(st.nextToken()) - 1;
			}
			HashSet<Integer> r = new HashSet<Integer>();
			HashSet<Integer> c = new HashSet<Integer>();
			//System.out.println(r + " " + c);
			long ans = 1;
			for(int i = q - 1; i >= 0; i--) {
				int nextR = ops[i][0];
				int nextC = ops[i][1];
				//System.out.println(nextR + " " + nextC);
				if(r.size() == n || c.size() == m || (r.contains(nextR) && c.contains(nextC))) {
					continue;
				}
				r.add(nextR);
				c.add(nextC);
				ans *= (long) k;
				ans %= mod;
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
