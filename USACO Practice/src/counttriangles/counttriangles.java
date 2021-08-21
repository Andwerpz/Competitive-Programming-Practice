//package counttriangles;

import java.util.*;
import java.io.*;

public class counttriangles {
	public static void main(String[] args) throws IOException {
		
		//1355C
		
		//first, make a pfx array. for each range of x and y, how many different triangles can we make with all of z. Then loop through all ranges of x and y. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int a = Integer.parseInt(st.nextToken());
		int b = Integer.parseInt(st.nextToken());
		int c = Integer.parseInt(st.nextToken());
		int d = Integer.parseInt(st.nextToken());
		long[] pfx = new long[b + 1];
		int pointer = c;
		int increment = 0;
		for(int i = 0; i < pfx.length; i++) {
			if(i == 0) {
				pfx[i] = increment;
			}
			else {
				pfx[i] = pfx[i - 1] + increment;
			}
			if(pointer <= d) {
				increment ++;
			}
			pointer ++;
		}
		long ans = 0;
		for(int i = a; i <= b; i++) {
			int low = i + b - (c);
			int high = i + c - (c);
			low = Math.max(1, low);
			high = Math.max(0, high);
			low = Math.min(pfx.length, low);
			high = Math.min(pfx.length - 1, high);
			ans += pfx[high] - pfx[low - 1];
		}
		System.out.println(ans);
	}
}
