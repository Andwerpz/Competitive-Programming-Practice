//package fence2;

import java.util.*;
import java.io.*;

public class fence {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		int[] nums = new int[n];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
		}
		int sum = 0;
		int ans = 1;
		int cur = 0;
		for(int i = 0; i < k; i++) {
			sum += nums[i];
		}
		cur = sum;
		for(int i = 0; i < n - k; i++) {
			//System.out.println(ans + " " + sum + " " + cur + " " + nums[i + k]);
			cur += nums[i + k] - nums[i];
			if(cur < sum) {
				sum = cur;
				ans = i + 2;
			}
		}
		System.out.println(ans);
	}
}
