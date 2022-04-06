//package sticklengths;

import java.util.*;
import java.io.*;

public class sticklengths {
	public static void main(String[] args) throws IOException {
		
		//CSES 1074
		
		//we want the target to be equal to the median stick length.
		
		//if x is the target, and the total cost to adjust all sticks to x = y, and you plot it, then the graph will
		//look like a parabola. The lowest point of the parabola is when x = median.
		
		//you can also think of it like the sum of a bunch of absolute value functions. 
		
		Reader cin = new Reader();
		int n = cin.nextInt();
		Integer[] nums = new Integer[n];
		for(int i = 0; i < n; i++) {
			nums[i] = cin.nextInt();
		}
		Arrays.sort(nums);
		int mid = nums[n / 2];
		long ans = 0;
		for(int i = 0; i < n; i++) {
			ans += (long) Math.abs(nums[i] - mid);
		}
		System.out.println(ans);
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
