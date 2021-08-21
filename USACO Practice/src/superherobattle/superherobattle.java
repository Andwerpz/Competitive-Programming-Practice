//package superherobattle;

import java.util.*;
import java.io.*;

public class superherobattle {
	public static void main(String[] args) throws IOException {
		
		//1141E
		
		//just have to pay attention to all cases.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		long h = Long.parseLong(st.nextToken());
		int n = Integer.parseInt(st.nextToken());
		st = new StringTokenizer(fin.readLine());
		long[] nums = new long[n];
		for(int i = 0; i < n; i++) {
			nums[i] = Long.parseLong(st.nextToken());
		}
		long[] pfxMin = new long[n];
		long min = Integer.MAX_VALUE;
		for(int i = 0; i < n; i++) {
			if(i == 0) {
				pfxMin[0] = nums[0];
			}
			else {
				pfxMin[i] = pfxMin[i - 1] + nums[i];
			}
			min = Math.min(min, pfxMin[i]);
		}
		long diff = pfxMin[n - 1];
		if(diff >= 0) {
			if(h + min <= 0) {
				long ans = 0;
				for(int i = 0; i < n; i++) {
					ans ++;
					if(h + pfxMin[i] <= 0) {
						break;
					}
				}
				System.out.println(ans);
			}
			else {
				System.out.println("-1");
			}
		}
		else {
			long ans = 0;
			if(h + min > 0) {
				long toMin = h + min;
				long cycles = Math.abs(Math.abs(toMin / diff) + (toMin % diff != 0? 1 : 0));
				ans += cycles * n;
				//System.out.println(cycles);
				h += cycles * diff;
			}
			
			//System.out.println(h);
			if(h > 0) {
				for(int i = 0; i < n; i++) {
					ans ++;
					if(h + pfxMin[i] <= 0) {
						break;
					}
				}
			}
			System.out.println(ans);
		}
	}
}
