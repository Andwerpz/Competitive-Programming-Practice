//package berryjam;

import java.util.*;
import java.io.*;

public class berryjam {
	public static void main(String[] args) throws IOException {
		
		//1278C
		
		//calculate for each amount of jam eaten on the left side, the minimum amount you need to eat on the right side to balance it out. Use a hash map or tree map
		//to make lookups fast.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int[] left = new int[n];
			int[] right = new int[n];
			for(int i = 0; i < n; i++) {
				left[i] = Integer.parseInt(st.nextToken());
			}
			for(int i = n - 1; i >= 0; i--) {
				right[i] = Integer.parseInt(st.nextToken());
				//System.out.println(right[i]);
			}
			HashMap<Integer, Integer> dict = new HashMap<Integer, Integer>();
			int sum = 0;
			dict.put(0, n);
			for(int i = 0; i < n; i++) {
				int next = left[i];
				sum += next == 1? -1 : 1;
				dict.put(sum, n - 1 - i);
			}
			//System.out.println(dict);
			sum = 0;
			int ans = 2 * n;
			for(int i = -1; i < n; i++) {
				int cur = n - i - 1;
				if(i == -1) {
					if(dict.containsKey(0)) {
						cur += dict.get(0);
						ans = Math.min(ans, cur);
					}
				}
				else {
					
					int next = right[i];
					sum += next == 1? -1 : 1;
					//System.out.println("SUM: " + sum + " CUR: " + cur);
					if(dict.containsKey(-sum)) {
						cur += dict.get(-sum);
						ans = Math.min(ans, cur);
					}
				}
				//System.out.println(ans + " " + i);
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
