//package knapsack;

import java.util.*;
import java.io.*;

public class knapsack {
	public static void main(String[] args) throws IOException {
		
		//1446A
		
		//if there is a number between w / 2 and w, then just take that number. Else, add up the smallest numbers until you reach the range.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			long w = Long.parseLong(st.nextToken());
			long sum = 0;
			boolean isValid = false;
			StringBuilder ans = new StringBuilder();
			st = new StringTokenizer(fin.readLine());
			Long[][] nums = new Long[n][2];
			for(int i = 0; i < n; i++) {
				nums[i][0] = Long.parseLong(st.nextToken());
				nums[i][1] = (long) (i + 1);
				if(nums[i][0] >= w / 2 + (w % 2 == 1? 1 : 0) && nums[i][0] <= w) {
					isValid = true;
					fout.append("1\n").append(i + 1).append("\n");
					break;
				}
			}
			if(!isValid) {
				Arrays.sort(nums, (a, b) -> Long.compare(a[0], b[0]));
				for(int i = 0; i < n; i++) {
					sum += nums[i][0];
					ans.append(nums[i][1]).append(" ");
					if(sum >= w / 2 + (w % 2 == 1? 1 : 0) && sum < w) {
						fout.append(i + 1).append("\n").append(ans).append("\n");
						isValid = true;
						break;
					}
				}
				if(!isValid) {
					fout.append("-1\n");
				}
			}
		}
		System.out.print(fout);
	}
}
