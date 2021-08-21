//package strangetable;

import java.util.*;
import java.io.*;

public class strangetable {
	public static void main(String[] args) throws IOException {
		
		//1506A
		
		//division
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0){
			StringTokenizer st = new StringTokenizer(fin.readLine());
			long n = Integer.parseInt(st.nextToken());
			long m = Integer.parseInt(st.nextToken());
			long x = Long.parseLong(st.nextToken());
			long ans = 0;
			ans += x / n + (x % n == 0? 0 : 1);
			ans += ((x - 1) % n) * m;
			//System.out.println(((x - 1) % n) * m);
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
