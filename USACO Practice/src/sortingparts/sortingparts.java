//package sortingparts;

import java.util.*;
import java.io.*;

public class sortingparts {
	public static void main(String[] args) throws IOException {
		
		//1637A
		
		//just check if the array is already sorted
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int prev = 0;
			boolean isValid = true;
			for(int i = 0; i < n; i++) {
				int next = Integer.parseInt(st.nextToken());
				if(next < prev) {
					isValid = false;
					break;
				}
				prev = next;
			}
			fout.append(isValid? "NO\n" : "YES\n");
		}
		System.out.print(fout);
	}
}
