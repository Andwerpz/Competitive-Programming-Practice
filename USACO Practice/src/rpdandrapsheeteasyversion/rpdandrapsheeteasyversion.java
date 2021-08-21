//package rpdandrapsheeteasyversion;

import java.util.*;
import java.io.*;

public class rpdandrapsheeteasyversion {
	
	static StreamTokenizer in;
	static int nextInt() throws IOException{
		in.nextToken();
		return (int)in.nval;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1543D1
		
		//not enough time for java to run, try c++ instead if you want to solve the problem
		
		in = new StreamTokenizer(new BufferedReader(new InputStreamReader(System.in)));
		PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
		int t = nextInt();
		while(t-- > 0) {
			int n = nextInt();
			int k = nextInt();
			for(int i = 0; i < n; i++) {
				if(i == 0) {
					out.println(0);
					out.flush();
				}
				else {
					out.println((i ^ (i - 1)));
					out.flush();
				}
				int r = nextInt();
				if(r == 1) {
					break;
				}
			}
		}
	}
}
