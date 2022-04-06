package concerttickets;

import java.util.*;
import java.io.*;

public class concertticketsver3 {
	public static void main(String[] args) throws IOException {

		// CSES 1091

		// this problem is simple with tree multiset.

		// for each customer, look for the greatest cost ticket to give them.
		// if there is no ticket less than what they want, then print -1

		Reader io = new Reader();
		PrintWriter pw = new PrintWriter(System.out);

		int n = io.nextInt();
		int m = io.nextInt();
		TreeMap<Integer, Integer> tickets = new TreeMap<>();
		int[] customers = new int[m];
		for (int i = 0; i < n; i++) {
			int next = io.nextInt();
			tickets.put(next, tickets.getOrDefault(next, 0) + 1);
		}
		for (int i = 0; i < m; i++) {
			customers[i] = io.nextInt();
		}
		StringBuilder fout = new StringBuilder();
		Map.Entry<Integer, Integer> val;
		for (int i = 0; i < m; i++) {
			int next = customers[i];
			val = tickets.lowerEntry(next + 1);
			if (val != null) {
				if (val.getValue() == 1) {
					tickets.remove(val.getKey());
				} else {
					tickets.put(val.getKey(), val.getValue() - 1);
				}
			}
			pw.println(val == null ? -1 : val.getKey());
		}
		io.close();
		pw.close();
	}

	// have to use custom input class
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
