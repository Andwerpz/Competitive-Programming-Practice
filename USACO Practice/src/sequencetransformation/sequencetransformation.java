//package sequencetransformation;

import java.util.*;
import java.io.*;

public class sequencetransformation {
	public static void main(String[] args) throws IOException {
		
		//1454C
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			HashMap<Integer, Integer> dict = new HashMap<Integer, Integer>();
			int prev = -1;
			for(int i = 0; i < n; i++) {
				int next = Integer.parseInt(st.nextToken());
				if(i == 0 || i == n - 1) {
					dict.put(next, dict.getOrDefault(next, 0));
					if(next == prev) {
						dict.put(next, dict.getOrDefault(next, 0) - 1);
					}
				}
				else {
					if(next != prev) {
						dict.put(next, dict.getOrDefault(next, 0) + 1);
					}
					else {
						dict.put(next, dict.getOrDefault(next, 0));
					}
				}
				prev = next;
			}
			int ans = Integer.MAX_VALUE;
			for(int i : dict.keySet()) {
				ans = Math.min(ans, dict.get(i) + 1);
			}
			if(dict.size() == 1) {
				ans = 0;
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
