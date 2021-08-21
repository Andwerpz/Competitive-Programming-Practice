//package thetreasureofthesegments;

import java.util.*;
import java.io.*;

public class thetreasureofthesegments {
	
	public static int numAbove(Integer[] nums, int val) {
		if(nums[0] > val) {
			return nums.length;
		}
		int high = nums.length - 1;
		int low = 0;
		int mid = low + (high - low) / 2;
		int ans = 0;
		while(low <= high) {
			//System.out.println(nums[mid] + " " + val);
			if(nums[mid] <= val) {
				
				low = mid + 1;
				ans = Math.max(ans, mid);
				//System.out.println(mid + " " + ans);
			}
			else {
				//System.out.println("HIG");
				high = mid - 1;
			}
			mid = low + (high - low) / 2;
		}
		return nums.length - (ans + 1);
	}
	
	public static int numBelow(Integer[] nums, int val) {
		if(nums[0] >= val) {
			return 0;
		}
		int high = nums.length - 1;
		int low = 0;
		int mid = low + (high - low) / 2;
		int ans = 0;
		while(low <= high) {
			if(nums[mid] < val) {
				low = mid + 1;
				ans = Math.max(ans, mid);
			}
			else {
				high = mid - 1;
			}
			mid = low + (high - low) / 2;
		}
		return ans + 1;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1462F
		
		//just check for the number of segments that are above and below this segment, and then take the minimum sum out of all the segments.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			Integer[] starts = new Integer[n];
			Integer[] ends = new Integer[n];
			int[][] nums = new int[n][2];
			for(int i = 0; i < n; i++) {
				StringTokenizer st = new StringTokenizer(fin.readLine());
				starts[i] = Integer.parseInt(st.nextToken());
				ends[i] = Integer.parseInt(st.nextToken());
				nums[i] = new int[] {starts[i], ends[i]};
			}
			Arrays.sort(starts);
			Arrays.sort(ends);
			int ans = Integer.MAX_VALUE;
			for(int i = 0; i < n; i++) {
				int curAns = numBelow(ends, nums[i][0]) + numAbove(starts, nums[i][1]);
				curAns = Math.max(curAns, 0);
				//System.out.println(numBelow(ends, nums[i][0]) + " " + numAbove(starts, nums[i][1]));
				ans = Math.min(ans, curAns);
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
