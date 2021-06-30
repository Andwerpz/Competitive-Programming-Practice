//package challengingcliffs;

import java.util.*;
import java.io.*;

public class challengingcliffs {
	public static void main(String[] args) throws IOException {
		
		//1537C
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			Integer[] nums = new Integer[n];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			Arrays.sort(nums);
			int minDiff = Integer.MAX_VALUE;
			for(int i = 0; i < n - 1; i++) {
				int diff = nums[i + 1] - nums[i];
				minDiff = Math.min(diff, minDiff);
			}
			int startIndex = 0;
			for(int i = 0; i < n - 1; i++) {
				int diff = nums[i + 1] - nums[i];
				if(diff == minDiff) {
					startIndex = i;
					break;
				}
			}
			fout.append(nums[startIndex]).append(" ");
			for(int i = startIndex + 2; i < n; i++) {
				fout.append(nums[i]).append(" ");
			}
			for(int i = 0; i < startIndex; i++) {
				fout.append(nums[i]).append(" ");
			}
			fout.append(nums[startIndex + 1]).append("\n");
		}
		System.out.print(fout);
	}
}
