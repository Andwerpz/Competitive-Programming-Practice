//package totallength;

import java.util.*;
import java.io.*;

public class totallength {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		long s = Long.parseLong(st.nextToken());
		int[] nums = new int[n];
		st = new StringTokenizer(fin.readLine());
		long sum = 0;
		int low = 0;
		long ans = 0;
		int count = 0;
		long countSum = 0;
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
			count ++;
			countSum += count;
			sum += nums[i];
			while(sum > s) {
				sum -= nums[low];
				low ++;
				countSum -= count;
				count--;
			}
			if(i - low >= 0) {
				ans += countSum;
			}
		}
		System.out.println(ans);
	}
}
