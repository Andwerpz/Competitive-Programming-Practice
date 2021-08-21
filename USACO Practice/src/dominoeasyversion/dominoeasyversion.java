//package dominoeasyversion;

import java.util.*;
import java.io.*;

public class dominoeasyversion {
	public static void main(String[] args) throws IOException {
		
		//1551D1
		
		//if n and m are even, you can essentially tile your dominoes in 2x2 tiles, each consisting of two horizontal or vertical tiles. This means that if both n and m are even, then if k is even, 
		//then you can fill the space with dominoes.
	
		//in the other case where one n or m is uneven, you can make the space into an even sided space by filling up either one row or column. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());
			int k = Integer.parseInt(st.nextToken());
			int total = n * m;
			total /= 2;
			if(n % 2 == 0 && m % 2 == 0) {
				if(k % 2 == 0) {
					fout.append("YES\n");
				}
				else {
					fout.append("NO\n");
				}
			}
			else {
				if(m % 2 == 1) {
					int temp = n;
					n = m;
					m = temp;
					k = total - k;
				}
				if(k < m / 2) {
					fout.append("NO\n");
				}
				else {
					k -= m / 2;
					if(k % 2 == 0) {
						fout.append("YES\n");
					}
					else {
						fout.append("NO\n");
					}
				}
			}
		}
		System.out.print(fout);
	}
}
