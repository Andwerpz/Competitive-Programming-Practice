//package meximumarray;

import java.util.*;
import java.io.*;

public class meximumarray {
	public static void main(String[] args) throws IOException {
		
		//1629C
		
		//since you want to maximize the lexographic value of the 'b' array, you need to maximize each value in turn starting from the 
		//first value in the array.
		
		//a O(n^2) solution will be to start by iterating from the start of the 'a' array, recording at which point the maximum 
		//mex sum is reached in the array. Add that mex sum to 'b', and on the next iteration, start at that point. 
		
		//the problem is that we need a linear time solution. Our problem is that when iterating through the array, we don't know when
		//we have hit the maximum value possible for that starting position, and thus we have to iterate through the entire array every time.
		
		//In order to solve this, we can first create a suffix mex sum array. This will tell us the maximum value for each starting point 
		//in the array, allowing us to stop at that point when we reach it, leading to a linear time solution. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int[] nums = new int[n];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			int[] sfx = new int[n];
			int p = 0;
			HashSet<Integer> v = new HashSet<Integer>();
			for(int i = n - 1; i >= 0; i--) {
				v.add(nums[i]);
				while(v.contains(p)) {
					p++;
				}
				sfx[i] = p;
			}
			v = new HashSet<Integer>();
			ArrayList<Integer> ans = new ArrayList<Integer>();
			p = 0;
			int target = sfx[0];
			for(int i = 0; i < n; i++) {
				v.add(nums[i]);
				while(v.contains(p)) {
					p ++;
				}
				if(p >= target) {
					ans.add(p);
					v.clear();
					p = 0;
					if(i != n - 1) {
						target = sfx[i + 1];
					}
				}
			}
			fout.append(ans.size()).append("\n");
			for(int i : ans) {
				fout.append(i).append(" ");
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}