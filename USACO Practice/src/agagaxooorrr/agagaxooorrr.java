//package agagaxooorrr;

import java.util.*;
import java.io.*;

public class agagaxooorrr {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int[] pfx = new int[2005];
			for(int i = 1; i <= n; i++) {
				pfx[i] = pfx[i - 1] ^ Integer.parseInt(st.nextToken());
				//System.out.println(pfx[i]);
			}
			boolean isValid = pfx[n] == 0;
			for(int i = 1; i <= n; i++) {
				for(int j = i + 1; j < n; j++) {
					isValid |= (pfx[i] == (pfx[j] ^ pfx[i]) && pfx[i] == (pfx[j] ^ pfx[n]));
				}
			}
			fout.append(isValid? "YES\n" : "NO\n");
		}
		System.out.print(fout);
	}
}
