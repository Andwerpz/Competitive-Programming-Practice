package newyearsproblem;

import java.util.*;
import java.io.*;

public class newyearsproblem {
	
	public static boolean isValid(int val, int[][] shops, int n, int m) {
		int[][] nums = new int[m][n];
		//first check if everyone is satisfied
		for(int i = 0; i < n; i++) {
			
		}
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int m = Integer.parseInt(st.nextToken());
			int n = Integer.parseInt(st.nextToken());
			int[][] shops = new int[m][n];
			for(int i = 0; i < m; i++) {
				st = new StringTokenizer(fin.readLine());
				for(int j = 0; j < n; j++) {
					shops[i][j] = Integer.parseInt(st.nextToken());
				}
			}
			int ans = 0;
			int low = 0;
			int high = 1000000000;
			int mid = low + (high - low) / 2;
			while(low <= high) {
				if(isValid(mid, shops, n, m)) {
					ans = Math.max(ans, mid);
					low = mid + 1;
				}
				else {
					high = mid - 1;
				}
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
