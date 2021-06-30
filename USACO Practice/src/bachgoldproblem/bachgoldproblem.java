//package bachgoldproblem;

import java.util.*;
import java.io.*;

public class bachgoldproblem {
	public static void main(String[] args) throws IOException {
		
		//749A
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		fout.append(n / 2).append("\n");
		while(n != 3 && n != 0) {
			fout.append("2 ");
			n -= 2;
		}
		if(n == 3) {
			fout.append("3");
		}
		System.out.println(fout);
	}
}
