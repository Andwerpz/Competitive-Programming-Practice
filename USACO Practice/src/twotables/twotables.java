//package twotables;

import java.util.*;
import java.io.*;

public class twotables {
	public static void main(String[] args) throws IOException {
		
		//1555B
		
		//notice that the fastest way to move the table is to either move it vertically or horizontally. If you can't do one of those, then there is not enough room for both tables.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int w = Integer.parseInt(st.nextToken());
			int h = Integer.parseInt(st.nextToken());
			st = new StringTokenizer(fin.readLine());
			int x1 = Integer.parseInt(st.nextToken());
			int y1 = Integer.parseInt(st.nextToken());
			int x2 = Integer.parseInt(st.nextToken());
			int y2 = Integer.parseInt(st.nextToken());
			st = new StringTokenizer(fin.readLine());
			int w2 = Integer.parseInt(st.nextToken());
			int h2 = Integer.parseInt(st.nextToken());
			int ans = -1;
			if(x2 - x1 + w2 <= w) {
				if(ans == -1) {
					ans = Integer.MAX_VALUE;
				}
				ans = Math.min(ans, Math.max(w2 - x1, 0));
				//System.out.println(w2 - x1);
				ans = Math.min(ans, Math.max(x2 - (w - w2), 0));
				//System.out.println((w - w2) - x2);
			}
			if(y2 - y1 + h2 <= h) {
				if(ans == -1) {
					ans = Integer.MAX_VALUE;
				}
				ans = Math.min(ans, Math.max(h2 - y1, 0));
				//System.out.println((h2 - y1));
				ans = Math.min(ans, Math.max(y2 - (h - h2), 0));
				//System.out.println((h - h2) - y2);
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
