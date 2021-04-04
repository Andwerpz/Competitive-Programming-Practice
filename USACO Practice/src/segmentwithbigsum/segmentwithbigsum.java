//package segmentwithbigsum;

import java.util.*;
import java.io.*;

public class segmentwithbigsum {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		long s = Long.parseLong(st.nextToken());
		int[] nums = new int[n];
		int min = -1;
		int low = 0;
		long sum = 0;
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
			sum += nums[i];
			while(low < n && sum - nums[low] >= s) {
				sum -= nums[low];
				low++;
			}
			if(sum >= s && (i - low + 1 < min || min == -1)) {
				min = i - low + 1;
			}
			//System.out.println(min + " " + sum + " " + low + " " + i);
		}
		System.out.println(min);
	}
}
