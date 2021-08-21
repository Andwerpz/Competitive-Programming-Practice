//package moamenandksubarrays;

import java.util.*;
import java.io.*;

public class moamenandksubarrays {
	public static void main(String[] args) throws IOException {
		
		//1557B
		
		//just reverse engineer the answer. You can do this because all n integers are distinct. Therefore, you can look at where all the numbers are before and after the sort, 
		//and work out the minimum number of required segments to sort it. If k is greater or equal to this minimum, then you can sort it, else false.
		
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
				nums[i][1] = i;
			}
			int amt = 1;
			Arrays.sort(nums, (a, b) -> a[0] - b[0]);
			for(int i = 1; i < n; i++) {
				if(nums[i][1] != nums[i - 1][1] + 1) {
					amt ++;
				}
			}
			//System.out.println(amt);
			fout.append(k >= amt? "YES\n" : "NO\n");
		}
		System.out.print(fout);
	}
}
