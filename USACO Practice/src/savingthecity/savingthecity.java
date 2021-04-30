//package savingthecity;

import java.util.*;
import java.io.*;

public class savingthecity {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t -- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int a = Integer.parseInt(st.nextToken());
			int b = Integer.parseInt(st.nextToken());
			char[] s = fin.readLine().toCharArray();
			int n = s.length;
			ArrayList<Integer> nums = new ArrayList<Integer>();	//starts with 0 section
			char prev = '0';
			nums.add(0);
			for(int i = 0; i < n; i++) {
				if(s[i] == prev) {
					nums.set(nums.size() - 1, nums.get(nums.size() - 1) + 1);
				}
				else {
					nums.add(1);
					prev = s[i];
				}
				//System.out.print(s[i]);
			}
			int ans = 0;
			for(int i = 1; i < nums.size(); i++) {
				//System.out.print(nums.get(i) + " ");
				if(i % 2 == 1) {
					ans += a;
					//System.out.print("odd");
				}
				else {
					if(i + 1 != nums.size()) {
						if(b * nums.get(i) < a) {
							ans -= a;
							ans += b * nums.get(i);
						}
					}
				}
			}
			//System.out.println();
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
