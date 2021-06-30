//package fairplayoff;

import java.util.*;
import java.io.*;

public class fairplayoff {
	public static void main(String[] args) throws IOException {
		
		//1535A
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t -- > 0) {
			int n = 4;
			int[] nums = new int[n];
			int[][] sortedNums = new int[n][2];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
				sortedNums[i][0] = nums[i];
				sortedNums[i][1] = i;
			}
			Arrays.sort(sortedNums, (a, b) -> a[0] - b[0]);
			int val = sortedNums[0][1] + sortedNums[1][1];
			if(val == 1 || val == 5) {
				fout.append("NO\n");
			}
			else {
				fout.append("YES\n");
			}
		}
		System.out.print(fout);
	}
}
