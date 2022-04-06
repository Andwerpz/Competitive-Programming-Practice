//package ferriswheel;

import java.util.*;
import java.io.*;

public class ferriswheel {
	public static void main(String[] args) throws IOException {
		
		//CSES 1090
		
		//note that all kids weigh less than x.
		
		//you want to have as many gondolas with 2 kids in them. Notice that the kids that weigh the most are most
		//likely to have one gondola to themselves, and the ones that weigh the least are likely to share.
		
		//we want to pair the kids that weigh the least with the ones that weigh the most, so sort the weights
		//and do 2pointer. If a pair of kids are over the weight limit, then put the heavier kid in their own gondola
		//and reduce the right pointer.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int x = Integer.parseInt(st.nextToken());
		Integer[] nums = new Integer[n];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
		}
		Arrays.sort(nums);
		int l = 0;
		int r = n - 1;
		int ans = 0;
		while(true) {
			if(nums[l] + nums[r] <= x) {
				l ++;
				r --;
				ans ++;
			}
			else {
				r --;
				ans ++;
			}
			if(l == r) {
				ans ++;
				break;
			}
			else if(l > r) {
				break;
			}
		}
		System.out.println(ans);
	}
}
