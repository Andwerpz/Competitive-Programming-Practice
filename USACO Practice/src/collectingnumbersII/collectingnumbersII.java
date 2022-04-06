//package collectingnumbersII;

import java.util.*;
import java.io.*;

public class collectingnumbersII {
	public static int getDiff(int[][] nums, int u, int v) {
		if(Math.abs(u - v) == 1) {	//u and v are next to each other
			int initial = 0;
			int after = 0;
			int prev = nums[Math.max(0, Math.min(u, v) - 1)][1];
			for(int i = Math.max(0, Math.min(u, v) - 1); i <= Math.min(nums.length - 1, Math.max(u, v) + 1); i++) {
				int next = nums[i][1];
				if(next < prev) {
					initial ++;
				}
				prev = next;
			}
			prev = nums[Math.max(0, Math.min(u, v) - 1)][1];
			if(prev == nums[u][1]) {
				prev = nums[v][1];
			}
			else if(prev == nums[v][1]) {
				prev = nums[u][1];
			}
			for(int i = Math.max(0, Math.min(u, v) - 1); i <= Math.min(nums.length - 1, Math.max(u, v) + 1); i++) {
				int next = nums[i][1];
				if(i == u) {
					next = nums[v][1];
				}
				else if(i == v) {
					next = nums[u][1];
				}
				//System.out.print(next + " ");
				if(next < prev) {
					//System.out.println("YES");
					after ++;
				}
				prev = next;
			}
			//System.out.println();
			//System.out.println(initial + " " + after);
			return after - initial;
		}
		else {
			int diff = 0;
			int iu = nums[u][1];
			int au = nums[v][1];
			int iv = nums[v][1];
			int av = nums[u][1];
			
			if(u - 1 >= 0) {
				int next = nums[u - 1][1];
				if(iu > next && au < next) {
					diff ++;
				}
				else if(iu < next && au > next) {
					diff --;
				}
			}
			if(u + 1 < nums.length) {
				int next = nums[u + 1][1];
				if(iu > next && au < next) {
					diff --;
				}
				else if(iu < next && au > next) {
					diff ++;
				}
			}
			if(v - 1 >= 0) {
				int next = nums[v - 1][1];
				if(iv > next && av < next) {
					diff ++;
				}
				else if(iv < next && av > next) {
					diff --;
				}
			}
			if(v + 1 < nums.length) {
				int next = nums[v + 1][1];
				if(iv > next && av < next) {
					diff --;
				}
				else if(iv < next && av > next) {
					diff ++;
				}
			}
			return diff;
		}
	}
	
	public static void main(String[] args) throws IOException {
		
		//CSES 2217
		
		//the trick is to first compute the amount of passes required, then modify the amount based on the number swaps
		
		//notice that when you replace a number with another number, you only need to check the numbers adjacent to it
		//in order to update the value. So each swap can be computed in constant time
		
		FastIO cin = new FastIO();
		int n = cin.nextInt();
		int m = cin.nextInt();
		int[][] nums = new int[n][2];	//value, initial order
		for(int i = 0; i < n; i++) {
			nums[i][0] = cin.nextInt();
			nums[i][1] = i;
		}
		int[] map = new int[n]; 	//init order, index
		Arrays.sort(nums, (a, b) -> Integer.compare(a[0], b[0]));
		int ans = 1;
		int prev = nums[0][1];
		map[nums[0][1]] = 0;
		for(int i = 1; i < n; i++) {
			int next = nums[i][1];
			map[next] = i;
			if(next < prev) {
				ans ++;
			}
			prev = next;
		}
		for(int i = 0; i < m; i++) {
			int a = cin.nextInt() - 1;
			int b = cin.nextInt() - 1;
			int u = map[a];	//indicies of current array
			int v = map[b];
			//System.out.println(u + " " + v + " " + a + " " + b);
			//System.out.println(map);
			ans += getDiff(nums, u, v);
			nums[v][1] = a;
			nums[u][1] = b;
			map[a] = v;
			map[b] = u;
			cin.println(ans);
		}
		cin.close();
	}
	
	static class FastIO extends PrintWriter {
		private InputStream stream;
		private byte[] buf = new byte[1 << 16];
		private int curChar;
		private int numChars;

		// standard input
		public FastIO() { this(System.in, System.out); }

		public FastIO(InputStream i, OutputStream o) {
			super(o);
			stream = i;
		}

		// file input
		public FastIO(String i, String o) throws IOException {
			super(new FileWriter(o));
			stream = new FileInputStream(i);
		}

		// throws InputMismatchException() if previously detected end of file
		private int nextByte() {
			if (numChars == -1) {
				throw new InputMismatchException();
			}
			if (curChar >= numChars) {
				curChar = 0;
				try {
					numChars = stream.read(buf);
				} catch (IOException e) {
					throw new InputMismatchException();
				}
				if (numChars == -1) {
					return -1;  // end of file
				}
			}
			return buf[curChar++];
		}

		// to read in entire lines, replace c <= ' '
		// with a function that checks whether c is a line break
		public String next() {
			int c;
			do {
				c = nextByte();
			} while (c <= ' ');

			StringBuilder res = new StringBuilder();
			do {
				res.appendCodePoint(c);
				c = nextByte();
			} while (c > ' ');
			return res.toString();
		}

		public int nextInt() {  // nextLong() would be implemented similarly
			int c;
			do {
				c = nextByte();
			} while (c <= ' ');

			int sgn = 1;
			if (c == '-') {
				sgn = -1;
				c = nextByte();
			}

			int res = 0;
			do {
				if (c < '0' || c > '9') {
					throw new InputMismatchException();
				}
				res = 10 * res + c - '0';
				c = nextByte();
			} while (c > ' ');
			return res * sgn;
		}

		public double nextDouble() { return Double.parseDouble(next()); }
	}
}
