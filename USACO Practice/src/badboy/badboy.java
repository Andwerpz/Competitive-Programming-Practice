//package badboy;

import java.util.*;
import java.io.*;

public class badboy {
	
	static long[] ans;
	
	public static long dist(long x1, long y1, long x2, long y2) {
		return Math.abs(x1 - x2) + Math.abs(y1 - y2);
	}
	
	public static void getAns(long x1, long y1, long n, long m) {
		long d1 = dist(x1, y1, 1, m) + dist(1, m, n, 1) + dist(n, 1, x1, y1);
		long d2 = dist(x1, y1, n, 1) + dist(n, 1, 1, m) + dist(1, m, x1, y1);
		//System.out.println(d1 + " " + d2);
		if(d1 > d2) {
			ans = new long[] {1, m, n, 1};
		}
		else {
			ans = new long[] {n, 1, 1, m};
		}
	}
	
	public static void main(String[] args) throws IOException {
		
		//1537B
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());
			int x1 = Integer.parseInt(st.nextToken());
			int y1 = Integer.parseInt(st.nextToken());
			ans = new long[4];
			getAns(x1, y1, n, m);
			for(long i : ans) {
				fout.append(i).append(" ");
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
