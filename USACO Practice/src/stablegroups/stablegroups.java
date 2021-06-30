//package stablegroups;

import java.util.*;
import java.io.*;

public class stablegroups {
	public static void main(String[] args) throws IOException {
		
		//1539C
		
		//first sort the numbers array. 
		//find out how many gaps there are, and how large the gaps are in terms of multiples of x. Then go along and fill in the gaps, prioritizing the smallest gaps first.
		//ans is the num gaps + 1.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		long k = Long.parseLong(st.nextToken());
		long x = Long.parseLong(st.nextToken());
		Long[] nums = new Long[n];
		ArrayList<Long> gaps = new ArrayList<Long>();
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Long.parseLong(st.nextToken());
		}
		Arrays.sort(nums);
		for(int i = 0; i < n - 1; i++) {
			long gap = (Math.abs(nums[i] - nums[i + 1]) - 1) / x;
			if(gap > 0) {
				gaps.add(gap);
			}
		}
		gaps.sort((a, b) -> -Long.compare(a, b));
		//System.out.println(gaps);
		for(int i = gaps.size() - 1; i >= 0; i --) {
			k -= gaps.get(i);
			if(k >= 0) {
				gaps.remove(i);
			}
			else {
				break;
			}
		}
		System.out.println(gaps.size() + 1);
	}
}
