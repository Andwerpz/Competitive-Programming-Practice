//package yetanotherballproblem;

import java.util.*;
import java.io.*;

public class yetanotherballproblem {
	public static void main(String[] args) throws IOException {
		
		//1118E
		
		//just generate all possible combinations of colors. There is a way to arrange them so that it follows the rules. If you can't generate enough, then the input is invalid.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		int p1 = 1;
		int p2 = 2;
		boolean reverse = false;
		boolean isValid = true;
		StringBuilder fout = new StringBuilder();
		for(int i = 0; i < n; i++) {
			if(!reverse) {
				fout.append(p1).append(" ").append(p2).append("\n");
				reverse = true;
			}
			else {
				fout.append(p2).append(" ").append(p1).append("\n");
				reverse = false;
				p2 ++;
				if(p2 > k) {
					p1 ++;
					p2 = p1 + 1;
				}
				if(p1 == k && i != n - 1) {
					isValid = false;
				}
			}
		}
		if(isValid) {
			System.out.print("YES\n" + fout);
		}
		else {
			System.out.println("NO");
		}
	}
}
