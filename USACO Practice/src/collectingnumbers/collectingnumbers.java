//package collectingnumbers;

import java.util.*;
import java.io.*;

public class collectingnumbers {
	public static void main(String[] args) throws IOException {
		
		//CSES 2216
		
		//record the initial order of the number alongside the value, and sort ascending by value. 
		
		//when iterating along the sorted list, if order[i] > order[i + 1], it means that initially, the lesser number
		//was placed after the greater number, and thus we require an extra pass to get the next number. 
		
		//for every i where order[i] > order[i + 1], we need an extra pass.
		
		Kattio cin = new Kattio();
		int n = cin.nextInt();
		int[][] nums = new int[n][2];	//value, initial order
		for(int i = 0; i < n; i++) {
			nums[i][0] = cin.nextInt();
			nums[i][1] = i;
		}
		Arrays.sort(nums, (a, b) -> Integer.compare(a[0], b[0]));
		int ans = 1;
		int prev = nums[0][1];
		for(int i = 1; i < n; i++) {
			int next = nums[i][1];
			if(next < prev) {
				ans ++;
			}
			prev = next;
		}
		System.out.println(ans);
		cin.close();
	}
	
	static class Kattio extends PrintWriter {
		private BufferedReader r;
		private StringTokenizer st;
		// standard input
		public Kattio() { this(System.in, System.out); }
		public Kattio(InputStream i, OutputStream o) {
			super(o);
			r = new BufferedReader(new InputStreamReader(i));
		}
		// USACO-style file input
		public Kattio(String problemName) throws IOException {
			super(problemName + ".out");
			r = new BufferedReader(new FileReader(problemName + ".in"));
		}
		// returns null if no more input
		public String next() {
			try {
				while (st == null || !st.hasMoreTokens())
					st = new StringTokenizer(r.readLine());
				return st.nextToken();
			} catch (Exception e) { }
			return null;
		}
		public int nextInt() { return Integer.parseInt(next()); }
		public double nextDouble() { return Double.parseDouble(next()); }
		public long nextLong() { return Long.parseLong(next()); }
	}
}
