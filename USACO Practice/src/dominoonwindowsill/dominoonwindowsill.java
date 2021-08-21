//package dominoonwindowsill;

import java.util.*;
import java.io.*;

public class dominoonwindowsill {
	
	public static boolean isValid(int n, int k1, int k2, int w) {
		int remainder = Math.abs(k1 - k2);
		return Math.min(k1, k2) + remainder / 2 >= w;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1499A
		
		//you're just checking whether or not they can all be placed down, not if they can fill up the space.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int k1 = Integer.parseInt(st.nextToken());
			int k2 = Integer.parseInt(st.nextToken());
			st = new StringTokenizer(fin.readLine());
			int w = Integer.parseInt(st.nextToken());
			int b = Integer.parseInt(st.nextToken());
			boolean isValid = isValid(n, k1, k2, w) && isValid(n, n - k1, n - k2, b);
			fout.append(isValid? "YES\n" : "NO\n");
		}
		System.out.print(fout);
	}
}
