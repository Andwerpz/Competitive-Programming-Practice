//package nastiaandnearlygoodnumbers;

import java.util.*;
import java.io.*;

public class nastiaandnearlygoodnumbers {
	public static void main(String[] args) throws IOException {
		
		//1521A
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			long a = Integer.parseInt(st.nextToken());
			long b = Integer.parseInt(st.nextToken());
			if(b == 1) {
				fout.append("NO\n");
			}
			else {
				fout.append("YES\n");
				fout.append(a).append(" ").append(a * b).append(" ").append(a * (b + 1)).append("\n");
			}
		}
		System.out.print(fout);
	}
}
