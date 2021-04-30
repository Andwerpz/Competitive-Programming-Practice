//package balancethebits;

import java.util.*;
import java.io.*;

public class balancethebits {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int[] s = new int[n];
			String input = fin.readLine();
			int num0 = 0;
			for(int i = 0; i < n; i++) {
				s[i] = Integer.parseInt(input.charAt(i) + "");
				num0 += s[i] == 0? 1 : 0;
			}
			if(num0 % 2 != 0 || s[0] != 1 || s[n - 1] != 1) {	//prerequisites
				fout.append("NO\n");
			}
			else {
				int num1 = n - num0;
				boolean isOpen = true;
				int num1Count = 0;
				fout.append("YES\n");
				StringBuilder a = new StringBuilder();
				StringBuilder b = new StringBuilder();
				for(int i = 0; i < n; i++) {
					if(s[i] == 1) {
						if(num1Count < num1 / 2) {
							a.append("(");
							b.append("(");
							num1Count++;
						}
						else {
							a.append(")");
							b.append(")");
						}
					}
					else {
						if(isOpen) {
							a.append("(");
							b.append(")");
							isOpen = !isOpen;
						}
						else {
							a.append(")");
							b.append("(");
							isOpen = !isOpen;
						}
					}
				}
				fout.append(a).append("\n").append(b).append("\n");
			}
		}
		System.out.print(fout);
	}
}
