package boboniuandbitoperations;

import java.util.*;
import java.io.*;

public class boboniuandbitoperationsver1 {
	public static void main(String[] args) throws IOException {
		
		//this solution too greedy, we need to somehow prioritize something.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int[] a = new int[n];
		int[] b = new int[m];
		HashSet<Integer> visited = new HashSet<Integer>();
		int ans = 0;
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			a[i] = Integer.parseInt(st.nextToken());
		}
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < m; i++) {
			b[i] = Integer.parseInt(st.nextToken());
		}
		for(int i = 0; i < n; i++) {
			int min = Integer.MAX_VALUE;
			for(int j = 0; j < m; j++) {
				min = Math.min(min, a[i] & b[j]);
				if(visited.contains(a[i] & b[j])) {
					min = a[i] & b[j];
					break;
				}
			}
			visited.add(min);
			System.out.println(min);
			ans |= min;
		}
		System.out.println(ans);
	}
}
