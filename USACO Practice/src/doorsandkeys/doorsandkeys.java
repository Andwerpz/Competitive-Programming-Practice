//package doorsandkeys;

import java.util.*;
import java.io.*;

public class doorsandkeys {
	public static void main(String[] args) throws IOException {
		
		//1644A
		
		//just make sure you get the key before opening the door
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			char[] c = fin.readLine().toCharArray();
			boolean r = false;
			boolean g = false;
			boolean b = false;
			boolean isValid = true;
			for(char a : c) {
				if(a == 'r') {
					r = true;
				}
				else if(a == 'g') {
					g = true;
				}
				else if(a == 'b') {
					b = true;
				}
				else if(a == 'R' && !r) {
					isValid = false;
					break;
				}
				else if(a == 'G' && !g) {
					isValid = false;
					break;
				}
				else if(a == 'B' && !b) {
					isValid = false;
					break;
				}
			}
			fout.append(isValid? "YES\n" : "NO\n");
		}
		System.out.print(fout);
	}
}
