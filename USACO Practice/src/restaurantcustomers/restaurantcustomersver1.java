package restaurantcustomers;

import java.io.*;
import java.util.*;

public class restaurantcustomersver1 {
	public static void main(String[] args) throws IOException {
		Reader io = new Reader();
		int n = io.nextInt();
		int[][] times = new int[n * 2][2];
		for (int i = 0; i < n; i++) {
			int a = io.nextInt();
			int b = io.nextInt();
			times[i] = new int[] { a, 0 };
			times[i + n] = new int[] { b, 1 };
		}
		Arrays.sort(times, (a, b) -> a[0] - b[0]);
		int max = 0;
		int cur = 0;
		for (int i = 0; i < times.length; i++) {
			// System.out.println(cur);
			if (times[i][1] == 0) {
				cur++;
			}
			else {
				cur--;
			}
			if (cur > max) {
				max = cur;
			}
		}
		System.out.println(max);
	}
	
	static class Reader {
		final private int BUFFER_SIZE = 1 << 16;
		private DataInputStream din;
		private byte[] buffer;
		private int bufferPointer, bytesRead;

		public Reader() {
			din = new DataInputStream(System.in);
			buffer = new byte[BUFFER_SIZE];
			bufferPointer = bytesRead = 0;
		}

		private void fillBuffer() throws IOException {
			bytesRead = din.read(buffer, bufferPointer = 0, BUFFER_SIZE);
			if (bytesRead == -1)
				buffer[0] = -1;
		}

		private byte read() throws IOException {
			if (bufferPointer == bytesRead)
				fillBuffer();
			return buffer[bufferPointer++];
		}

		public void close() throws IOException {
			if (din == null)
				return;
			din.close();
		}

		public int nextInt() throws IOException {
			int ret = 0;
			byte c = read();
			while (c <= ' ')
				c = read();
			boolean neg = (c == '-');
			if (neg)
				c = read();
			do {
				ret = ret * 10 + c - '0';
			} while ((c = read()) >= '0' && c <= '9');

			if (neg)
				return -ret;
			return ret;
		}
	}
}