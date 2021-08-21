//package thirteenthlaborofheracles;

import java.util.*;
import java.io.*;

public class thirteenthlaborofheracles {
	public static void main(String[] args) throws IOException {
		
		//1466D
		
		//greedy solution: for the initial sum, sum up all edges and verticies. For each subsequent sum, add the maximum vertex that still has two edges pointing out of it.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			long sum = 0;
			long[] weights = new long[n];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				weights[i] = Integer.parseInt(st.nextToken());
				sum += weights[i];
			}
			int[] c = new int[n];
			for(int i = 0; i < n - 1; i++) {
				st = new StringTokenizer(fin.readLine());
				int a = Integer.parseInt(st.nextToken()) - 1;
				int b = Integer.parseInt(st.nextToken()) - 1;
				c[a] ++;
				c[b] ++;
			}
			ArrayList<Long> nums = new ArrayList<Long>();
			for(int i = 0; i < c.length; i++) {
				for(int j = 0; j < c[i] - 1; j++) {
					nums.add(weights[i]);
				}
			}
			nums.sort((a, b) -> -Long.compare(a, b));
			fout.append(sum).append(" ");
			for(int i = 0; i < nums.size(); i++) {
				sum += nums.get(i);
				fout.append(sum).append(" ");
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
