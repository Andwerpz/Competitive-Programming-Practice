package partialteacher;

import java.util.*;
import java.io.*;

public class partialteacherver1 {
	public static void main(String[] args) throws IOException {
		
		//incorrect solution. too greedy
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		char[] s = fin.readLine().toCharArray();
		int prev = 0;
		ArrayList<ArrayList<Integer>> nums = new ArrayList<ArrayList<Integer>>();
		StringBuilder fout = new StringBuilder();
		fout.append(prev).append(" ");
		for(int i = 0; i < n - 1; i++) {
			if(s[i] == 'L') {
				
			}
			else if(s[i] == '='){
				
			}
			else {


			}
		}
		System.out.println(fout);
	}
}
