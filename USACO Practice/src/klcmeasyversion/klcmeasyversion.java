//package klcmeasyversion;

import java.util.*;
import java.io.*;

public class klcmeasyversion {
	public static void main(String[] args) throws IOException {
		
		//1497C1
		
		//the answer is so obvious, read the tutorial
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int k = Integer.parseInt(st.nextToken());
			if(n % 2 == 0) {
				if(n % 4 == 0) {
					fout.append(n / 2).append(" ").append(n / 4).append(" ").append(n / 4);
				}
				else {
					fout.append(2).append(" ").append(n / 2 - 1).append(" ").append(n / 2 - 1);
				}
			}
			else {
				fout.append(1).append(" ").append(n / 2).append(" ").append(n / 2);
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
