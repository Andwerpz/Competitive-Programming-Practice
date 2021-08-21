//package uniqueness;

import java.util.*;
import java.io.*;

public class uniqueness {
	public static void main(String[] args) throws IOException {
		
		//1208B
		
		//for each prefix, find the largest suffix that will make all the values distinct
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int[] nums = new int[n];
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
		}
		int l = -1;
		int r = n;
		int ans = 0;
		HashSet<Integer> dict = new HashSet<Integer>();
		while(l + 1 < n && !dict.contains(nums[l + 1])) {
			dict.add(nums[l + 1]);
			l ++;
		}
		while(r - 1 != -1 && !dict.contains(nums[r - 1])) {
			dict.add(nums[r - 1]);
			r --;
		}
		ans = l + 1 + (n - r);
		for(int i = l; i >= 0; i--) {
			dict.remove(nums[l]);
			l --;
			while(r - 1 != -1 && !dict.contains(nums[r - 1])) {
				dict.add(nums[r - 1]);
				r --;
			}
			ans = Math.max(ans, l + 1 + (n - r));
		}
		System.out.println(n - ans);
	}
}
