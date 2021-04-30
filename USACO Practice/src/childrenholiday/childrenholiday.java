//package childrenholiday;

import java.util.*;
import java.io.*;

public class childrenholiday {
	
	static int[][] a;
	
	public static boolean isValid(long targetTime, int m) {
		long sum = 0;
		for(int i = 0; i < a.length; i++) {
			long cycleTime = a[i][0] * a[i][1] + a[i][2];
			sum += (targetTime / cycleTime) * a[i][1];
			long remainingTime = targetTime % cycleTime;
			sum += Math.min(a[i][1], remainingTime / a[i][0]);	//make sure that we don't go over into rest time
		}
		if(sum >= m) {
			return true;
		}
		else {
			return false;
		}
	}
	
	public static String constructList(long targetTime, int m) {
		StringBuilder fout = new StringBuilder();
		long total = 0;
		for(int i = 0; i < a.length; i++) {
			long sum = 0;
			long cycleTime = a[i][0] * a[i][1] + a[i][2];
			sum += (targetTime / cycleTime) * a[i][1];
			long remainingTime = targetTime % cycleTime;
			sum += Math.min(a[i][1], remainingTime / a[i][0]);	//make sure that we don't go over into rest time
			total += sum;
			if(total > m) {	//making sure that we don't produce more baloons than we have to
				long diff = m - total;
				//System.out.println(a[10000]);
				sum += diff;
				total += diff;
			}
			fout.append(sum).append(" ");
		}
		return fout.substring(0, fout.length() - 1);
	}
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int m = Integer.parseInt(st.nextToken());
		int n = Integer.parseInt(st.nextToken());
		a = new int[n][3];
		for(int i = 0; i < n; i++) {
			st = new StringTokenizer(fin.readLine());
			a[i] = new int[] {Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken())};
		}
		long low = 0;
		long high = Long.MAX_VALUE;
		long mid = low + (high - low) / 2;
		long ans = high;
		while(low <= high) {
			if(isValid(mid, m)) {
				if(mid < ans) {
					ans = mid;
				}
				high = mid - 1;
			}
			else {
				low = mid + 1;
			}
			mid = low + (high - low) / 2;
		}
		System.out.println(ans);
		System.out.println(constructList(ans, m));
	}
}
