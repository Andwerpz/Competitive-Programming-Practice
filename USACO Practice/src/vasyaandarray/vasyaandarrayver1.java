package vasyaandarray;

import java.util.*;
import java.io.*;

public class vasyaandarrayver1 {
	public static void main(String[] args) throws IOException {
		
		//there is a much easier way to solve the problem: simulation
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		StringBuilder fout = new StringBuilder();
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int[] pfxSorted = new int[n * 2 + 3];
		int[] pfxUnsorted = new int[n * 2 + 3];
		ArrayList<int[]> unsorted = new ArrayList<int[]>();
		for(int i = 0; i < m; i++) {
			st = new StringTokenizer(fin.readLine());
			int which = Integer.parseInt(st.nextToken());
			int l = (Integer.parseInt(st.nextToken()) - 1) * 2 + 1;
			int r = (Integer.parseInt(st.nextToken()) - 1) * 2 + 1;
			if(which == 1) {
				pfxSorted[l] += 1;
				pfxSorted[r + 2] += -1;
			}
			else {
				unsorted.add(new int[] {l, r});
			}
		}
		for(int i : pfxSorted) {
			System.out.print(i + " ");
		}
		System.out.println();
		int pointer = 1000000;
		for(int i = 0; i < pfxSorted.length - 1; i++) {
			pfxSorted[i + 1] += pfxSorted[i];
			if(pfxSorted[i] == 0) {
				pfxUnsorted [i] += 1;
				pointer --;
			}
			else {
				pointer ++;
			}
			pfxUnsorted[i + 1] += pfxUnsorted[i];
			fout.append(pointer).append(" ");
		}
		for(int i = 0; i < pfxUnsorted.length; i++) {
			if(i % 2 == 1) {
				System.out.print(pfxSorted[i] + " ");
			}
		}
		System.out.println();
		boolean isValid = true;
		for(int i = 0; i < unsorted.size(); i++) {
			int[] next = unsorted.get(i);
			int l = next[0];
			int r = next[1];
			if(pfxUnsorted[l] == pfxUnsorted[r]) {
				isValid = false;
				break;
			}
		}
		if(isValid) {
			System.out.println("YES");
			System.out.println(fout);
		}
		else {
			System.out.println("NO");
		}
	}
}
