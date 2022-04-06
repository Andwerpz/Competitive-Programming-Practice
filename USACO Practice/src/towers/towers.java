//package towers;

import java.util.*;
import java.io.*;	

public class towers {
	public static void main(String[] args) throws IOException {
		
		//CSES 1073
		
		//for each cube, put it on the smallest cube that you can put it on, or if there exists no cube that you can
		//place it on, make a new tower.
		
		FastIO cin = new FastIO();
		int n = cin.nextInt();
		int[] nums = new int[n];
		for(int i = 0; i < n; i++) {
			nums[i] = cin.nextInt();
		}
		TreeMap<Integer, Integer> map = new TreeMap<Integer, Integer>();
		Map.Entry<Integer, Integer> val;
		for(int i = 0; i < n; i++) {
			int next = nums[i];
			val = map.ceilingEntry(next + 1);
			if(val == null) {
				map.put(next, map.getOrDefault(next, 0) + 1);
			}
			else {
				if(val.getValue() == 1) {
					map.remove(val.getKey());
				}
				else {
					map.put(val.getKey(), val.getValue() - 1);
				}
				map.put(next, map.getOrDefault(next, 0) + 1);
			}
		}
		int ans = 0;
		for(Integer i : map.values()) {
			ans += i;
		}
		System.out.println(ans);
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
