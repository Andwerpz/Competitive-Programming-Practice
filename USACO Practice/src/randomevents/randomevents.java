//package randomevents;

import java.util.*;
import java.io.*;

public class randomevents {
	public static void main(String[] args) throws IOException {
		
		//1461C
		
		//notice that given an array, part of the array can already be sorted. We can disregard that part. Now for the remaining array, only if the action sorts the entire array, 
		//will it be sorted, sorting only part of the array doesn't help, so we can disregard any action that doesn't sort the entire unsorted section.
		//Now, we are just looking at actions that sort the entire unsorted section, so all we have to do from now is multiply probabilities. 
		//in the solution, i kept track of the probability that it was unsorted, but ofc you can do the probability of it being sorted.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());
			double pUnsorted = 1;
			st = new StringTokenizer(fin.readLine());
			int unsortedIndex = -1;
			int[] nums = new int[n];
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			for(int i = n - 1; i >= 0; i--) {
				if(nums[i] != i + 1) {
					unsortedIndex = i + 1;
					break;
				}
			}
			if(unsortedIndex == -1) {
				fout.append((double) 1).append("\n");
				for(int i = 0; i < m; i++) {
					fin.readLine();
				}
			}
			else {
				for(int i = 0; i < m; i++) {
					st = new StringTokenizer(fin.readLine());
					int index = Integer.parseInt(st.nextToken());
					double p = Double.parseDouble(st.nextToken());
					if(index >= unsortedIndex) {
						pUnsorted *= (double) 1 - p;
					}
				}
				fout.append(1 - pUnsorted).append("\n");
			}
		}
		System.out.print(fout);
	}
}
