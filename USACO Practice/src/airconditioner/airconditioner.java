//package airconditioner;

import java.util.*;
import java.io.*;

public class airconditioner {
	public static void main(String[] args) throws IOException {
		
		//1304C
		
		//this problem is like the fence problem that i did maybe a couple weeks earlier.
		
		//be careful, there might be multiple visitors at the same time. Just combine their ranges, and if their ranges don't intersect, then the input is invalid.
		
		//All you have to do is between each set of guests, just calculate the upper and lower bound that you can set the temp to. If this intersects with their preferred temp range,
		//then calculate the possible range of temps that you can set it to within their range, and repeat. If the possible range doesn't intersect, then the input is invalid
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());
			int[][] people = new int[n][3];
			for(int i = 0; i < n; i++) {
				st = new StringTokenizer(fin.readLine());
				int time = Integer.parseInt(st.nextToken());
				int low = Integer.parseInt(st.nextToken());
				int high = Integer.parseInt(st.nextToken());
				people[i] = new int[] {time, low, high};
			}
			int low = m;
			int high = m;
			boolean isValid = true;
			for(int i = 0; i < n; i++) {
				int prevTime = 0;
				if(i != 0) {
					prevTime = people[i - 1][0];
				}
				int curTime = people[i][0];
				int curLow = people[i][1];
				int curHigh = people[i][2];
				while(i + 1 < n && curTime == people[i + 1][0]) {
					i++;
					curLow = Math.max(curLow, people[i][1]);
					curHigh = Math.min(curHigh, people[i][2]);
				}
				if(curLow > curHigh) {
					isValid = false;
					break;
				}
				int diff = curTime - prevTime;
				int possLow = low - diff;
				int possHigh = high + diff;
				if(possLow < curLow && possHigh < curLow || possLow > curHigh && possHigh > curHigh) {
					isValid = false;
					break;
				}
				low = Math.max(possLow, curLow);
				high = Math.min(possHigh, curHigh);
			}
			if(isValid) {
				fout.append("YES\n");
			}
			else {
				fout.append("NO\n");
			}
		}
		System.out.print(fout);
	}
}
