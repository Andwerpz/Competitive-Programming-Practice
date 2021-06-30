//package pricefixed;

import java.util.*;
import java.io.*;

public class pricefixed {
	public static void main(String[] args) throws IOException {
		
		//1539D
		
		//sort the various goods by the discount threshold in ascending order.
		//have two pointers, l and r. l points to the lowest threshold and r points to the highest threshold. Check whether the good denoted by l can be bought with a discount. If it
		//can, buy out the good, and increment l. If it can't be bought with a discount, then buy the good denoted by r until the threshold is met, or you bought out the good. If 
		//you buy the good out, then decrement r.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		long[][] nums = new long[n][2];	//0: num left, 1: threshold
		long sum = 0;
		for(int i = 0; i < n; i++) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			nums[i] = new long[] {Long.parseLong(st.nextToken()), Long.parseLong(st.nextToken())};
			sum += nums[i][0];
		}
		Arrays.sort(nums, (a, b) -> Long.compare(a[1], b[1]));
		int l = 0;
		int r = n - 1;
		long counter = 0;	//longs...
		long ans = 0;
		
		while(counter < sum) {
			if(counter >= nums[l][1]) {
				ans += nums[l][0];
				counter += nums[l][0];
				nums[l][0] = 0;
				l++;
			}
			else {
				if(r == -1) {
					break;
				}
				long diff = Math.abs(nums[l][1] - counter);
				long remove = Math.min(diff, nums[r][0]);
				counter += remove;
				nums[r][0] -= remove;
				if(nums[r][0] == 0) {
					r --;
				}
				ans += remove * 2;
			}
//			System.out.println("COUNTER: " + counter);
//			for(long[] i : nums) {
//				System.out.println(i[0] + " " + i[1]);
//			}
		}
		System.out.println(ans);
	}
}
