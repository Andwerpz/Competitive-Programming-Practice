//package dislikeofthrees;

import java.util.*;
import java.io.*;

public class dislikeofthrees {
	
	public static boolean isValid(int x) {
		if(x % 3 == 0 || x % 10 == 3) {
			return false;
		}
		return true;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1560A
		
		//remember to read the problem statement fully. It said "end with digit 3" not "contains digit 3".
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int k = Integer.parseInt(fin.readLine());
			int pointer = 0;
			for(int i = 0; i < k; i++) {
				pointer ++;
				while(!isValid(pointer)) {
					pointer ++;
				}
			}
			fout.append(pointer).append("\n");
		}
		System.out.print(fout);
	}
}
