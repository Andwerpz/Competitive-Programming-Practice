//package repetitionsdecoding;

import java.util.*;
import java.io.*;

public class repetitionsdecoding {
	public static void main(String[] args) throws IOException {
		
		//1642D
		
		//first, try to find which test cases are invalid.
		
		//notice that as we need to find pairs of sequences that contain the exact same content, the amount of occurrences for each number
		//need to be even. So if a number occurs an odd number of times, then the input is invalid. All other cases are valid.
		
		//we can maintain a prefix of valid tandem repeats, and go from left to right.
		
		//using the operations, we can take in a subarray of the form a, x1, x2, ..., xn, a, where x is any number, and turn it into the form
		//a, x1, x2, ..., xn, a, x1, x2, ..., xn, xn, xn - 1, ..., x1. We essentially create a tandem repeat out of the original
		//subarray, and get rid of 2 numbers using only the operations provided, given that the start and end numbers are the same
		
		//Since we remove 2 of the same number at a time, and the requirement for a valid input is that each number must appear an even
		//amount of times, this method always produces an answer. 
		
		//complexity is O(n^2) since for each 2 numbers, we potentially have to build the whole array.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int[] nums = new int[n];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			HashMap<Integer, Integer> count = new HashMap<Integer, Integer>();
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
				count.put(nums[i], count.getOrDefault(nums[i], 0) + 1);
			}
			boolean isValid = true;
			for(int i : count.values()) {
				if(i % 2 == 1) {
					isValid = false;
					break;
				}
			}
			if(!isValid) {
				fout.append("-1\n");
				continue;
			}
			int l = 0;
			int r = 0;
			int extra = 0;
			ArrayList<int[]> ansOps = new ArrayList<int[]>();
			ArrayList<Integer> ansSeq = new ArrayList<Integer>();
			while(true) {
				int first  = nums[l];
				r = l + 1;
				while(nums[r] != first) {
					r ++;
				}
				if(r == l + 1) {
					ansSeq.add(2);
					l += 2;
					extra += 2;
					if(l == n) {
						break;
					}
					continue;
				}
				int diff = r - l;
				ansSeq.add(diff * 2);
				//System.out.println(extra + " " + l + " " + diff + " " + first);
				int counter = 1;
				for(int i = l + 1; i < r; i++) {
					ansOps.add(new int[] {extra + diff + counter, nums[i]});
					counter ++;
					//fout.append(extra + i + diff).append(" ").append(nums[i]).append("\n");
				}
				extra += (diff * 2);
				//reverse arr segment
				ArrayList<Integer> temp = new ArrayList<Integer>();
				for(int i = l + 1; i < r; i++) {
					temp.add(nums[i]);
				}
				int p = 0;
				for(int i = r; i >= l + 2; i--) {
					nums[i] = temp.get(p);
					p ++;
				}
				l += 2;
//				for(int i : nums) {
//					System.out.print(i + " ");
//				}
//				System.out.println();
				if(l == n) {
					break;
				}
				//System.out.println(l);
			}
			fout.append(ansOps.size()).append("\n");
			for(int[] i : ansOps) {
				fout.append(i[0]).append(" ").append(i[1]).append("\n");
			}
			fout.append(ansSeq.size()).append("\n");
			for(int i : ansSeq) {
				fout.append(i).append(" ");
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
