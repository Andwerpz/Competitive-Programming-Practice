//package differentrules;

import java.util.*;
import java.io.*;

public class differentrules {
	public static void main(String[] args) throws IOException {
		
		//1313B
		
		//first, to get the maximum place, we need to find out how many other combinations we can make that equal a + b. To do this, we can just subtract n from a + b.
		//this will give us a number, that is the highest place a person can get on the first round, and still be able to equal a + b. The lower this number is, the less
		//the number of people that will be able to get a score that equals a + b. Use a similar approach but opposite on finding the minimum placement.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int a = Integer.parseInt(st.nextToken());
			int b = Integer.parseInt(st.nextToken());
			int max = Math.min(a + b - 1, n);
			int min = Math.min(Math.max((a + b + 1) - n, 1), n);
			fout.append(min).append(" ").append(max).append("\n");
		}
		System.out.print(fout);
	}
}
