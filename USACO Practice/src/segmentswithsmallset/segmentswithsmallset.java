//package segmentswithsmallset;

import java.util.*;
import java.io.*;

public class segmentswithsmallset {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		HashMap<Integer, Integer> dict = new HashMap<Integer, Integer>();
		int[] nums = new int[n];
		long ans = 0;
		int numUnique = 0;
		int low = 0;
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
			if(!dict.containsKey(nums[i])) {
				numUnique++;
			}
			dict.put(nums[i], dict.getOrDefault(nums[i], 0) + 1);
			while(numUnique > k) {
				dict.put(nums[low], dict.get(nums[low]) - 1);
				if(dict.get(nums[low]) == 0) {
					dict.remove(nums[low]);
					numUnique --;
				}
				low ++;
			}
			if(low <= i) {
				ans += i - low + 1;
			}
		}
		System.out.println(ans);
	}
}
