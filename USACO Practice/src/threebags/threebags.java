package threebags;

import java.util.*;
import java.io.*;

public class threebags {
	
	public static long getAns(ArrayList<Long> keep, ArrayList<Long> keep2, ArrayList<Long> remove) {
		keep.sort((a, b) -> Long.compare(a, b));
		keep2.sort((a, b) -> Long.compare(a, b));
		remove.sort((a, b) -> Long.compare(a, b));
		if(keep.size() != 1 || remove.size() != 1) {
			
		}
		long sum = 0;
		for(long i : keep) {
			sum += i;
		}
		long removeSum = 0;
		
		return sum - remove.get(0);
	}
	
	public static void main(String[] args) throws IOException {
		
		//1467C
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n1 = Integer.parseInt(st.nextToken());
		int n2 = Integer.parseInt(st.nextToken());
		int n3 = Integer.parseInt(st.nextToken());
		int[] a = new int[n1];
		int[] b = new int[n2];
		int[] c = new int[n3];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n1; i++) {
			a[i] = Integer.parseInt(st.nextToken());
		}
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n2; i++) {
			b[i] = Integer.parseInt(st.nextToken());
		}
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n3; i++) {
			c[i] = Integer.parseInt(st.nextToken());
		}
	}
}
