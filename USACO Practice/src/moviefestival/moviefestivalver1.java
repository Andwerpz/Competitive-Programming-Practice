/*
ID: andwerp1
LANG: JAVA
TASK: moviefestival
*/

package moviefestival;

import java.io.*;
import java.util.*;

public class moviefestivalver1 {
	public static void main(String[] args) throws IOException {
		Reader fin = new Reader();
		int n = fin.nextInt();
		int[][] movies = new int[n][2];
		for (int i = 0; i < n; i++) {
			movies[i] = new int[] { fin.nextInt(), fin.nextInt() };
		}
		Arrays.sort(movies, (a, b) -> a[1] - b[1]);
		int curTime = 0;
		int numMovies = 0;
		for (int i = 0; i < n; i++) {
			if (curTime <= movies[i][0]) {
				numMovies++;
				curTime = movies[i][1];
			}
		}
		System.out.println(numMovies);
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