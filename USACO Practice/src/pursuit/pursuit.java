//package pursuit;

import java.util.*;
import java.io.*;

public class pursuit {
	
	static Integer[] aPoints, bPoints;
	
	public static boolean isValid(int extra) {
		int amtCounted = (extra + aPoints.length) - (extra + aPoints.length) / 4;
		int b = 0;
		int a = extra * 100;
		for(int i = 0; i < Math.min(amtCounted, aPoints.length); i++) {
			b += bPoints[i];
		}
		for(int i = 0; i < amtCounted - extra; i++) {
			a += aPoints[i];
		}
		if(a >= b) {
			return true;
		}
		return false;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1530C
		
		//binary search the number of extra rounds.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			aPoints = new Integer[n];
			bPoints = new Integer[n];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			StringTokenizer stb = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				aPoints[i] = Integer.parseInt(st.nextToken());
				bPoints[i] = Integer.parseInt(stb.nextToken());
			}
			Arrays.sort(aPoints, Collections.reverseOrder());
			Arrays.sort(bPoints, Collections.reverseOrder());
			int high = 1000000;
			int low = 0;
			int mid = low + (high - low) / 2;
			int ans = high;
			while(low <= high) {
				if(isValid(mid)) {
					ans = Math.min(ans, mid);
					high = mid - 1;
				}
				else {
					low = mid + 1;
				}
				mid = low + (high - low) / 2;
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
