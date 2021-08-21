//package yetanotherarrayrestoration;

import java.util.*;
import java.io.*;

public class yetanotherarrayrestoration {
	public static void main(String[] args) throws IOException {
		
		//1409C
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int x = Integer.parseInt(st.nextToken());
			int y = Integer.parseInt(st.nextToken());
			int diff = y - x;
			StringBuilder ans = new StringBuilder();
			int max = Integer.MAX_VALUE;
			for(int i = 1; i <= diff; i++) {
				if(diff % i == 0) {
					StringBuilder curAns = new StringBuilder();
					int amt = 0;
					int curMax = y;
					int pointer = y;
					boolean isValid = false;
					while(amt < n && pointer > 0) {
						amt ++;
						if(pointer == x) {
							isValid = true;
						}
						curAns.append(pointer).append(" ");
						pointer -= i;
					}
					pointer = y + i;
					while(amt < n) {
						amt ++;
						curAns.append(pointer).append(" ");
						curMax = pointer;
						pointer += i;
					}
					if(max > curMax && isValid) {
						max = curMax;
						ans = curAns;
					}
				}
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
