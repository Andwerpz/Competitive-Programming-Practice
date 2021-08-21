//package gregorandcryptography;

import java.util.*;
import java.io.*;

public class gregorandcryptography {
	public static void main(String[] args) throws IOException {
		
		//1549A
		
		//since p is greater than 5, and guaranteed to be prime, it is also guaranteed to be odd. This means that we can have two numbers: 2 and p - 1. both these numbers will
		//return 1 when modded by p.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int p = Integer.parseInt(fin.readLine());
			fout.append("2 ").append(p - 1).append("\n");
		}
		System.out.print(fout);
	}
}
