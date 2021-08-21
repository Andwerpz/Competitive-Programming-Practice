//package maximumcostdeletion;

import java.util.*;
import java.io.*;

public class maximumcostdeletion {
	public static void main(String[] args) throws IOException {
		
		//1550B
		
		//there are two cases, when b is greater than or equal to 0, and when b is less than 0. the cost for a stays constant; it is linearly related to the size of the array.
		
		//when b is greater or equal to 0, then remove each character in the string separately. This will maximize the b cost. 
		
		//when b is less than 0, you have to remove the minimum amount of substrings. Find out how many groups of 1 and 0s there are, and whichever group has the least amount of
		//groups, remove all of that type. Then you can remove all of the other type in one operation.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int a = Integer.parseInt(st.nextToken());
			int b = Integer.parseInt(st.nextToken());
			char[] s = fin.readLine().toCharArray();
			int ans = 0;
			if(b >= 0) {
				ans = a * n + b * n;
			}
			else {
				int numZero = 0;
				int numOne = 0;
				char prev = 0;
				for(int i = 0; i < n; i++) {
					if(i == 0) {
						prev = s[0];
					}
					else {
						if(s[i] != prev) {
							if(prev == '0') {
								numZero ++;
							}
							else {
								numOne ++;
							}
							prev = s[i];
						}
					}
				}
				if(prev == '0') {
					numZero ++;
				}
				else {
					numOne ++;
				}
				ans += Math.min(numZero, numOne) * b;
				ans += b;
				ans += n * a;
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
