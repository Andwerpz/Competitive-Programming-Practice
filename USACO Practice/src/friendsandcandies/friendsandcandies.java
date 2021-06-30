//package friendsandcandies;

import java.util.*;
import java.io.*;

public class friendsandcandies {
	public static void main(String[] args) throws IOException {
		
		//1538B
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int[] nums = new int[n];
			int sum = 0;
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
				sum += nums[i];
			}
			Arrays.sort(nums);
			if(sum % n == 0) {
				int needed = 0;
				int avg = sum / n;
				for(int i = 0; i < n; i++) {
					if(nums[i] < avg) {
						needed += avg - nums[i];
					}
				}
				int ans = 0;
				sum = 0;
				for(int i = n - 1; i >= 0; i--) {
					if(sum < needed) {
						ans ++;
						sum += nums[i] - avg;
					}
					else {
						break;
					}
				}
				fout.append(ans).append("\n");
			}
			else {
				fout.append("-1\n");
			}
		}
		System.out.print(fout);
	}
}
