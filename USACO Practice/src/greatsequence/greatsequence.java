//package greatsequence;

import java.util.*;
import java.io.*;

public class greatsequence {
	public static void main(String[] args) throws IOException {
		
		//1642C
		
		//this is solvable using a greedy approach
		
		//define two pointers, l and r = 0, sort the array in ascending order, and define a boolean array, v, v[0] - v[n] = false;
		
		//iterate l until !v[l]
		//iterate r until nums[r] >= nums[l] * x && !v[r]. 
		//if nums[r] == nums[l] * x: v[l] = true, v[r] = true
		//else: v[l] = true, ans ++
		
		//this works in linear time as we sorted it in ascending order, when we iterate l, we only need to iterate r to the right in
		//order to find possible matches.
		
		//i believe that this works because if there exists a match for a number within the array, we want to match it up, else, we
		//are forced to create a match. The amount of numbers we have to create matches for is fixed, and can't be changed depending on
		//the order we match things, so the problem is just a matter of finding all the numbers without matches. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			long x = Integer.parseInt(st.nextToken());
			Long[] nums = new Long[n];
			boolean[] v = new boolean[n];
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Long.parseLong(st.nextToken());
			}
			Arrays.sort(nums, (a, b) -> Long.compare(a, b));
			int l = 0;
			int r = 0;
			int ans = 0;
			for(int i = 0; i < n; i++) {
				if(v[i]) {
					continue;
				}
				long next = nums[i];
				long target = next * x;
				while(r < n && (nums[r] < target || v[r])) {
					r ++;
				}
				if(r < n && nums[r] == target) {
					v[r] = true;
				}
				else {
					ans ++;
				}
				v[i] = true;
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
