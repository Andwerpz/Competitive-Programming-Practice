//package equidistantletters;

import java.util.*;
import java.io.*;

public class equidistantletters {
	public static void main(String[] args) throws IOException {
		
		//1626A
		
		//just sort the given string. Each pair will have distance of 1
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			char[] s = fin.readLine().toCharArray();
			Arrays.sort(s);
			fout.append(String.valueOf(s)).append("\n");
		}
		System.out.print(fout);
	}
}
