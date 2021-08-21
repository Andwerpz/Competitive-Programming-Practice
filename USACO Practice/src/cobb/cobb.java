package cobb;

import java.util.*;
import java.io.*;

public class cobb {
	public static void main(String[] args) throws IOException {
		
		//1554B
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		long[] powers = new long[20];
		for(int i = 1; i < powers.length; i++) {
			powers[i] = (int) Math.pow(2, i);
		}
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			long k = Integer.parseInt(st.nextToken());
			long ans = 0;
			for(int i = n; i >= 1; i--) {
				ans += i * ((i * (i - 1)) / 2);
				//System.out.println(ans);
			}
			//System.out.println(ans);
			int[][] pfx = new int[n][20];
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				int next = Integer.parseInt(st.nextToken());
				for(int j = 0; j <  20; j++) {
					if((next | (1 << j)) == next) {
						pfx[i][j] ++;
					}
					//System.out.println(1 << j);
					if(i != 0) {
						if(pfx[i][j] == 1) {
							ans -= ((long) (1 << j)) * i * k;
						}
						else {
							ans -= ((long) (1 << j)) * pfx[i - 1][j] * k;
						}
						pfx[i][j] += pfx[i - 1][j];
					}
				}
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
