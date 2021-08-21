//package pairs;

import java.util.*;
import java.io.*;

public class pairs {
	public static void main(String[] args) throws IOException {
		
		//1463C 
		
		//notice that the valid x values all lie adjacent to each other. So if we can figure out the upper and lower bounds of this range, then we can figure out how many x values there are in total.
		
		//computing the upper bound is simple. First, sort the selected numbers in ascending order, and then iterate through them. For each number, pair them up with the lowest number
		//that is greater than it, and that hasn't been picked yet. The amount of successful pairs is the upper bound.
		
		//computing the lower bound is simple as well. Repeat the upper bound process, except you sort in descending order, and when finding the pair, look for the greatest number
		//that hasn't been picked yet.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			boolean[] v = new boolean[n * 2];
			Integer[] nums = new Integer[n];
			for(int i = 0; i < n; i++) {
				int next = Integer.parseInt(st.nextToken()) - 1;
				nums[i] = next;
				v[next] = true;
			}
			Arrays.sort(nums);
			int pointer = 0;
			int maxX = 0;
			int minX = n;
			for(int i = 0; i < nums.length; i++) {
				int next = nums[i];
				while(pointer < v.length && (v[pointer] == true || pointer <= next)) {
					pointer ++;
				}
				if(pointer == v.length) {
					break;
				}
				maxX ++;
				pointer ++;
			}
			pointer = v.length - 1;
			for(int i = nums.length - 1; i >= 0; i--) {
				int next = nums[i];
				while(pointer >= 0 && (v[pointer] == true || pointer >= next)) {
					pointer --;
				}
				if(pointer == -1) {
					break;
				}
				minX --;
				pointer --;
			}
			fout.append(maxX - minX + 1).append("\n");
		}
		System.out.print(fout);
	}
}
