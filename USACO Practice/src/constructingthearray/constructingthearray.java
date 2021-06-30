//package constructingthearray;

import java.util.*;
import java.io.*;

public class constructingthearray {
	
	static PriorityQueue<int[]> q;
	
	public static void main(String[] args) throws IOException {
		
		//1353D
		
		//you can represent all the remaining segments of 0s as a tuple consisting of starting point, and length. 
		//all you have to do is use an priority queue to keep track of the orders of the segments. To get the next segment, just pop off top of list. Sort list by first length, and then 
		//starting point. When processing, if the length of segment is >= 3, it can split into two segments, if its' == 2, it splits into a segment of length 1, and if the length
		//is 1, then you don't add a new segment.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int[] ans = new int[n];
			q = new PriorityQueue<int[]>((a, b) -> Comparator.compareIntArr(a, b));
			q.add(new int[] {n, 0});
			for(int i = 0; i < n; i++) {
//				for(int[] j : q) {
//					System.out.print(j[0] + " " + j[1] + ", ");
//				}
				//System.out.println();
				int[] next = q.poll();
				ans[(next[1] * 2 + next[0] - 1) / 2] = i + 1;
				//System.out.println("MID: " + ((next[1] * 2 + next[0] - 1) / 2));
				if(next[0] > 2) {
					q.add(new int[] {next[0] / 2 + (next[0] % 2 == 0? -1 : 0), next[1]});
					q.add(new int[] {next[0] / 2, (next[1] * 2 + next[0] - 1) / 2 + 1});
				}
				else if(next[0] == 2) {
					q.add(new int[] {1, next[1] + 1});
				}
				
			}
			for(int i = 0; i < n; i++) {
				fout.append(ans[i]).append(" ");
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
	
	static class Comparator {
		public static int compareIntArr(int[] a, int[] b) {
			if(Integer.compare(a[0], b[0]) != 0) {
				return -Integer.compare(a[0], b[0]);
			}
			return Integer.compare(a[1], b[1]);
		}
	}
}
