//package minimumextraction;

import java.util.*;
import java.io.*;

public class minimumextraction {
	public static void main(String[] args) throws IOException {
		
		//1607C
		
		//damn you, object sort
		
		//notice that at any point in time, you are given only 1 option, to remove the lowest number and subtract it from all the other numbers.
		//if you go through all the moves for a given array, and take the max of the minimum numbers that you come up with, then you'll get
		//the right answer.
		
		//also notice that you are given 10^9 moves that you can do, n * t = 10^9. This means that if we can simulate each move in O(1) time, 
		//it's feasible to just simulate them all. 
		
		//since we add the value of the minimum number to all the numbers in the array, we can just keep it in an offset variable, and add to
		//the values in the array when needed. Every time we do a move, just add the negative of the minimum to the offset. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			Long[] nums = new Long[n];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Long.parseLong(st.nextToken());
			}
			long offset = 0;
			Arrays.sort(nums);
			long max = nums[0];
			for(int i = 1; i < n; i++) {
				offset -= (nums[i - 1] + offset);
				max = Math.max(max, nums[i] + offset);
			}
			fout.append(max).append("\n");
		}
		System.out.print(fout);
	}
}
