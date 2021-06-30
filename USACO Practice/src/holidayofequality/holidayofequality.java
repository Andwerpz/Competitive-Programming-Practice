//package holidayofequality;

import java.util.*;
import java.io.*;

public class holidayofequality {
	public static void main(String[] args) throws IOException {
		
		//758A
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		int[] nums = new int[n];
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int max = 0;
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
			max = Math.max(nums[i], max);
		}
		int ans = 0;
		for(int i = 0; i < n; i++) {
			ans += max - nums[i];
		}
		System.out.println(ans);
	}
}
