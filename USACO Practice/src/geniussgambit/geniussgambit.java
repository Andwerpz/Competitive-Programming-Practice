//package geniussgambit;

import java.util.*;
import java.io.*;

public class geniussgambit {
	public static void main(String[] args) throws IOException {
		
		//1492D
		
		//look at tutorial...
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int a = Integer.parseInt(st.nextToken());
		int b = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		if(k != 0 && ((a + b - 2) < k || (b == 0 && k != 0) || (b == 1 && k != 0) || (a == 0 && k != 0))) {
			System.out.println("NO");
		}
		else {
			System.out.println("YES");
			StringBuilder fout = new StringBuilder();
			if(b == 0) {
				fout.append("1");
				for(int i = 0; i < a; i++) {
					fout.append("0");
				}
				fout.append("\n");
				fout.append("1");
				for(int i = 0; i < a; i++) {
					fout.append("0");
				}
				fout.append("\n");
			}
			else {
				int firstZeroes = a - k;
				for(int i = 0; i < b; i++) {
					fout.append("1");
				}
				for(int i = 0; i < a; i++) {
					fout.append("0");
				}
				fout.append("\n");
				int count = 0;
				char[] ans = new char[a + b];
				for(int i = 0; i < ans.length; i++) {
					if(i < b) {
						ans[i] = '1';
					}
					else {
						ans[i] = '0';
					}
				}
				for(int i = b - 1; i < ans.length - 1; i++) {
					if(count == k) {
						break;
					}
					ans[i + 1] = '1';
					ans[i] = '0';
					count ++;
				}
				for(int i = b - 2; i > 0; i--) {
					if(count == k) {
						break;
					}
					ans[i] = '0';
					ans[i + 1] = '1';
					count ++;
				}
				fout.append(String.valueOf(ans)).append("\n");
			}
			System.out.print(fout);
		}
	}
}
