//package josephusproblemI;

import java.util.*;
import java.io.*;

public class josephusproblemI {
	public static void main(String[] args) throws IOException {
		
		//CSES 2612
		
		//since k == 2, if you only search among the remaining kids, then you can simulate it in 2n steps. 
		
		Reader cin = new Reader();
		int n = cin.nextInt();
		TreeSet<Integer> set = new TreeSet<>();
		for(int i = 0; i < n; i++) {
			set.add(i + 1);
		}
		Integer prev = 0;
		StringBuilder fout = new StringBuilder();
		for(int i = 0; i < n; i++) {
			prev = set.ceiling(prev + 1);
			if(prev == null) {
				prev = set.ceiling(0);
			}
			prev = set.ceiling(prev + 1);
			if(prev == null) {
				prev = set.ceiling(0);
			}
			set.remove(prev);
			fout.append(prev).append(" ");
		}
		System.out.println(fout);
		cin.close();
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
