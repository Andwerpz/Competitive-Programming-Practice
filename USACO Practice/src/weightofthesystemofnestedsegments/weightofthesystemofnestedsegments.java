//package weightofthesystemofnestedsegments;

import java.util.*;
import java.io.*;

public class weightofthesystemofnestedsegments {
	public static void main(String[] args) throws IOException {
		
		//1650C
		
		//notice that if you choose any even number of points, you can always make a nested system of segments out of them
		
		//so you just have to choose an even set of the least value points.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		int t = Integer.parseInt(fin.readLine());
		while(t-- > 0) {
			fin.readLine();
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());
			int[][] nums = new int[m][4]; 	//coord, weight, original index, flag
			for(int i = 0; i < m; i++) {
				st = new StringTokenizer(fin.readLine());
				nums[i][0] = Integer.parseInt(st.nextToken());
				nums[i][1] = Integer.parseInt(st.nextToken());
				nums[i][2] = i + 1;
			}
			Arrays.sort(nums, (a, b) -> Integer.compare(a[1], b[1]));	//sort by weight
			//mark the first 2n least weights
			int sum = 0;
			for(int i = 0; i < n * 2; i++) {
				nums[i][3] = 1;
				sum += nums[i][1];
			}
			Arrays.sort(nums, (a, b) -> Integer.compare(a[0], b[0]));	//sort by coord
			int l = 0;
			int r = m - 1;
			ArrayList<int[]> ans = new ArrayList<int[]>();
			for(int i = 0; i < n; i++) {
				while(nums[l][3] != 1) {
					l ++;
				}
				while(nums[r][3] != 1) {
					r --;
				}
				ans.add(new int[] {nums[l][2], nums[r][2]});
				l++;
				r--;
			}
			fout.append(sum).append("\n");
			for(int[] i : ans) {
				fout.append(i[0]).append(" ").append(i[1]).append("\n");
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
