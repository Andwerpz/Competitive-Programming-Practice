//package corruptedarray;

import java.util.*;
import java.io.*;

public class corruptedarray {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t -- > 0) {
			int n = Integer.parseInt(fin.readLine()) + 2;
			long[] nums = new long[n];
			long sum = 0;
			StringTokenizer st = new StringTokenizer(fin.readLine());
			HashSet<Long> numSet = new HashSet<Long>();
			HashMap<Long, Long> dict = new HashMap<Long, Long>();
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
				numSet.add(nums[i]);
				dict.put(nums[i], dict.getOrDefault(nums[i], (long) 0) + 1);
				sum += nums[i];
			}
			long ansSum = -1;
			long ansX = -1;
			for(int i = 0; i < n; i++) {
				if(numSet.contains(sum - 2 * nums[i])) {
					//System.out.println(sum - 2 * nums[i]);
					if(sum - 2 * nums[i] == nums[i]) {
						if(dict.get(nums[i]) >= 2) {
							ansSum = nums[i];
							ansX = sum - 2 * nums[i];
						}
					}
					else {
						ansSum = nums[i];
						ansX = sum - 2 * nums[i];
					}
				}
			}
			//System.out.println(sum);
			if(ansSum == -1 && ansX == -1) {
				fout.append("-1\n");
			}
			else {
				for(int i = 0; i < n; i++) {
					if(nums[i] == ansSum) {
						ansSum = -1;
					}
					else if(nums[i] == ansX) {
						ansX = -1;
					}
					else {
						fout.append(nums[i]).append(" ");
					}
				}
				fout.append("\n");
			}
		}
		System.out.println(fout);
	}
}
