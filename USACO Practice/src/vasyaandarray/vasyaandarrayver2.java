package vasyaandarray;

import java.util.*;
import java.io.*;

public class vasyaandarrayver2 {
	public static void main(String[] args) throws IOException {
		
		//the problem describes an unknown array. You are given segments, and told that they are either sorted non descending, or not. Your job is to reconstruct any array
		//that fits the criteria given, or print "NO" if there is no array that fits the criteria. First, we must see that in order for no array to fit the criteria, 
		//there must be conflicting criteria. There is only conflicting criteria if a non-sorted segment is completely within a sorted segment. To check whether this is true or not
		//we just build the array, only using the information from the sorted segments; make sure that everything within the sorted segments are ascending, and the rest are descending.
		//then we just check whether the non sorted segment's criteria are met. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int[] pfx = new int[n * 2 + 1];
		int[] pfxUnsorted = new int[n * 2 + 1];
		ArrayList<int[]> unsorted = new ArrayList<int[]>();
		for(int i = 0; i < m; i++) {
			st = new StringTokenizer(fin.readLine());
			int which = Integer.parseInt(st.nextToken());
			int l = (Integer.parseInt(st.nextToken()) - 1) * 2 + 1;
			int r = (Integer.parseInt(st.nextToken()) - 1) * 2;
			if(which == 1) {
				pfx[l] += 1;
				if(r != n * 2) {
					pfx[r + 2] += -1;
				}
				else {
					//System.out.println("FAOL " + i);
				}
			}
			else {
				unsorted.add(new int[] {l, r});
			}
//			for(int j : pfx) {
//				System.out.print(j + " ");
//			}
//			System.out.println();
		}
		
		for(int i = 0; i < pfx.length - 1; i++) {
			pfx[i + 1] += pfx[i];
			pfxUnsorted[i + 1] += pfxUnsorted[i] + (pfx[i] == 0? 1 : 0);
		}
//		for(int i : pfxUnsorted) {
//			System.out.print(i + " ");
//		}
//		System.out.println();
		int pointer = 1000000;
		StringBuilder fout = new StringBuilder();
		for(int i = 1; i < pfx.length; i += 2) {
			if(pfx[i - 1] == 0) {
				pointer --;
			}
			else {
				pointer ++;
			}
			fout.append(pointer).append(" ");
		}
		boolean isValid = true;
		for(int i = 0; i < unsorted.size(); i++) {
			int[] next = unsorted.get(i);
			int l = next[0];
			int r = next[1] + 1;
			if(pfxUnsorted[l] == pfxUnsorted[r]) {
				isValid = false;
				break;
			}
		}
		if(isValid) {
			System.out.println("YES\n" + fout);
		}
		else {
			System.out.println("NO");
		}
	}
}
