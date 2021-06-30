//package firecrackers;

import java.util.*;
import java.io.*;

public class firecrackers {
	
	static int n;
	static int m;
	static int a;
	static int b;
	static int[] crackers;
	
	public static boolean isValid(int val) {
		int crackerTime = 0;
		int totalTime = 0;
		if(a < b) {
			crackerTime = b - a - 1;
			totalTime = b - 1;
		}
		else {
			crackerTime = a - b - 1;
			totalTime = n - b;
		}
		if(crackerTime < val) {
			return false;
		}
		int curTime = 0;
		for(int i = val - 1; i >= 0; i--) {
			int endTime = curTime + crackers[i];
			if(endTime >= totalTime) {
				return false;
			}
			curTime ++;
		}
		return true;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1468D
		
		//make sure to not confuse variables 'n' and 'm'...
		
		//when setting off firecrackers, it is optimal to set off the ones of longer duration first, all the way down to the ones of shorter duration. You can't 
		//directly calculate the total since you have to first decide how many firecrackers you want to set off before you can check for validity. You can binary
		//search for the correct value though
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0 ) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			n = Integer.parseInt(st.nextToken());
			m = Integer.parseInt(st.nextToken());
			a = Integer.parseInt(st.nextToken());
			b = Integer.parseInt(st.nextToken());
			crackers = new int[m];
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < m; i++) {
				crackers[i] = Integer.parseInt(st.nextToken());
			}
			Arrays.sort(crackers);
			int high = m;
			int low = 0;
			int mid = low + (high - low) / 2;
			int ans = low;
			while(low <= high) {
				if(isValid(mid)) {
					if(ans < mid) {
						ans = mid;
					}
					low = mid + 1;
				}
				else {
					high = mid - 1;
				}
				mid = low + (high - low) / 2;
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
