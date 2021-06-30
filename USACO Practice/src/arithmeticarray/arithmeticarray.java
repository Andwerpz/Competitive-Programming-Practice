//package arithmeticarray;

import java.util.*;
import java.io.*;

public class arithmeticarray {
	public static void main(String[] args) throws IOException {
		
		//1537A
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int sum = 0;
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				sum += Integer.parseInt(st.nextToken());
			}
			if(sum == n) {
				fout.append("0\n");
			}
			else if(sum < n) {
				fout.append("1\n");
			}
			else {
				fout.append(sum - n).append("\n");
			}
		}
		System.out.print(fout);
	}
}
