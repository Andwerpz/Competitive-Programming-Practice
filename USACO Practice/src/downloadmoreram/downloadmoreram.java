//package downloadmoreram;

import java.util.*;
import java.io.*;

public class downloadmoreram {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int k = Integer.parseInt(st.nextToken());
			int[][] nums = new int[n][2];
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i][0] = Integer.parseInt(st.nextToken());
			}
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i][1] = Integer.parseInt(st.nextToken());
			}
			Arrays.sort(nums, (a, b) -> Integer.compare(a[0], b[0]));
			for(int i = 0; i < n; i++) {
				if(k >= nums[i][0]) {
					k += nums[i][1];
				}
			}
			fout.append(k).append("\n");
		}
		System.out.print(fout);
	}
}
