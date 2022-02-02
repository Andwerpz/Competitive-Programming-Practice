//package abc;

import java.util.*;
import java.io.*;

public class abc {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		int t = Integer.parseInt(fin.readLine());
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			char[] s = fin.readLine().toCharArray();
			if(n >= 3) {
				fout.append("NO\n");
				continue;
			}
			if(n == 1) {
				fout.append("YES\n");
				continue;
			}
			fout.append(s[0] == s[1]? "NO\n" : "YES\n");
		}
		System.out.print(fout);
	}
}
