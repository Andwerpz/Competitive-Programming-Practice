//package needforpinkslips;

import java.util.*;
import java.io.*;

public class needforpinkslips {
	
	static long scale;
	
	public static double getAns(long c, long m, long p, long v) {
		double ans = (double) p / scale;
		//System.out.println(ans);
		if(c > 0) {
			if(c > v) {
				if(m > 0) {
					ans += ((double) c / scale) * (1 + getAns(c - v, m + v / 2, p + v / 2, v));
				}
				else {
					ans += ((double) c / scale) * (1 + getAns(c - v, 0, p + v, v));
				}
			}
			else {
				if(m > 0) {
					ans += ((double) c / scale) * (1 + getAns(0, m + c / 2, p + c / 2, v));
				}
				else {
					ans += ((double) c / scale) * (1 + getAns(0, 0, p + c, v));
				}
			}
		}
		if(m > 0) {
			if(m > v) {
				if(c > 0) {
					ans += ((double) m / scale) * (1 + getAns(c + v / 2, m - v, p + v / 2, v));
				}
				else {
					ans += ((double) m / scale) * (1 + getAns(0, m - v, p + v, v));
				}
			}
			else {
				if(c > 0) {
					ans += ((double) m / scale) * (1 + getAns(c + m / 2, 0, p + m / 2, v));
				}
				else {
					ans += ((double) m / scale) * (1 + getAns(0, 0, p + m, v));
				}
			}
		}
		return ans;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1543C
		
		//probability problem with floating point precision. In these types of problems, if you have a error margin, convert all doubles into longs and just use the longs
		//to do the calculations. After calculating, just convert back into double.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		scale = 10000000;
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			long c = (long) (Double.parseDouble(st.nextToken()) * scale);
			long m = (long) (Double.parseDouble(st.nextToken()) * scale);
			long p = (long) (Double.parseDouble(st.nextToken()) * scale);
			long v = (long) (Double.parseDouble(st.nextToken()) * scale);
			fout.append(getAns(c, m, p, v)).append("\n");
		}
		System.out.print(fout);
	}
}
