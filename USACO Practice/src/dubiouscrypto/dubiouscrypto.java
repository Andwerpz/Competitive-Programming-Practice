//package dubiouscrypto;

import java.util.*;
import java.io.*;

public class dubiouscrypto {
	public static void main(String[] args) throws IOException {
		
		//1379B
		
		//just iterate through all possible values of a, and then check for valid values of b.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			long l = Long.parseLong(st.nextToken());
			long r = Long.parseLong(st.nextToken());
			long m = Long.parseLong(st.nextToken());
			long maxDiff = r - l + 1;
			//boolean isValid = false;
			for(long i = l; i <= r; i++) {
				long curDiff = m % i;
				//System.out.println(curDiff);
				if(curDiff < maxDiff && m - (curDiff) != 0 && r - curDiff >= l) {
					//System.out.println(curDiff);
					fout.append(i).append(" ").append(r).append(" ").append(r - curDiff).append("\n");
					break;
				}
				else if(i - curDiff <= maxDiff && l + (i - curDiff) <= r) {
					//System.out.println(i - curDiff);
					fout.append(i).append(" ").append(l).append(" ").append(l + (i - curDiff)).append("\n");
					break;
				}
			}
		}
		System.out.print(fout);
	}
}
