//package omkarandwaterslide;

import java.util.*;
import java.io.*;

public class omkarandwaterslide {
	public static void main(String[] args) throws IOException {
		
		//1392C
		
		//remember to use longs whenever you need to
		
		//add to ans when you go down in value.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			long ans = 0;
			int[] nums = new int[n];
			int[] pfx = new int[n];
			for(int i = 0; i < n; i++) {
				int next = Integer.parseInt(st.nextToken());
				nums[i] = next;
				if(i != 0) {
					pfx[i] = Math.max(next, pfx[i - 1]);
				}
			}
			int max = 0;
			int prev = 0;
			for(int i = 0; i < n; i++) {
				if(i != 0) {
					if(nums[i] < prev) {
						ans += prev - nums[i];
					}
				}
				prev = nums[i];
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
