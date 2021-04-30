//package suffixarray1;

import java.util.*;
import java.io.*;

public class suffixarray1 {
	public static void main(String[] args) throws IOException {
		
		//solution works, but takes too much memory, O(n^2)
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		String s = fin.readLine();
		s += "$";
		s += s;
		String[][] str = new String[s.length() / 2][2];
		
		int k = (int) Math.ceil(Math.log10(s.length()) / Math.log10(2));
		//System.out.println(k);
		for(int i = 0; i < str.length; i++) {
			str[i][0] = s.substring(s.length() / 2 - i - 1, s.length() - i);
			str[i][1] = s.length() / 2 - i - 1 + "";
		}
		Arrays.sort(str, (a, b) -> a[0].compareTo(b[0]));
		StringBuilder fout = new StringBuilder();
		for(String[] i : str) {
			fout.append(i[1] + " ");
		}
		System.out.println(fout.substring(0, fout.length() - 1));
	}
}
