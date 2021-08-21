//package aquamoonandtwoarrays;

import java.util.*;
import java.io.*;

public class aquamoonandtwoarrays {
	public static void main(String[] args) throws IOException {
		
		//1546A
		
		//first, check whether you can make the two arrays equal. just check whether the sums of the two arrays are the same. 
		
		//Now, to make the two arrays equal. Find the first number in a that is lower than b, and the first that is higher. Do operations until they are equal, and move on.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int aSum = 0;
			int bSum = 0;
			int[] a = new int[n];
			int[] b = new int[n];
			for(int i = 0; i < n; i++) {
				a[i] = Integer.parseInt(st.nextToken());
				aSum += a[i];
			}
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				b[i] = Integer.parseInt(st.nextToken());
				bSum += b[i];
			}
			if(aSum == bSum) {
				int ans = 0;
				StringBuilder steps = new StringBuilder();
				int low = 0;
				int high = 0;
				while(low < n && high < n) {
					while(low != n && a[low] >= b[low]) {
						low ++;
					}
					while(high != n && a[high] <= b[high]) {
						high ++;
					}
					if(low == n) {
						break;
					}
					a[low] ++;
					a[high] --;
					steps.append(high + 1).append(" ").append(low + 1).append("\n");
					ans ++;
				}
				fout.append(ans).append("\n").append(steps);
			}
			else {
				fout.append("-1\n");
			}
		}
		System.out.print(fout);
	}
}
