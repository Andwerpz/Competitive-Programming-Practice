package maximummedian;

import java.util.*;
import java.io.*;

public class maximummedianver2 {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		long n = Integer.parseInt(st.nextToken());
		long k = Integer.parseInt(st.nextToken());
		int[] nums = new int[(int)n];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
		}
		int low = (int)n / 2;
		int high = low;
		int curLevel = nums[low];
		Arrays.sort(nums);
		long ans = nums[low];
		for(int i = low; i < n; i++) {
			
			long gap = nums[i] - curLevel;
			long range = i - low;
			System.out.println(k + " " + range + " " + gap);
			if(k - range * gap < 0) {
				high = i;
				break;
			}
			else {
				k -= range * gap;
				curLevel = nums[i];
				high = i;
				ans = nums[i];
			}
		}
		System.out.println("leftover: " + k);
		System.out.println(ans + (k / (n - (n / 2) - (n - high - 1))));
	}
}
