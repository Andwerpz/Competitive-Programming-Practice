//package arrayreordering;

import java.util.*;
import java.io.*;

public class arrayreordering {
	
	public static int gcd(int a, int b) {
		if(b == 0) {
			return a;
		}
		return gcd(b, a % b);
	}
	
	public static void main(String[] args) throws IOException {\
		
		//1535B
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			ArrayList<Integer> evens = new ArrayList<Integer>();
			ArrayList<Integer> odds = new ArrayList<Integer>();
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				int next = Integer.parseInt(st.nextToken());
				if(next % 2 == 0) {
					evens.add(next);
				}
				else {
					odds.add(next);
				}
			}
			//System.out.println(odds);
			odds.sort((a, b) -> Integer.compare(a, b));
			int[] nums = new int[n];
			for(int i = 0; i < n; i++) {
				if(i < evens.size()) {
					nums[i] = evens.get(i);
				}
				else {
					nums[i] = odds.get(i - evens.size());
				}
			}
			long ans = 0;
			for(int i = 0; i < n; i++) {
				//System.out.print(nums[i] + " ");
				for(int j = i + 1; j < n; j++) {
					if(gcd(nums[i], nums[j] * 2) != 1) {
						ans ++;
					}
				}
			}
			//System.out.println();
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
