//package weboflies;

import java.util.*;
import java.io.*;

public class weboflies {
	public static void main(String[] args) throws IOException {
		
		//1549C
		
		//notice that only the nobles that are only friends with weaker nobles will survive. If a noble has a friend that is stronger than him, then he will die. Given this, we can keep 
		//track for each noble how many friends they have that are more powerful than themselves. The answer for each query is the number of nobles that don't have friends more powerful
		//than themselves.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int[] greaterThan = new int[n];
		for(int i = 0; i < m; i++) {
			st = new StringTokenizer(fin.readLine());
			int a = Integer.parseInt(st.nextToken()) - 1;
			int b = Integer.parseInt(st.nextToken()) - 1;
			greaterThan[Math.min(a, b)] ++;
		}
		int ans = 0;
		for(int i = 0; i < n; i++) {
			if(greaterThan[i] == 0) {
				ans ++;
			}
		}
		StringBuilder fout = new StringBuilder();
		int q = Integer.parseInt(fin.readLine());
		while(q-- > 0) {
			st = new StringTokenizer(fin.readLine());
			int which = Integer.parseInt(st.nextToken());
			if(which == 1) {
				int a = Integer.parseInt(st.nextToken()) - 1;
				int b = Integer.parseInt(st.nextToken()) - 1;
				greaterThan[Math.min(a, b)] ++;
				if(greaterThan[Math.min(a, b)] == 1) {
					ans --;
				}
			}
			else if(which == 2) {
				int a = Integer.parseInt(st.nextToken()) - 1;
				int b = Integer.parseInt(st.nextToken()) - 1;
				greaterThan[Math.min(a, b)] --;
				if(greaterThan[Math.min(a, b)] == 0) {
					ans ++;
				}
			}
			else {
				fout.append(ans).append("\n");
			}
		}
		System.out.print(fout);
	}
}
