package geometricprogression;

import java.util.*;
import java.io.*;

public class geometricprogressionver3 {
	public static void main(String[] args) throws IOException {
		
		//working solution
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		HashMap<Long, Long> dict1 = new HashMap<Long, Long>();
		HashMap<Long, Long> dict2 = new HashMap<Long, Long>();
		int[] nums = new int[n];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
		}
		long ans = 0;
		for(int i = n - 1; i >= 0; i --) {
			long next = nums[i];
			ans += dict2.getOrDefault(next * k, (long) 0);
			dict2.put(next, dict2.getOrDefault(next, (long) 0) + dict1.getOrDefault(next * k, (long) 0));
			dict1.put(next, dict1.getOrDefault(next, (long) 0) + 1);
		}
		System.out.println(ans);
	}
}
