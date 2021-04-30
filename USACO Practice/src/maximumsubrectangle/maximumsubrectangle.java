package maximumsubrectangle;

import java.util.*;
import java.io.*;

public class maximumsubrectangle {
	
	static long[][] pfx;
	
	public static void main(String[] args) throws IOException {
		
		//CF round #513 C
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int[][] nums = new int[n][m];
		pfx = new long[n + 1][m + 1];
	}
}
