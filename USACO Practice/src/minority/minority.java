//package minority;

import java.util.*;
import java.io.*;

public class minority {
	public static void main(String[] args) throws IOException {
		
		//1633B
		
		//notice that not choosing the entire binary string as your substring will lead to unnecessary losses
		//in your final answer.
		
		//the only exception is when there are an equal amount of 1s and 0s in the string. In this case, you just need to 
		//get rid of a 1 or 0, and take that one. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			char[] s = fin.readLine().toCharArray();
			int zero = 0;
			int one = 0;
			for(int i = 0; i < s.length; i++) {
				if(s[i] == '0') {
					zero ++;
				}
				else {
					one ++;
				}
			}
			fout.append(zero == one? zero - 1 : Math.min(zero, one)).append("\n");
		}
		System.out.print(fout);
	}
}
