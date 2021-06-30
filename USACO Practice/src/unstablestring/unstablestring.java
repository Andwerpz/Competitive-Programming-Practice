//package unstablestring;

import java.util.*;
import java.io.*;

public class unstablestring {
	public static void main(String[] args) throws IOException {
		
		//1535C
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			char[] s = fin.readLine().toCharArray();
			boolean next = false;	//false for 0, true for 1.
			int pointer = 0;
			long ans = 0;
			if(s[0] == '0') {
				next = false;
			}
			else if(s[0] == '1') {
				next = true;
			}
			int n = s.length;
			boolean undetermined = s[0] == '?'? true : false;
			for(int i = 0; i < n; i++) {
				if(undetermined) {
					if(s[i] == '0') {
						undetermined = false;
						next = true;
					}
					else if(s[i] == '1') {
						undetermined = false;
						next = false;
					}
				}
				else {
					boolean reset = false;
					if(s[i] == '?') {
						next = !next;
					}
					else if(next && s[i] == '0') {
						reset = true;
						pointer = i;
						next = true;
					}
					else if(!next && s[i] == '1') {
						reset = true;
						pointer = i;
						next = false;
					}
					else {
						next = !next;
					}
					while(pointer - 1 != -1 && s[pointer - 1] == '?' && reset) {
						pointer --;
					}
				}
				//System.out.println(pointer + " " + i);
				ans += i - pointer + 1;
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
