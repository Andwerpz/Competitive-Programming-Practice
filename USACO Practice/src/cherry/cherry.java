//package cherry;

import java.util.*;
import java.io.*;

public class cherry {
	public static void main(String[] args) throws IOException {
		
		//1554A
		
		//take the maximum out of the products of adjacent numbers.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			long ans = 0;
			long prev = 0;
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				if(i == 0) {
					prev = Integer.parseInt(st.nextToken());
				}
				else {
					long next = Integer.parseInt(st.nextToken());
					ans = Math.max(ans, next * prev);
					prev = next;
				}
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
