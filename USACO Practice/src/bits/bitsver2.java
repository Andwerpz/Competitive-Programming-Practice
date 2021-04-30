package bits;

import java.util.*;
import java.io.*;

public class bitsver2 {
	
	public static long solve(long l, long r) {
		if(l == r) {
			return l;
		}
		long b = (long) Math.pow(2, Math.floor(Math.log(r) / Math.log(2)));
		if(b <= l) {
			return solve(l - b, r - b) + b;
		}
		else if(b * 2 - 1 <= r) {
			return b * 2 - 1;
		}
		else {
			return b - 1;
		}
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(n -- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			long l = Long.parseLong(st.nextToken());
			long r = Long.parseLong(st.nextToken());
			fout.append(solve(l, r)).append("\n");
		}
		System.out.print(fout);
	}
}
