//package numberofpairs;

import java.util.*;
import java.io.*;

public class numberofpairs {
	public static void main(String[] args) throws IOException {
		
		//1538C
		
		//use two pointer technique
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int l = Integer.parseInt(st.nextToken());
			int r = Integer.parseInt(st.nextToken());
			st = new StringTokenizer(fin.readLine());
			Integer[] nums = new Integer[n];
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			Arrays.sort((Integer[])nums);
			int low = 0;
			int high = n - 2;
			long ans = 0;
			for(int i = n - 1; i > 0; i--) {
				int next = nums[i];
				while(low + 1 < i && nums[low] + next < l) {
					low ++;
				}
				while(low - 1 >= 0 && nums[low - 1] + next >= l) {
					low --;
				}
				while(high - 1 >= 0 && nums[high] + next > r) {
					high --;
				}
				while(high + 1 < i && nums[high + 1] + next <= r) {
					high ++;
				}
				if(i <= low) {
					low = i - 1;
				}
				if(i <= high) {
					high = i - 1;
				}
				if(nums[high] + next <= r && nums[low] + next >= l) {
					ans += (long) (high - low + 1);
				}
				//System.out.println(next + " " + high + " " + low);
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
