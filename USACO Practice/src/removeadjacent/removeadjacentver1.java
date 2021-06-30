package removeadjacent;

import java.util.*;
import java.io.*;

public class removeadjacentver1 {
	
	public static int solve(String s) {
		System.out.println(s);
		if(s.length() == 1) {
			return 0;
		}
		int max = 0;
		for(int i = 0; i < s.length(); i++) {
			if(s.charAt(i) != 'a') {
				//System.out.println(i);
				if(i == 0 && s.charAt(i + 1) == (char) (s.charAt(i) - 1)) {
					//System.out.println("LEFT");
					max = Math.max(max, solve(s.substring(i + 1)) + 1);
				}
				else if(i == s.length() - 1 && s.charAt(i - 1) == (char) (s.charAt(i) - 1)) {
					//System.out.println("RIGHT");
					max = Math.max(max, solve(s.substring(0, i - 1)) + 1);
				}
				else if(i > 0 && i < s.length() - 1){
					//System.out.println("SOLVE MID");
					if(s.charAt(i - 1) == (char) (s.charAt(i) - 1) || s.charAt(i + 1) == (char) (s.charAt(i) - 1)) {
						//System.out.println("REMOVE " + s.charAt(i));
						max = Math.max(max, solve(s.substring(0, i) + s.substring(i + 1)) + 1);
					}
				}
			}
		}
		return max;
	}
	
	public static void main(String[] args) throws IOException {
		
		//no need for a complete search. there is greedy solution
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		String s = fin.readLine();
		System.out.println(solve(s));
	}
}
