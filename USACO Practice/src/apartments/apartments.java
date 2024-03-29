//package apartments;
 
import java.util.*;
import java.io.*;
 
public class apartments {
	
	public static void main(String[] args) throws IOException {
		
		//CSES 1084
		
		//for each apartment, we assign the lowest request to it
		
		FastIO cin = new FastIO();
		int n = cin.nextInt();
		int m = cin.nextInt();
		int k = cin.nextInt();
		Integer[] p = new Integer[n];
		Integer[] a = new Integer[m];
		for(int i = 0; i < n; i++) {
			p[i] = cin.nextInt();
		}
		for(int i = 0; i < m; i++) {
			a[i] = cin.nextInt();
		}
		Arrays.sort(p);
		Arrays.sort(a);
		int pointer = 0;
		int ans = 0;
		for(int i = 0; i < m; i++) {
			a[i]-=k;
			while(pointer < n && p[pointer] < a[i]) {
				pointer ++;
			}
			if(pointer == n) {
				break;
			}
			if(p[pointer] <= a[i] + 2*k) {
				pointer++;
				ans ++;
			}
		}
		System.out.println(ans);
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
