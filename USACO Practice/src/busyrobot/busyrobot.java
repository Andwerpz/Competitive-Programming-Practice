//package busyrobot;

import java.util.*;
import java.io.*;

public class busyrobot {
	public static void main(String[] args) throws IOException {
		
		//1463C
		
		//just go command by command and process them in order.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int[][] nums = new int[n][2];
			for(int i = 0; i < n; i++) {
				StringTokenizer st = new StringTokenizer(fin.readLine());
				nums[i][0] = Integer.parseInt(st.nextToken());
				nums[i][1] = Integer.parseInt(st.nextToken());
			}
			boolean hasDestination = false;
			int destination = 0;
			int position = 0;
			int ans = 0;
			for(int i = 0; i < n - 1; i++) {
				//System.out.println(destination + " " + position);
				if(!hasDestination) {
					destination = nums[i][1];
					hasDestination = true;
				}
				int curDest = nums[i][1];
				int timeUntilNext = Math.abs(nums[i][0] - nums[i + 1][0]);
				int low = position;
				int high = position;
				if(destination > position) {
					high = Math.min(destination, position + timeUntilNext);
					position = high;
					//System.out.println("GREATER THAN");
				}
				else if(destination < position) {
					low = Math.max(destination, position - timeUntilNext);
					position = low;
					//System.out.println("LESS THAN");
				}
				//System.out.println(low + " " + high);
				if(position == destination) {
					hasDestination = false;
				}
				if(low <= curDest && high >= curDest) {
					//System.out.println("YES: " + i);
					ans ++;
				}
			}
			if(!hasDestination) {
				ans ++;
			}
			else if(Math.min(position, destination) <= nums[n - 1][1] && Math.max(position, destination) >= nums[n - 1][1]) {
				ans ++;
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
