//package youngexplorers;

import java.util.*;
import java.io.*;

public class youngexplorers {
	public static void main(String[] args) throws IOException {
		
		//1355B
		
		//just start making groups from the most experienced explorers.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			Integer[] nums = new Integer[n];
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			Arrays.sort(nums);
			int curAmt = 0;
			int needed = -1;
			int ans = 0;
			for(int i = 0; i < n; i++) {
				needed = Math.max(needed, nums[i]);
				curAmt ++;
				if(curAmt == needed) {
					needed = -1;
					ans ++;
					curAmt = 0;
				}
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
