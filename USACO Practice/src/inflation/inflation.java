package inflation;

import java.util.*;
import java.io.*;

public class inflation {
	public static void main(String[] args) throws IOException {
		
		//1476B
		
		//solve later 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int k = Integer.parseInt(st.nextToken());
			long[] nums = new long[n];
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			long sum = nums[0];
			long ans = 0;
			for(int i = 1; i < n; i++) {
				long next = nums[i];
				long percentage = sum * k;
				long total = next * 100;
				if(total > percentage) {
					
				}
			}
		}
	}
}
