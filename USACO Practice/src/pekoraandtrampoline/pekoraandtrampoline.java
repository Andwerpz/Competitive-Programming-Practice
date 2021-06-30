//package pekoraandtrampoline;

import java.util.*;
import java.io.*;

public class pekoraandtrampoline {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			long[] nums = new long[n];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			long ans = 0;
			long[] nump = new long[n];
			for(int i = 0; i < n; i++) {
				if(nums[i] > 1) {
					if(nump[i] < nums[i] - 1) {
						ans += (nums[i] - 1) - nump[i];
						nump[i] = nums[i] - 1;
					}
//					System.out.println("CUR NUMS: " + nums[i]);
//					System.out.println("CUR PEKORA: " + nump[i]);
					for(long j = Math.min(i + nums[i], n - 1) ; j > i + 1; j--) {
						nump[(int) j] ++;
					}
					nump[i] -= nums[i] - 1;
					if(i != n - 1) {
						nump[i + 1] += nump[i];
						nump[i] = 0;
					}
					
				}
				else {
					if(i != n - 1) {
						nump[i + 1] += nump[i];
						nump[i] = 0;
					}
					
				}
//				System.out.println("ANS: " + ans);
//				for(int j : nump) {
//					System.out.print(j + " ");
//				}
//				System.out.println();
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
