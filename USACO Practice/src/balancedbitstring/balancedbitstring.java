//package balancedbitstring;

import java.util.*;
import java.io.*;

public class balancedbitstring {
	public static void main(String[] args) throws IOException {
		
		//1404A
		
		//a balanced bitstring will be k-cyclic. Just see if you can make the string k-cyclic while making the first k bits balanced.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int k = Integer.parseInt(st.nextToken());
			char[] s = fin.readLine().toCharArray();
			boolean isValid = true;
			int num0 = 0;
			int num1 = 0;
			int numQ = 0;
			for(int i = 0; i < k; i++) {
				if(s[i] == '0') {
					num0 ++;
				}
				else if(s[i] == '1') {
					num1 ++;
				}
				else {
					numQ ++;
				}
			}
			outer:
			for(int i = 0; i < k; i++) {
				char cur = s[i];
				boolean changed = false;
				for(int j = i + k; j < n; j += k) {
					char next = s[j];
					//System.out.print(next + " ");
					if(cur == '?') {
						if(next == '0') {
							cur = '0';
							changed = true;
						}
						else if(next == '1') {
							cur = '1';
							changed = true;
						}
					}
					else {
						if(next != cur && next != '?') {
							isValid = false;
							break outer;
						}
					}
				}
				//System.out.println();
				if(changed) {
					numQ --;
					if(cur == '0') {
						num0 ++;
					}
					else {
						num1 ++;
					}
				}
			}
			if(num0 > k / 2 || num1 > k / 2) {
				isValid = false;
			}
			fout.append(isValid? "YES\n" : "NO\n");
		}
		System.out.print(fout);
	}
}
