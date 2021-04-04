//package numberofsegmentswithbigsum;

import java.util.*;
import java.io.*;

public class numberofsegmentswithbigsum {
	public static void main(String[] args) throws IOException {
		
		//the number of good segments is equal to the total number of segments minus the number of bad segments.
		//we just count the number of bad segments and take the difference, exactly the same as number of smaller than
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		long s = Long.parseLong(st.nextToken());
		int[] nums = new int[n];
		long ans = 0;
		long sum = 0;
		int low = 0;
		long total = 0;
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			total += i + 1;
			nums[i] = Integer.parseInt(st.nextToken());
			sum += nums[i];
			while(low < n && sum >= s) {
				sum -= nums[low];
				low++;
			}
			if(low <= i) {
				ans += i - low + 1;
			}
			//System.out.println(low + " " + i);
		}
		System.out.println(total - ans);
	}
}
