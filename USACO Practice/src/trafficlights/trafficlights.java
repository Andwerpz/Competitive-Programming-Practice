//package trafficlights;

import java.util.*;
import java.io.*;

public class trafficlights {
	public static void main(String[] args) throws IOException {
		
		//CSES 1163
		
		//first, calculate the maximum seg length with all the lights installed. Then you can remove the lights in backwards order
		//and to find the new max seg length, you can just take the max of the prev max seg length and the new segment created
		//by removing the light. 
		
		//Solving it while considering the lights in forward order is also possible, but it requires an extra treemap to store the 
		//lengths of each segment. This is necessary as when you install a light, you reduce the length of segments, and in order
		//to find the next max segment, it is necessary to store all segments. 
		
		FastIO cin = new FastIO();
		int x = cin.nextInt();
		int n = cin.nextInt();
		int[] nums = new int[n];
		NavigableSet<Integer> lights = new TreeSet<Integer>();
		for(int i = 0; i < n; i++) {
			nums[i] = cin.nextInt();
			lights.add(nums[i]);
		}
		lights.add(0);
		lights.add(x);
		//find max seg length
		int maxSeg = 0;
		int prev = lights.first();
		while(true) {
			Integer next = lights.ceiling(prev + 1);
			if(next == null) {
				break;
			}
			maxSeg = Math.max(maxSeg, next - prev);
			prev = next;
		}
		//remove lights backwards
		int[] ansArr = new int[n];
		ansArr[n - 1] = maxSeg;
		for(int i = n - 1; i > 0; i--) {
			int next = nums[i];
			lights.remove(next);
			int l = lights.floor(next);
			int r = lights.ceiling(next);
			maxSeg = Math.max(maxSeg, r - l);
			ansArr[i - 1] = maxSeg;
		}
		StringBuilder fout = new StringBuilder();
		for(int i : ansArr) {
			fout.append(i).append(" ");
		}
		cin.println(fout);
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
