//package arraystabilizationgcdversion;

import java.util.*;
import java.io.*;

public class arraystabilizationgcdversionver1 {
	
	public static int gcd(int a, int b) {
		if(b == 0) {
			return a;
		}
		return gcd(b, a % b);
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int ans = 0;
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int[] nums = new int[n];
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			while(true) {
				boolean isValid = true;
				int first = nums[0];
				for(int i = 0; i < n; i++) {
					if(nums[i] != nums[(i + 1) % n]) {
						isValid = false;
						if(i == n - 1) {
							nums[i] = gcd(nums[i], first);
						}
						else {
							nums[i] = gcd(nums[i], nums[i + 1]);
						}
					}
				}
				if(isValid) {
					break;
				}
				else {
					ans ++;
				}
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
