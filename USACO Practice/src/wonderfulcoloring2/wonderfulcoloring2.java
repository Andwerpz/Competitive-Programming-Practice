//package wonderfulcoloring2;

import java.util.*;
import java.io.*;

public class wonderfulcoloring2 {
	public static void main(String[] args) throws IOException {
		
		//1551B2
		
		//for groups that are larger than k, you can have a color set for each.
		
		//for all groups less than k, you can make sum / k color sets.
		
		//read tutorial pls.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int k = Integer.parseInt(st.nextToken());
			int[] nums = new int[n];
			int[] dict = new int[n];
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken()) - 1;
				dict[nums[i]] ++;
			}
			HashSet<Integer> lessThan = new HashSet<Integer>();
			int sum = 0;
			for(int i = 0; i < dict.length; i++) {
				if(dict[i] < k) {
					lessThan.add(i);
					sum += dict[i];
				}
				else {
					dict[i] = k;
				}
			}
			int[] ans = new int[n];
			int[] limit = new int[n];
			int multiple = sum / k;
			int max = multiple * k;
			//System.out.println(multiple + " " + sum);
			int pointer = -1;
			for(int i = 0; i < dict.length; i++) {
				if(lessThan.contains(i)) {
					if(pointer == max - 1) {
						dict[i] = -1;
					}
					else {
						int temp = pointer;
						pointer += dict[i];
						pointer = Math.min(pointer, max - 1);
						int diff = Math.abs(pointer - temp);
						limit[i] = diff;
						dict[i] = pointer;
					}
				}
			}
			//System.out.println(lessThan);
			int counter = 1;
			pointer = 1;
			for(int i = 0; i < nums.length; i++) {
				int next = nums[i];
				if(lessThan.contains(next)) {
					if(limit[next] == 0) {
						ans[i] = 0;
					}
					else {
						ans[i] = (dict[next] % k) + 1;
						dict[next] --;
						limit[next] --;
					}
				}
				else {
					ans[i] = Math.max(0, dict[next]);
					dict[next] --;
				}
				fout.append(ans[i]).append(" ");
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
