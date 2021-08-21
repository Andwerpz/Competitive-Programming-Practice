//package airconditioners;

import java.util.*;
import java.io.*;

public class airconditioners {
	public static void main(String[] args) throws IOException {
		
		//1547E
		
		//for every cell, we need to consider every single air conditioner in order to find the minimum temperature it can be at. To do this, we can make a pfx and sfx minimum array
		//the pfx array will only be concerned with air conditioners to the left, and the sfx will only be concerned with ones to the right. Doing this is linear time, and to get the 
		//actual temp of the cell, just take the minimum out of the pfx and sfx for that cell.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int q = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(q-- > 0) {
			fin.readLine();
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int k = Integer.parseInt(st.nextToken());
			int[][] nums = new int[k][2];
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < k; i++) {
				nums[i][0] = Integer.parseInt(st.nextToken());
			}
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < k; i++) {
				nums[i][1] = Integer.parseInt(st.nextToken());
			}
			Arrays.sort(nums, (a, b) -> a[0] - b[0]);
			int[] pfx = new int[n];
			int[] sfx = new int[n];
			int pointer = -1;
			for(int i = 0; i < n; i++) {
				int cur = i + 1;
				int curTemp = Integer.MAX_VALUE / 2;
				if(i != 0) {
					curTemp = pfx[i - 1] + 1;
				}
				while(pointer + 1 < k && nums[pointer + 1][0] <= cur) {
					pointer ++;
					curTemp = Math.min(curTemp, nums[pointer][1] + Math.abs(cur - nums[pointer][0]));
				}
				pfx[i] = curTemp;
				//System.out.print(pfx[i] + " ");
			}
			//System.out.println();
			pointer = k;
			for(int i = n - 1; i >= 0; i --) {
				int cur = i + 1;
				int curTemp = Integer.MAX_VALUE / 2;
				if(i != n - 1) {
					curTemp = sfx[i + 1] + 1;
				}
				while(pointer - 1 >= 0 && nums[pointer - 1][0] >= cur) {
					pointer --;
					curTemp = Math.min(curTemp, nums[pointer][1] + Math.abs(cur - nums[pointer][0]));
				}
				sfx[i] = curTemp;
				//System.out.print(sfx[i] + " ");
			}
			//System.out.println();
			for(int i = 0; i < n; i++) {
				fout.append(Math.min(pfx[i], sfx[i])).append(" ");
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
