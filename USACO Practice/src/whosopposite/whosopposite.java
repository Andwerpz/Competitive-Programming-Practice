//package whosopposite;

import java.util.*;
import java.io.*;

public class whosopposite {
	public static void main(String[] args) throws IOException {
		
		//1560B
		
		//a and b are not necessarily from a valid table setup.
		
		//to check, just look at the difference between a and b. If the table setup is valid, then the difference must be at least as large as the smallest out of a and b.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int a = Integer.parseInt(st.nextToken());
			int b = Integer.parseInt(st.nextToken());
			int c = Integer.parseInt(st.nextToken());
			int n = Math.abs(a - b) * 2;
			int ans = -1;
			if(c <= n && Math.abs(a - b) >= Math.min(a, b)) {
				if(c <= n / 2) {
					//System.out.println("YES");
					ans = c + Math.abs(a - b);
				}
				else {
					ans = c - Math.abs(a - b);
				}
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
