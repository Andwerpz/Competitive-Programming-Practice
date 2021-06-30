//package jumps;

import java.util.*;
import java.io.*;

public class jumps {
	public static void main(String[] args) throws IOException {
		
		//1455B
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int x = Integer.parseInt(fin.readLine());
			int pointer = 0;
			int add = 1;
			int counter = 0;
			while(pointer < x) {
				pointer += add;
				add ++;
				counter ++;
			}
			if(pointer == x) {
				fout.append(counter);
			}
			else if(pointer - 1 == x) {
				fout.append(counter + 1);
			}
			else {
				fout.append(counter);
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
