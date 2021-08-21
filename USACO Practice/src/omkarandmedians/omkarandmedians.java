//package omkarandmedians;

import java.util.*;
import java.io.*;

public class omkarandmedians {
	public static void main(String[] args) throws IOException {
		
		//1536D
		
		//consider making the a array two values at a time. Notice that you can only shift the median by 1 value every 2 values you add. What this means for the b array is that
		//every time you want to shift the median, there must not be a previous median in between the immediate previous median and the new median. 
		
		//just use a tree set to check. If the floor or ceiling value is equal to prev, then it's valid; else, it's not.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int[] nums = new int[n];
			Integer[] sorted = new Integer[n];
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
				sorted[i] = nums[i];
			}
			TreeSet<Integer> dict = new TreeSet<Integer>();
			boolean isValid = true;
			dict.add(nums[0]);
			for(int i = 1; i < n; i++) {
				int prev = nums[i - 1];
				int cur = nums[i];
				if(prev < cur) {
					if(dict.floor(cur - 1) != prev) {
						isValid = false;
						break;
					}
				}
				else if(prev > cur) {
					if(dict.ceiling(cur + 1) != prev) {
						isValid = false;
						break;
					}
				}
				if(!dict.contains(cur)) {
					dict.add(cur);
				}
			}
			fout.append(isValid? "YES\n" : "NO\n");
		}
		System.out.print(fout);
	}
}
