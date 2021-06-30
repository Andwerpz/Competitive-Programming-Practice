//package berlandcrossword;

import java.util.*;
import java.io.*;

public class berlandcrossword {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int[] nums = new int[4];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			for(int i = 0; i < 4; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			boolean isValid = false;
			int[] diff = new int[4];
			for(int i = 0; i <= 1; i++) {
				diff[0] = i;
				for(int j = 0; j <= 1; j++) {
					diff[1] = j;
					for(int k = 0; k <= 1; k++) {
						diff[2] = k;
						for(int l = 0; l <= 1; l++) {
							diff[3] = l;
//							for(int m : diff) {
//								System.out.print(m + " ");
//							}
//							System.out.println();
							isValid = true;
							int[] cur = new int[4];
							for(int m = 0; m < 4; m++) {
								cur[m] = nums[m];
							}
							for(int m = 0; m < 4; m++) {
								cur[m] -= diff[m];
								cur[(m + 1) % 4] -= diff[m];
							}
							for(int m = 0; m < 4; m++) {
								if(cur[m] < 0 || cur[m] > n - 2) {
									isValid = false;
									break;
								}
							}
							if(isValid) {
								break;
							}
						}
						if(isValid) {
							break;
						}
					}
					if(isValid) {
						break;
					}
				}
				if(isValid) {
					break;
				}
			}
			fout.append(isValid? "YES" : "NO").append("\n");
		}
		System.out.print(fout);
	}
}
