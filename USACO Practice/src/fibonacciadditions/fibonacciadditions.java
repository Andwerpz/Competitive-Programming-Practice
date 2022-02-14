//package fibonacciadditions;

import java.util.*;
import java.io.*;

public class fibonacciadditions {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int q = Integer.parseInt(st.nextToken());
		int mod = Integer.parseInt(st.nextToken());
		int[] f = new int[300001];
		f[1] = 1;
		for(int i = 2; i < f.length; i++) {
			long next = (long) f[i - 1] + (long) f[i - 2];
			if(next > Integer.MAX_VALUE) {
				next -= mod;
			}
			f[i] = (int) next % mod;
//			if(f[i] < 0) {
//				System.out.println(f[i]);
//			}
		}
		int[] a = new int[n];
		int[] b = new int[n];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			a[i] = Integer.parseInt(st.nextToken());
		}
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			b[i] = Integer.parseInt(st.nextToken());
		}
		int[][] nums = new int[n][2];
		int pointer = 0;
		StringBuilder fout = new StringBuilder();
		for(int i = 0; i < q; i++) {
			st = new StringTokenizer(fin.readLine());
			char which = st.nextToken().charAt(0);
			int l = Integer.parseInt(st.nextToken()) - 1;
			int r = Integer.parseInt(st.nextToken()) - 1;
			int finalF = r - l + 1;
			pointer = Math.min(pointer, l);
			boolean isValid = false;
			if(which == 'A') {
				nums[l][1] ++;
				nums[l][1] %= mod;
				if(r + 1 < n) {
					nums[r + 1][0] -= f[finalF];
					nums[r + 1][1] -= f[finalF - 1];
					if(nums[r + 1][0] < 0) {
						nums[r + 1][0] += mod;
					}
					if(nums[r + 1][1] < 0) {
						nums[r + 1][1] += mod;
					}
					nums[r + 1][0] %= mod;
					nums[r + 1][1] %= mod;
				}
			}
			else {
				nums[l][1] --;
				if(nums[l][1] < 0) {
					nums[l][1] += mod;
				}
				nums[l][1] %= mod;
				if(r + 1 < n) {
					nums[r + 1][0] += f[finalF];
					nums[r + 1][1] += f[finalF - 1];
					nums[r + 1][0] %= mod;
					nums[r + 1][1] %= mod;
				}
			}
			while(true) {
				a[pointer] += nums[pointer][0];	a[pointer] %= mod;
				a[pointer] += nums[pointer][1];	a[pointer] %= mod;
				if(pointer + 1 != n) {
					nums[pointer + 1][0] += nums[pointer][0];
					nums[pointer + 1][1] += nums[pointer][0];
					nums[pointer + 1][0] %= mod;
					nums[pointer + 1][1] %= mod;
					nums[pointer + 1][0] += nums[pointer][1];
					nums[pointer + 1][0] %= mod;
				}
				nums[pointer][0] = 0;
				nums[pointer][1] = 0;
				if(a[pointer] != b[pointer]) {
					break;
				}
				if(pointer + 1 == n) {
					isValid = true;
					break;
				}
				pointer ++;
			}
			fout.append(isValid? "YES\n" : "NO\n");
//			for(int j : a) {
//				System.out.print(j + " ");
//			}
//			System.out.println();
		}
		System.out.print(fout);
	}
}
