//package flipthebits;

import java.util.*;
import java.io.*;

public class flipthebits {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			char[] s1 = (fin.readLine() + "1").toCharArray();	//just have to be equal
			char[] s2 = (fin.readLine() + "1").toCharArray();
			int pfx = 0;
			boolean isValid = true;
			for(int i = 0; i < n; i++) {
				pfx += s1[i] == '1'? 1 : -1;
				//System.out.println(s1[i] + " " + s2[i] + " " + pfx);
				if((s1[i] == s2[i]) != (s1[i + 1] == s2[i + 1]) && pfx != 0){
					fout.append("NO\n");
					isValid = false;
					break;
				}
			}
			if(isValid) {
				fout.append("YES\n");
			}
		}
		System.out.println(fout);
	}
}
