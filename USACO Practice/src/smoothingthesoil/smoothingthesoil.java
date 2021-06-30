package smoothingthesoil;

import java.util.*;
import java.io.*;

public class smoothingthesoil {
	public static void main(String[] args) throws IOException {
		
		//2021 Keep Austin Hacking
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int d = Integer.parseInt(st.nextToken());
		long mod = 1000000007;
		long[] nums = new long[n];
		st = new StringTokenizer(fin.readLine());
		long avg = 0;
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
			avg += nums[i];
		}
		long ans = 0;
		avg /= (long) n;
		int pointer = 0;
		for(int i = 0; i < n; i++) {
			if(nums[i] < avg) {
				while(nums[pointer] <= avg) {
					pointer ++;
				}
				long pointerDiff = nums[pointer] - avg;
				long curDiff = avg - nums[i];
				long diff = Math.min(pointerDiff, curDiff);
				long cost = Math.abs(i - pointer) / d + (Math.abs(i - pointer) % d == 0? 0 : 1);
				ans += diff * cost;
				ans %= mod;
				nums[pointer] -= diff;
				nums[i] += diff;
				if(nums[i] < avg) {
					i --;
				}
			}
		}
		System.out.println(ans);
	}
}
