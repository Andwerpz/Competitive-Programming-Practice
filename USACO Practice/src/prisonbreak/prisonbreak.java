//package prisonbreak;

import java.util.*;
import java.io.*;

public class prisonbreak {
	public static void main(String[] args) throws IOException {
		
		//1482A
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int a = Integer.parseInt(st.nextToken());
			int b = Integer.parseInt(st.nextToken());
			fout.append(a * b).append("\n");
		}
		System.out.print(fout);
	}
}
