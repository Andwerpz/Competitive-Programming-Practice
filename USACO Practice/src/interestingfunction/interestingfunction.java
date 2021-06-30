//package interestingfunction;

import java.util.*;
import java.io.*;

public class interestingfunction {
	public static void main(String[] args) throws IOException {
		
		//1538F
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			long l = Integer.parseInt(st.nextToken());
			long r = Integer.parseInt(st.nextToken());
			int power = 0;
			long ans = 0;
			while(l != r) {
				while(l % (long) Math.pow(10, power + 1) == 0) {
					power ++;
				}
				long val = (long) Math.pow(10, power);
				while(l + val > r) {
					val /= 10;
					power --;
				}
				long increment = 1;
				for(int i = 0; i < power; i++) {
					increment = increment * 10l + 1l;
				}
				String test = l + "";
				int limit = (int) (Math.floor(Math.log10(val))) + 1;
				boolean added = false;
				for(int i = test.length() - 1; i >= 0; i--) {
					if(test.charAt(i) == '9' && (i < test.length() - limit? test.charAt(i + 1) == '9' : true)) {
						//System.out.println("ADDED");
						added = true;
						increment ++;
					}
					else if(test.charAt(i) != '0' || added || i < test.length() - limit){
						break;
					}
				}
				//System.out.println(l + " " + val + " " + increment);
				l += val;
				ans += increment;
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}
