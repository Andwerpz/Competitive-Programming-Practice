package exactchange;

import java.util.*;
import java.io.*;

public class exactchange {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int max3 = 0;
			boolean hasOne = false;
			boolean hasTwo = false;
			boolean hasModOne = false;
			boolean threeTwos = false;
			int[] nums = new int[n];
			int ans = 0;
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int max = 0;
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
				max = Math.max(max, nums[i]);
				if(nums[i] == 1) {
					hasOne = true;
				}
				else if(nums[i] % 3 == 1) {
					hasModOne = true;
				}
				if(nums[i] % 3 == 2) {
					hasTwo = true;
				}
			}
			if(max % 3 == 0 && (hasTwo || hasModOne)) {
				hasModOne = false;
				hasTwo = false;
				threeTwos = true;
			}
			for(int i = 0; i < n; i++) {
				//System.out.println(max3);
				if(nums[i] == max && max % 3 == 1) {
					max3 = Math.max(max3, nums[i] / 3 - 1);
				}
				else {
					max3 = Math.max(max3, nums[i] / 3);
				}
			}
			Arrays.sort(nums);
			int topDiff = 0;
			//System.out.println(max3 + " " + (max / 3));
			ans = max3 + (hasOne || hasModOne? 1 : 0) + (hasTwo? 1 : 0) + (threeTwos? 1 : 0);
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
