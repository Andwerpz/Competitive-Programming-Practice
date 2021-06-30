//package conteststart;

import java.util.*;
import java.io.*;

public class conteststart {
	public static void main(String[] args) throws IOException {
		
		//1539A
		
		//combinatorics. idk how i solved this one, but it's very cheese. Read the tutorial
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int k = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(k-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			long n = Integer.parseInt(st.nextToken());
			long x = Integer.parseInt(st.nextToken());
			long t = Integer.parseInt(st.nextToken());
			long max = t / x;
			long ans = 0;
			if(n - 1 >= max) {
				n -= 1 + max;
				ans = (max * (max + 1)) / 2;
				ans += n * max;
			}
			else {
				n -= 1;
				ans = (n * (n + 1)) / 2;
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
