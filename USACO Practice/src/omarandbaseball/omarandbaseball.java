//package omarandbaseball;

import java.util.*;
import java.io.*;

public class omarandbaseball {
	public static void main(String[] args) throws IOException {
		
		//1372C
		
		//you can sort the permutation using 2 or less special exchanges
		//if the permutation is already sorted, then you need 0 special exchanges.
		//if there is only one subarray of the array that is completely unsorted, none of the numbers are in the correct locations, and that subarray's length is greater than 1, then you only need
		//1 special exchange. 
		//other than that situation, you need a maximum of 2 special exchanges. You can any permutation by first moving all the numbers to incorrect locations, essentially making the 
		//permutation all unsorted. Then the second special exchange you do will sort all the numbers.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t -- > 0) {
			int n = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int numSegments = 0;
			int segmentLength = 0;
			boolean isSegment = false;
			for(int i = 0; i < n; i++) {
				int next = Integer.parseInt(st.nextToken());
				if(next != i + 1 && !isSegment) {
					numSegments ++;
					isSegment = true;
				}
				else if(next == i + 1 && isSegment) {
					isSegment = false;
				}
				if(numSegments == 1 && isSegment) {
					segmentLength ++;
				}
			}
			if(numSegments == 0) {
				fout.append("0\n");
			}
			else if(numSegments == 1 && segmentLength >= 2) {
				fout.append("1\n");
			}
			else {
				fout.append("2\n");
			}
		}
		System.out.print(fout);
	}
}
