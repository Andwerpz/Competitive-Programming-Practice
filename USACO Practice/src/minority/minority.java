//package minority;

import java.util.*;
import java.io.*;

public class minority {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			char[] s = fin.readLine().toCharArray();
			int zero = 0;
			int one = 0;
			for(int i = 0; i < s.length; i++) {
				if(s[i] == '0') {
					zero ++;
				}
				else {
					one ++;
				}
			}
			fout.append(zero == one? zero - 1 : Math.min(zero, one)).append("\n");
		}
		System.out.print(fout);
	}
}
