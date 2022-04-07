package josephusproblemII;

import java.util.*;
import java.io.*;

public class josephusproblemII {
	public static int getRangeSum(int[][] tree, int l, int r) {	//l, r inclusive
		int sum = 0;
		for(int i = l; i <= r; i += 0) {
			int index = i;
			int layer = 0;
			int increment = 1;
			while(true) {
				int temp = index;
				index /= 2;
				layer ++;
				increment *= 2;
				if(index * increment < l || (index + 1) * increment > r) {
					index = temp;
					layer --;
					increment /= 2;
					break;
				}
			}
			i += increment;
			sum += tree[layer][index];
		}
		return sum;
	}
	
	public static void setValue(int[][] tree, int index, int val) {
		int diff = val - tree[0][index];
		for(int layer = 0; layer < tree.length; layer++) {
			tree[layer][index] += diff;
			index /= 2;
		}
		
	}
	
	public static void main(String[] args) throws IOException {
		
		//CSES 2163
		
		//my attempt at simulating the problem. Gets TLE
		
		Reader cin = new Reader();
		int n = cin.nextInt();
		int k = cin.nextInt() + 1;	
		//in the problem statement, k is the amount of children that are skipped, here you count k
		//children and the kth one is removed. It functions the same as josephusproblemI
		TreeSet<Integer> set = new TreeSet<>();
		int treeSize = (int) Math.pow(2, 18);
		int[][] segTree = new int[19][];
		for(int i = 0; i < segTree.length; i++) {
			segTree[i] = new int[treeSize];
			if(i == 0) {
				for(int j = 0; j < n; j++) {
					segTree[0][j] = 1;
					set.add(j);
				}
			}
			else {
				for(int j = 0; j < treeSize; j++) {
					segTree[i][j] = segTree[i - 1][j * 2] + segTree[i - 1][j * 2 + 1];
				}
			}
			treeSize /= 2;
		}
		StringBuilder fout = new StringBuilder();
		Integer pointer = 0;
		for(int i = 0; i < n; i++) {
			int numRemaining = n - i;
			int moveAmt = (k - 1) % numRemaining;
			pointer = set.ceiling(pointer);
			if(pointer == null) {
				pointer = set.ceiling(0);
			}
			//System.out.println("PTR: " + pointer);
			//check if next remove is after pointer
			boolean after = true;
			//subtract 1 since we already counted the move required to get to pointer
			int afterSum = getRangeSum(segTree, pointer + 1, n - 1);
			if(afterSum < moveAmt) {
				after = false;
				moveAmt -= afterSum;
			}
			//bin search for position of next remove
			int leftBound = after? pointer + 1 : 0;
			int low = after? pointer + 1 : 0;
			int high = after? n - 1 : pointer - 1;
			int mid = low + (high - low) / 2;
			int leftmostPos = high;	//find the leftmost position where rangeSum(leftBound, leftmostPos) >= moveAmt
			while(low <= high) {
				int sum = getRangeSum(segTree, leftBound, mid);
				if(sum >= moveAmt) {
					leftmostPos = Math.min(leftmostPos, mid);
					high = mid - 1;
				}
				else {
					low = mid + 1;
				}
				mid = low + (high - low) / 2;
			}
			
			if(moveAmt != 0) {	//bin search doesn't work when move amt == 0
				pointer = leftmostPos;
			}
			
			set.remove(pointer);
			setValue(segTree, pointer, 0);
			fout.append(pointer + 1).append(" ");
			
//			System.out.println(pointer + " " + moveAmt + " " + numRemaining);
//			for(int j = 0; j < n; j++) {
//				System.out.print(segTree[0][j] + " ");
//			}
//			System.out.println();
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