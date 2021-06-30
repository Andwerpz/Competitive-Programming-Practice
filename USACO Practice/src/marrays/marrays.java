//package marrays;

import java.util.*;
import java.io.*;

public class marrays {
	public static void main(String[] args) throws IOException {
		
		//1497B
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());
			int[] dict = new int[m];
			int[] nums = new int[n];
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken()) % m;
				dict[nums[i]] ++;
			}
			int ans = 0;
			for(int i = 1; i <= m / 2; i++) {
				int count = Math.min(dict[i], dict[m - i]) + 1;
				if(dict[i] != 0 && dict[m - i] != 0) {
					ans ++;
					dict[i] -= count;
					dict[m - i] -= count;
				}
			}
			if(dict[0] != 0) {
				ans ++;
			}
			for(int i = 1; i < m; i++) {
				if(dict[i] > 0) {
					ans += dict[i];
				}
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
