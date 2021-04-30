package divisibilityby8;

import java.util.*;
import java.io.*;

public class divisibilityby8ver1 {
	public static void main(String[] args) throws IOException {
		
		//lol, misunderstood problem
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		char[] s = fin.readLine().toCharArray();
		int[] nums = new int[s.length];
		int n = s.length;
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(s[i] + "");
		}
		int ans = 0;
		boolean isValid = false;
		for(int i = 0; i < n; i++) {
			if(nums[i] % 8 == 0) {
				isValid = true;
				ans = nums[i];
			}
		}
		for(int i = 0; i < n - 1; i++) {
			int next = nums[i] * 10 + nums[i + 1];
			if(next % 8 == 0) {
				isValid = true;
				ans = next;
			}
		}
		for(int i = 0; i < n - 2; i++) {
			int next = nums[i] * 100 + nums[i + 1] * 10 + nums[i];
			if(next % 8 == 0) {
				isValid = true;
				ans = next;
			}
		}
		if(isValid) {
			System.out.println("YES");
			System.out.println(ans);
		}
		else {
			System.out.println("NO");
		}
	}
}
