//package oddgrasshopper;

import java.util.*;
import java.io.*;

public class oddgrasshopper {
	public static void main(String[] args) throws IOException {
		
		//1607B
		
		//notice that the grasshopper changes direction only on odd distance jumps. 
		
		//use that to easily calculate the offset. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		int t = Integer.parseInt(fin.readLine());
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			long x = Long.parseLong(st.nextToken());
			long n = Long.parseLong(st.nextToken());
			long offset = -1;
			if(n == 0) {
				offset = 0;
			}
			else {
				long cycles = (n - 1) / 4 + ((n - 1) % 4 != 0? 1 : 0);
				offset -= cycles * 4;
				long summed = cycles * 4 + 1;
				//System.out.println(cycles + " " + summed + " " + offset);
				for(long i = summed; i > n; i--) {
					if(summed - 2 < i) {
						//System.out.println("sub " + i);
						offset += i;
					}
					else {
						offset -= i;
					}
				}
			}
			if(Math.abs(x) % 2 == 1) {
				offset *= -1;
			}
			//System.out.println("OFF:" +  offset);
			fout.append(x + offset).append("\n");
		}
		System.out.print(fout);
	}
}
