//package bornthisway;

import java.util.*;
import java.io.*;

public class bornthisway {
	
	static int[] aFlights;
	static int[] bFlights;
	static int k;
	static int[][] pfx;
	static int[][] flights;
	static int firstA;
	
	public static boolean isValid(int val) {
		//System.out.println(val);
		for(int i = 0; i < val; i++) {
			if(pfx[i][0] + (pfx[val][1] - 1 - pfx[i][1]) <= k) {
				return true;
			}
		}
		if(pfx[val][1] - pfx[firstA][1] <= k) {
			return true;
		}
		return false;
	}
	
	public static int search(int val) {
		//System.out.println("SEARCHing");
		for(int i = 0; i < flights.length; i++) {
			//System.out.println(flights[i][0] + " " + flights[i][1]);
			if(flights[i][1] == 1 && flights[i][0] == val) {
				//System.out.println("found it");
				return i;
			}
		}
		return 0;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1148B
		
		//ok, no explanation for this one. Refer to the tutorial for help, my implementation is too complicated lol
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int ta = Integer.parseInt(st.nextToken());
		int tb = Integer.parseInt(st.nextToken());
		k = Integer.parseInt(st.nextToken());
		aFlights = new int[n];
		bFlights = new int[m];
		flights = new int[n + m][2];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			aFlights[i] = Integer.parseInt(st.nextToken()) + ta;
			flights[i][0] = aFlights[i];
			flights[i][1] = 0;
		}
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < m; i++) {
			bFlights[i] = Integer.parseInt(st.nextToken());
			flights[i + n][0] = bFlights[i];
			flights[i + n][1] = 1;
		}
		Arrays.sort(aFlights);
		Arrays.sort(bFlights);
		Arrays.sort(flights, (a, b) -> Comparator.compareIntArr(a, b));
//		for(int[] i : flights) {
//			System.out.println(i[0] + " " + i[1]);
//		}
		pfx = new int[n + m][2];
		for(int i = 0; i < pfx.length; i++) {
			if(i != 0) {
				pfx[i][0] += pfx[i - 1][0];
				pfx[i][1] += pfx[i - 1][1];
			}
			pfx[i][flights[i][1]] ++;
		}
		boolean canCancelAll = false;
		for(int i = 0; i < pfx.length; i++) {
			if(pfx[i][0] + (pfx[pfx.length - 1][1] - pfx[i][1]) <= k) {
				canCancelAll = true;
				break;
			}
		}
		if(k == n || k == m) {	//why we need this???
			canCancelAll = true;
		}
		if(canCancelAll) {
			System.out.println(-1);
		}
		else {
			firstA = 0;
			for(int i = 0; i < pfx.length; i++) {
				if(pfx[i][1] != 0) {
					firstA = i;
					break;
				}
			}
			int high = m - 1;
			int low = 0;
			int mid = low + (high - low) / 2;
			int ans = -1;
			while(low <= high) {
				//System.out.println("MID: " + mid);
				if(isValid(search(bFlights[mid]))) {
					//System.out.println("VALID");
					ans = Math.max(ans, bFlights[mid]);
					low = mid + 1;
				}
				else {
					high = mid - 1;
				}
				mid = low + (high - low) / 2;
			}
			System.out.println(ans + tb);
		}
	}
	
	static class Comparator {
		public static int compareIntArr(int[] a, int[] b) {
			return a[0] == b[0]? Integer.compare(a[1], b[1]) : Integer.compare(a[0], b[0]);
		}
	}
	
}
